#!/usr/bin/env python3
"""
Fetch solved Open Kattis problems via autokattis and enrich each problem with:
  - Category from cpbook.net/methodstosolve?oj=kattis (same source & parsing
    logic as kattis-hint-giver/background.js and kattis-hint-giver/kattis.js).
    If a problem has no category entry, category is "".
  - All programming languages used in Accepted (AC) submissions for each problem.
"""

from __future__ import annotations

import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
from datetime import datetime, timedelta, timezone, tzinfo
from email.utils import parsedate_to_datetime
import json
import math
import os
from pathlib import Path
import sys
import tempfile
from typing import Any
from urllib.parse import quote
from zoneinfo import ZoneInfo, ZoneInfoNotFoundError

from bs4 import BeautifulSoup
import requests

HINTS_SOURCE_URL = "https://cpbook.net/methodstosolve?oj=kattis"
OPEN_KATTIS_BASE_URL = "https://open.kattis.com"
WIB_TZ: tzinfo = timezone(timedelta(hours=7))


def parse_categories_html(html: str) -> dict[str, str]:
    """
    Parse the cpbook.net methodstosolve HTML page using the exact same rules
    as kattis-hint-giver/kattis.js:
      - select all elements matching `.Kattis`
      - children[0] text -> problem id
      - children[2] text -> category
    """
    soup = BeautifulSoup(html, "html.parser")
    categories: dict[str, str] = {}
    for row in soup.select(".Kattis"):
        cells = row.find_all("td", recursive=False)
        if len(cells) < 3:
            continue
        problem_id = cells[0].get_text(strip=True)
        category = cells[2].get_text(strip=True)
        if problem_id:
            categories[problem_id] = category
    return categories


def fetch_categories(timeout: float = 20.0) -> dict[str, str]:
    """Fetch Kattis problem categories from cpbook.net/methodstosolve?oj=kattis."""
    try:
        response = requests.get(HINTS_SOURCE_URL, timeout=timeout)
        response.raise_for_status()
        return parse_categories_html(response.text)
    except Exception as exc:
        print(
            f"[warn] Failed to fetch categories from {HINTS_SOURCE_URL}: {exc}",
            file=sys.stderr,
        )
        return {}


def _detect_page_timezone(soup: BeautifulSoup) -> tzinfo | None:
    """
    Detect the timezone Open Kattis used to render submission timestamps on the page
    from the user's selected `profile_timezone_identifier` option, if present.
    """
    select = soup.find("select", id="profile_timezone_identifier") or soup.find(
        "select", attrs={"name": "timezone_identifier"}
    )
    if not select:
        return None
    selected = select.find("option", selected=True)
    if not selected:
        return None
    tz_name = (selected.get("value") or selected.get_text(strip=True) or "").strip()
    if not tz_name:
        return None
    if tz_name.upper() == "UTC":
        return timezone.utc
    try:
        return ZoneInfo(tz_name)
    except ZoneInfoNotFoundError:
        return None


def parse_submission_timestamp(
    raw_value: str | None,
    source_tz: tzinfo = timezone.utc,
    reference_time: datetime | None = None,
) -> datetime | None:
    """
    Parse an Open Kattis submission timestamp string into a timezone-aware datetime
    converted to WIB (UTC+07:00).

    Open Kattis renders older submissions as `YYYY-MM-DD HH:MM:SS` in the user's
    configured profile timezone (or UTC when unset), and submissions from today as
    `HH:MM:SS` only.
    """
    if not isinstance(raw_value, str):
        return None
    text = raw_value.strip()
    if not text:
        return None

    ref_now = (
        reference_time.astimezone(source_tz)
        if reference_time is not None
        else datetime.now(source_tz)
    )

    for fmt in ("%Y-%m-%d %H:%M:%S", "%Y-%m-%d %H:%M", "%Y-%m-%d"):
        try:
            parsed = datetime.strptime(text, fmt).replace(tzinfo=source_tz)
            return parsed.astimezone(WIB_TZ)
        except ValueError:
            continue

    for time_fmt in ("%H:%M:%S", "%H:%M"):
        try:
            parsed_time = datetime.strptime(text, time_fmt).time()
            candidate = datetime.combine(ref_now.date(), parsed_time, tzinfo=source_tz)
            # Guard against midnight rollover between submission and page fetch.
            if candidate > ref_now + timedelta(minutes=5):
                candidate -= timedelta(days=1)
            return candidate.astimezone(WIB_TZ)
        except ValueError:
            continue

    try:
        iso_dt = datetime.fromisoformat(text.replace("Z", "+00:00"))
        if iso_dt.tzinfo is None:
            iso_dt = iso_dt.replace(tzinfo=source_tz)
        return iso_dt.astimezone(WIB_TZ)
    except ValueError:
        return None


def _response_reference_time(response: Any) -> datetime | None:
    """Extract an aware datetime from an HTTP response Date header, if available."""
    headers = getattr(response, "headers", None)
    if not headers or not hasattr(headers, "get"):
        return None
    date_header = headers.get("Date")
    if not isinstance(date_header, str) or not date_header.strip():
        return None
    try:
        parsed = parsedate_to_datetime(date_header)
        if parsed.tzinfo is None:
            parsed = parsed.replace(tzinfo=timezone.utc)
        return parsed
    except (TypeError, ValueError):
        return None


def parse_ac_submissions_html(
    html: str | bytes,
    reference_time: datetime | None = None,
) -> tuple[list[tuple[str, str, datetime | None]], tzinfo | None]:
    """
    Parse a single Open Kattis user submissions page (filtered to status=AC)
    and return a tuple of:
      - list of (problem_id, language, submitted_at_wib) tuples
      - detected page timezone (or None if not present in the HTML)
    """
    from autokattis.api.enums import SubmissionsColumn
    from autokattis.api.utils import get_last_path, get_table_rows

    soup = BeautifulSoup(html, "lxml")
    detected_tz = _detect_page_timezone(soup)
    source_tz = detected_tz or timezone.utc

    table = soup.find("table", class_="table2 double-rows")
    if not table:
        return [], detected_tz

    records: list[tuple[str, str, datetime | None]] = []
    min_cols = max(
        int(SubmissionsColumn.SUBMISSION_TIME),
        int(SubmissionsColumn.CONTEST_PROBLEM_NAME),
        int(SubmissionsColumn.PROGRAMMING_LANGUAGE),
    )
    for row in get_table_rows(table):
        columns = row.find_all("td")
        if not columns or not any(c.get_text(strip=True) for c in columns):
            continue
        if len(columns) <= min_cols:
            continue

        links = columns[SubmissionsColumn.CONTEST_PROBLEM_NAME].find_all("a")
        if not links:
            continue
        href = links[-1].get("href") or ""
        pid = get_last_path(href)
        if not pid:
            continue
        language = columns[SubmissionsColumn.PROGRAMMING_LANGUAGE].get_text(strip=True)
        raw_time = columns[SubmissionsColumn.SUBMISSION_TIME].get_text(strip=True)
        submitted_at = parse_submission_timestamp(
            raw_time,
            source_tz=source_tz,
            reference_time=reference_time,
        )
        records.append((pid, language, submitted_at))
    return records, detected_tz


def parse_ac_submission_languages_html(html: str) -> list[tuple[str, str]]:
    """
    Parse a single Open Kattis user submissions page (filtered to status=AC)
    and return a list of (problem_id, language) pairs.
    """
    records, _ = parse_ac_submissions_html(html)
    return [(pid, lang) for pid, lang, _ in records if pid and lang]


def collect_ac_submission_metadata(
    kt: Any,
) -> tuple[dict[str, list[str]], dict[str, str]]:
    """
    Collect per-problem metadata from all Accepted (AC) submissions for the
    authenticated user:
      1. All unique programming languages used in AC submissions.
      2. The earliest (first) AC submission timestamp in WIB (ISO 8601 +07:00).

    Uses the authenticated autokattis session (`kt.new_get`) to paginate all AC
    submissions in one pass so multiple languages and earlier AC submissions per
    problem are preserved, falling back to `kt.stats()` if needed.
    """
    languages_by_problem: dict[str, set[str]] = {}
    earliest_ac_by_problem: dict[str, datetime] = {}
    detected_tz: tzinfo | None = None

    has_content = True
    params = {"page": 0, "status": "AC"}
    max_workers = kt.get_max_workers() if hasattr(kt, "get_max_workers") else 6
    submissions_url = f"{kt.get_base_url()}/users/{kt.get_username()}?tab=submissions"

    pagination_failed = False
    try:
        with ThreadPoolExecutor(max_workers=max_workers) as executor:
            while has_content:
                has_content = False
                futures = []
                for _ in range(max_workers):
                    futures.append(
                        executor.submit(kt.new_get, submissions_url, params=params.copy())
                    )
                    params["page"] += 1

                for future in as_completed(futures):
                    response = future.result()
                    status_code = getattr(response, "status_code", None)
                    if isinstance(status_code, int) and status_code >= 400:
                        raise RuntimeError(
                            f"HTTP {status_code} while fetching AC submissions"
                        )
                    ref_time = _response_reference_time(response)
                    records, page_tz = parse_ac_submissions_html(
                        response.content,
                        reference_time=ref_time,
                    )
                    if page_tz is not None and detected_tz is None:
                        detected_tz = page_tz
                    if records:
                        has_content = True
                        for pid, lang, submitted_at in records:
                            if lang:
                                languages_by_problem.setdefault(pid, set()).add(lang)
                            if submitted_at is not None:
                                prev = earliest_ac_by_problem.get(pid)
                                if prev is None or submitted_at < prev:
                                    earliest_ac_by_problem[pid] = submitted_at
    except Exception as exc:
        pagination_failed = True
        print(
            f"[warn] AC submission pagination failed ({exc}); falling back to kt.stats()",
            file=sys.stderr,
        )

    if pagination_failed or not languages_by_problem:
        fallback_tz = detected_tz or timezone.utc
        for entry in kt.stats():
            pid = entry.get("id")
            if not pid:
                continue
            lang = entry.get("language")
            if lang:
                languages_by_problem.setdefault(pid, set()).add(lang)
            submitted_at = parse_submission_timestamp(
                entry.get("timestamp"),
                source_tz=fallback_tz,
            )
            if submitted_at is not None:
                prev = earliest_ac_by_problem.get(pid)
                if prev is None or submitted_at < prev:
                    earliest_ac_by_problem[pid] = submitted_at

    return (
        {pid: sorted(langs) for pid, langs in languages_by_problem.items()},
        {pid: dt.isoformat() for pid, dt in earliest_ac_by_problem.items()},
    )


def collect_problem_languages(kt: Any) -> dict[str, list[str]]:
    """Collect all unique programming languages used for AC submissions per problem."""
    languages_by_problem, _ = collect_ac_submission_metadata(kt)
    return languages_by_problem


def _normalize_difficulty(value: Any) -> float | None:
    """Return a finite float difficulty or None."""
    if value is None or isinstance(value, bool):
        return None
    try:
        parsed = float(value)
    except (TypeError, ValueError):
        return None
    return parsed if math.isfinite(parsed) else None


def build_solutions_payload(
    username: str,
    solved_problems: list[dict[str, Any]],
    categories: dict[str, str],
    languages_by_problem: dict[str, list[str]],
    first_accepted_by_problem: dict[str, str] | None = None,
) -> dict[str, Any]:
    """Combine solved problems, cpbook categories, AC languages, and first AC dates into final JSON."""
    first_accepted = first_accepted_by_problem or {}
    items_by_id: dict[str, dict[str, Any]] = {}
    for problem in solved_problems:
        pid = str(problem.get("id") or "").strip()
        if not pid:
            continue
        name = str(problem.get("name") or pid).strip()
        link = str(problem.get("link") or f"{OPEN_KATTIS_BASE_URL}/problems/{pid}").strip()
        difficulty = _normalize_difficulty(problem.get("difficulty"))
        category = categories.get(pid, "")
        languages = languages_by_problem.get(pid, [])
        first_accepted_at = first_accepted.get(pid)

        existing = items_by_id.get(pid)
        if existing is not None:
            if existing["difficulty"] is None and difficulty is not None:
                existing["difficulty"] = difficulty
            if existing["firstAcceptedAt"] is None and first_accepted_at is not None:
                existing["firstAcceptedAt"] = first_accepted_at
            continue

        items_by_id[pid] = {
            "id": pid,
            "name": name,
            "link": link,
            "difficulty": difficulty,
            "category": category,
            "languages": languages,
            "firstAcceptedAt": first_accepted_at,
        }

    items = sorted(
        items_by_id.values(),
        key=lambda item: (item["name"].lower(), item["id"].lower()),
    )

    return {
        "username": username,
        "profileUrl": f"{OPEN_KATTIS_BASE_URL}/users/{quote(username, safe='')}",
        "fetchedAt": datetime.now(timezone.utc).isoformat(),
        "problems": items,
    }


def fetch_kattis_solutions(
    username: str,
    password: str,
    show_partial: bool = False,
) -> dict[str, Any]:
    """Log into Open Kattis via autokattis and build the full solutions payload."""
    from autokattis import OpenKattis, set_verbose

    set_verbose(False)
    kt = OpenKattis(username, password)
    resolved_username = kt.get_username()

    with ThreadPoolExecutor(max_workers=3) as executor:
        problems_future = executor.submit(
            kt.problems,
            show_solved=True,
            show_partial=show_partial,
            show_tried=False,
            show_untried=False,
            low_detail_mode=False,
        )
        submissions_future = executor.submit(collect_ac_submission_metadata, kt)
        categories_future = executor.submit(fetch_categories)

        solved_problems = list(problems_future.result())
        languages_by_problem, first_accepted_by_problem = submissions_future.result()
        categories = categories_future.result()

    return build_solutions_payload(
        username=resolved_username,
        solved_problems=solved_problems,
        categories=categories,
        languages_by_problem=languages_by_problem,
        first_accepted_by_problem=first_accepted_by_problem,
    )


def _load_dotenv_file(dotenv_path: Path) -> None:
    """Minimal .env loader for standalone CLI usage without extra dependencies."""
    if not dotenv_path.is_file():
        return
    for raw_line in dotenv_path.read_text(encoding="utf-8").splitlines():
        line = raw_line.strip()
        if not line or line.startswith("#") or "=" not in line:
            continue
        key, value = line.split("=", 1)
        key = key.strip()
        value = value.strip().strip('"').strip("'")
        if key and key not in os.environ:
            os.environ[key] = value


def _write_text_atomic(target: Path, content: str) -> None:
    """Atomically write UTF-8 text to target via a sibling temp file + os.replace."""
    target.parent.mkdir(parents=True, exist_ok=True)
    tmp_path: Path | None = None
    try:
        with tempfile.NamedTemporaryFile(
            mode="w",
            encoding="utf-8",
            dir=target.parent,
            prefix=f".{target.name}.",
            suffix=".tmp",
            delete=False,
        ) as handle:
            tmp_path = Path(handle.name)
            handle.write(content)
            handle.flush()
            os.fsync(handle.fileno())
        os.replace(tmp_path, target)
    except Exception:
        if tmp_path is not None and tmp_path.exists():
            tmp_path.unlink(missing_ok=True)
        raise


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        description="Fetch Open Kattis solved problems using autokattis."
    )
    parser.add_argument(
        "--output",
        type=Path,
        default=None,
        help="Optional path to write the resulting JSON file.",
    )
    parser.add_argument(
        "--stdin-json",
        action="store_true",
        help="Read JSON credentials {username, password, showPartial} from stdin.",
    )
    parser.add_argument(
        "--show-partial",
        action="store_true",
        default=None,
        help="Include partially solved problems.",
    )
    args = parser.parse_args(argv)

    project_root = Path(__file__).resolve().parent.parent
    _load_dotenv_file(project_root / ".env.local")
    _load_dotenv_file(project_root / ".env")

    username = os.environ.get("KATTIS_USERNAME", "").strip()
    password = os.environ.get("KATTIS_PASSWORD", "")
    show_partial = os.environ.get("KATTIS_SHOW_PARTIAL", "").lower() in (
        "1",
        "true",
        "yes",
    )

    if args.stdin_json:
        raw_stdin = sys.stdin.read().strip()
        if raw_stdin:
            try:
                stdin_payload = json.loads(raw_stdin)
            except json.JSONDecodeError as exc:
                print(f"Invalid JSON on stdin: {exc}", file=sys.stderr)
                return 1
            if not isinstance(stdin_payload, dict):
                print("Expected a JSON object on stdin.", file=sys.stderr)
                return 1
            if isinstance(stdin_payload.get("username"), str) and stdin_payload["username"].strip():
                username = stdin_payload["username"].strip()
            if isinstance(stdin_payload.get("password"), str) and stdin_payload["password"]:
                password = stdin_payload["password"]
            if "showPartial" in stdin_payload and stdin_payload["showPartial"] is not None:
                show_partial = bool(stdin_payload["showPartial"])

    if args.show_partial is not None:
        show_partial = args.show_partial

    if not username or not password:
        print(
            "Missing KATTIS_USERNAME or KATTIS_PASSWORD. Set them in web/.env.local "
            "or pass them via --stdin-json.",
            file=sys.stderr,
        )
        return 1

    try:
        payload = fetch_kattis_solutions(
            username=username,
            password=password,
            show_partial=show_partial,
        )
    except Exception as exc:
        print(f"Failed to fetch Kattis solutions: {exc}", file=sys.stderr)
        return 1

    encoded = json.dumps(payload, indent=2, ensure_ascii=False, allow_nan=False)
    if args.output:
        _write_text_atomic(args.output, encoded + "\n")

    print(encoded)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
