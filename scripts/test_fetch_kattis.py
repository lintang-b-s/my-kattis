from datetime import datetime, timezone
import io
import json
from pathlib import Path
import tempfile
import unittest
from unittest.mock import MagicMock, patch
from zoneinfo import ZoneInfo

from scripts.fetch_kattis import (
    _write_text_atomic,
    build_solutions_payload,
    collect_ac_submission_metadata,
    collect_problem_languages,
    main,
    parse_ac_submission_languages_html,
    parse_ac_submissions_html,
    parse_categories_html,
    parse_submission_timestamp,
)

SAMPLE_CPBOOK_HTML = """
<table>
  <tbody>
    <tr class="Kattis nonstarred cp5">
      <td>sorttwonumbers</td>
      <td id="sorttwonumbers"><a href="https://open.kattis.com/problems/sorttwonumbers">sorttwonumbers</a></td>
      <td>1.4c, Selection Only, 2 Cases</td>
      <td>swap a and b if a &gt; b</td>
      <td>1313</td>
      <td>1.4</td>
    </tr>
    <tr class="Kattis nonstarred">
      <td>mnist10class</td>
      <td id="mnist10class"><a href="https://open.kattis.com/problems/mnist10class">mnist10class</a></td>
      <td><i>non-starred</i></td>
      <td>partial scoring problem</td>
      <td>258</td>
      <td>8.3</td>
    </tr>
    <tr class="UVa starred">
      <td>100</td>
      <td>3n+1</td>
      <td>1.4a</td>
      <td>hint</td>
    </tr>
  </tbody>
</table>
"""

SAMPLE_SUBMISSIONS_HTML = """
<table class="table2 double-rows">
  <thead><tr><th>P</th><th>Time</th><th>Team</th><th>Problem</th><th>Status</th><th>CPU</th><th>Lang</th><th>TC</th><th>View</th></tr></thead>
  <tbody>
    <tr>
      <td></td>
      <td>2025-01-01 10:00:00</td>
      <td></td>
      <td><a href="/problems/sorttwonumbers">Sort Two Numbers</a></td>
      <td>Accepted</td>
      <td>0.01 s</td>
      <td>C++</td>
      <td>10/10</td>
      <td><a href="/submissions/1001">Details</a></td>
    </tr>
    <tr>
      <td></td>
      <td>2025-01-02 10:00:00</td>
      <td></td>
      <td><a href="/contests/abc">Contest</a> / <a href="/problems/sorttwonumbers">Sort Two Numbers</a></td>
      <td>Accepted</td>
      <td>0.05 s</td>
      <td>Python 3</td>
      <td>10/10</td>
      <td><a href="/submissions/1002">Details</a></td>
    </tr>
    <tr>
      <td></td>
      <td>2025-01-03 10:00:00</td>
      <td></td>
      <td><a href="/problems/hello">Hello World!</a></td>
      <td>Accepted</td>
      <td>0.00 s</td>
      <td>Rust</td>
      <td>1/1</td>
      <td><a href="/submissions/1003">Details</a></td>
    </tr>
  </tbody>
</table>
"""


class TestFetchKattis(unittest.TestCase):
    def test_parse_categories_html_matches_kattis_rows_only(self):
        categories = parse_categories_html(SAMPLE_CPBOOK_HTML)
        self.assertEqual(
            categories,
            {
                "sorttwonumbers": "1.4c, Selection Only, 2 Cases",
                "mnist10class": "non-starred",
            },
        )
        self.assertNotIn("100", categories)

    def test_parse_categories_html_empty(self):
        self.assertEqual(parse_categories_html("<html><body></body></html>"), {})

    def test_parse_ac_submission_languages_html(self):
        pairs = parse_ac_submission_languages_html(SAMPLE_SUBMISSIONS_HTML)
        self.assertEqual(
            pairs,
            [
                ("sorttwonumbers", "C++"),
                ("sorttwonumbers", "Python 3"),
                ("hello", "Rust"),
            ],
        )

    def test_collect_problem_languages_aggregates_multiple_languages(self):
        kt = MagicMock()
        kt.get_max_workers.return_value = 2
        kt.get_base_url.return_value = "https://open.kattis.com"
        kt.get_username.return_value = "testuser"

        def fake_new_get(_url, params=None):
            resp = MagicMock()
            if params and params.get("page") == 0:
                resp.content = SAMPLE_SUBMISSIONS_HTML.encode("utf-8")
            else:
                resp.content = b"<html><body></body></html>"
            return resp

        kt.new_get.side_effect = fake_new_get
        result = collect_problem_languages(kt)
        self.assertEqual(
            result,
            {
                "hello": ["Rust"],
                "sorttwonumbers": ["C++", "Python 3"],
            },
        )

    def test_collect_problem_languages_falls_back_to_stats(self):
        kt = MagicMock()
        kt.get_max_workers.return_value = 1
        kt.get_base_url.return_value = "https://open.kattis.com"
        kt.get_username.return_value = "testuser"
        kt.new_get.side_effect = RuntimeError("network error")
        kt.stats.return_value = [
            {"id": "hello", "language": "Python 3"},
        ]

        result = collect_problem_languages(kt)
        self.assertEqual(result, {"hello": ["Python 3"]})

    def test_collect_problem_languages_merges_stats_on_partial_pagination_failure(self):
        kt = MagicMock()
        kt.get_max_workers.return_value = 1
        kt.get_base_url.return_value = "https://open.kattis.com"
        kt.get_username.return_value = "testuser"

        def fail_on_page_1(_url, params=None):
            if params and params.get("page") == 0:
                resp = MagicMock()
                resp.content = SAMPLE_SUBMISSIONS_HTML.encode("utf-8")
                return resp
            raise RuntimeError("mid-pagination timeout")

        kt.new_get.side_effect = fail_on_page_1
        kt.stats.return_value = [
            {"id": "twosum", "language": "Go"},
            {"id": "hello", "language": "C"},
        ]

        result = collect_problem_languages(kt)
        self.assertEqual(result["twosum"], ["Go"])
        self.assertEqual(result["hello"], ["C", "Rust"])
        self.assertEqual(result["sorttwonumbers"], ["C++", "Python 3"])

    def test_build_solutions_payload_empty_category_when_missing(self):
        payload = build_solutions_payload(
            username="lintang",
            solved_problems=[
                {
                    "id": "hello",
                    "name": "Hello World!",
                    "difficulty": 1.2,
                    "link": "https://open.kattis.com/problems/hello",
                },
                {
                    "id": "sorttwonumbers",
                    "name": "Sort Two Numbers",
                    "difficulty": 1.4,
                    "link": "https://open.kattis.com/problems/sorttwonumbers",
                },
            ],
            categories={"sorttwonumbers": "1.4c, Selection Only, 2 Cases"},
            languages_by_problem={
                "sorttwonumbers": ["C++", "Python 3"],
                "hello": ["Rust"],
            },
        )

        self.assertEqual(payload["username"], "lintang")
        self.assertEqual(payload["profileUrl"], "https://open.kattis.com/users/lintang")
        self.assertEqual(len(payload["problems"]), 2)

        by_id = {p["id"]: p for p in payload["problems"]}
        self.assertEqual(by_id["hello"]["category"], "")
        self.assertEqual(by_id["hello"]["languages"], ["Rust"])
        self.assertEqual(
            by_id["sorttwonumbers"]["category"], "1.4c, Selection Only, 2 Cases"
        )
        self.assertEqual(by_id["sorttwonumbers"]["languages"], ["C++", "Python 3"])

    def test_build_solutions_payload_deduplicates_and_normalizes_difficulty(self):
        payload = build_solutions_payload(
            username="user name",
            solved_problems=[
                {"id": "dup", "name": "Dup Problem", "difficulty": float("nan")},
                {"id": "dup", "name": "Dup Problem", "difficulty": 3.5},
                {"id": "infprob", "name": "Inf Problem", "difficulty": float("inf")},
            ],
            categories={},
            languages_by_problem={},
        )
        self.assertEqual(
            payload["profileUrl"], "https://open.kattis.com/users/user%20name"
        )
        self.assertEqual(len(payload["problems"]), 2)
        by_id = {p["id"]: p for p in payload["problems"]}
        self.assertEqual(by_id["dup"]["difficulty"], 3.5)
        self.assertIsNone(by_id["infprob"]["difficulty"])
        # Ensure strict JSON serialization succeeds without NaN/Infinity tokens.
        json.dumps(payload, allow_nan=False)

    def test_write_text_atomic_replaces_target(self):
        with tempfile.TemporaryDirectory() as tmpdir:
            target = Path(tmpdir) / "nested" / "solutions.json"
            _write_text_atomic(target, '{"ok": true}\n')
            self.assertEqual(target.read_text(encoding="utf-8"), '{"ok": true}\n')
            _write_text_atomic(target, '{"ok": 2}\n')
            self.assertEqual(target.read_text(encoding="utf-8"), '{"ok": 2}\n')
            # No leftover temp files in directory.
            self.assertEqual([p.name for p in target.parent.iterdir()], ["solutions.json"])

    def test_main_rejects_non_object_stdin_json(self):
        with (
            patch("sys.stdin", io.StringIO("null")),
            patch("sys.stderr", new_callable=io.StringIO) as fake_err,
        ):
            code = main(["--stdin-json"])
        self.assertEqual(code, 1)
        self.assertIn("JSON object", fake_err.getvalue())

    def test_parse_submission_timestamp_converts_timezones_to_wib(self):
        # UTC -> WIB (+7h, crossing midnight)
        dt_utc = parse_submission_timestamp("2026-07-11 20:15:05", source_tz=timezone.utc)
        self.assertIsNotNone(dt_utc)
        self.assertEqual(dt_utc.isoformat(), "2026-07-12T03:15:05+07:00")

        # Already Asia/Jakarta -> preserved as WIB without double-shifting
        dt_wib = parse_submission_timestamp(
            "2026-07-11 11:28:42",
            source_tz=ZoneInfo("Asia/Jakarta"),
        )
        self.assertIsNotNone(dt_wib)
        self.assertEqual(dt_wib.isoformat(), "2026-07-11T11:28:42+07:00")

        # America/New_York (EDT = UTC-4 in July -> +11h to WIB)
        dt_ny = parse_submission_timestamp(
            "2026-07-11 00:28:42",
            source_tz=ZoneInfo("America/New_York"),
        )
        self.assertIsNotNone(dt_ny)
        self.assertEqual(dt_ny.isoformat(), "2026-07-11T11:28:42+07:00")

    def test_parse_submission_timestamp_handles_time_only_and_midnight_rollover(self):
        ref = datetime(2026, 11, 20, 7, 41, 39, tzinfo=timezone.utc)  # 14:41:39 WIB
        dt_today = parse_submission_timestamp(
            "13:21:09",
            source_tz=ZoneInfo("Asia/Jakarta"),
            reference_time=ref,
        )
        self.assertIsNotNone(dt_today)
        self.assertEqual(dt_today.isoformat(), "2026-11-20T13:21:09+07:00")

        # Midnight rollover: submission at 23:59:50 WIB, fetched at 00:00:10 WIB next day
        ref_after_midnight = datetime(2026, 11, 20, 17, 0, 10, tzinfo=timezone.utc)  # Nov 21 00:00:10 WIB
        dt_prev_day = parse_submission_timestamp(
            "23:59:50",
            source_tz=ZoneInfo("Asia/Jakarta"),
            reference_time=ref_after_midnight,
        )
        self.assertIsNotNone(dt_prev_day)
        self.assertEqual(dt_prev_day.isoformat(), "2026-11-20T23:59:50+07:00")

        # Empty / invalid / non-string inputs
        self.assertIsNone(parse_submission_timestamp(None))
        self.assertIsNone(parse_submission_timestamp(""))
        self.assertIsNone(parse_submission_timestamp("not-a-timestamp"))
        self.assertIsNone(parse_submission_timestamp(12345))  # type: ignore[arg-type]

    def test_parse_ac_submissions_html_detects_profile_timezone(self):
        html_with_tz = f"""
        <select id="profile_timezone_identifier" name="timezone_identifier">
          <option value="UTC">UTC</option>
          <option value="Asia/Jakarta" selected="selected">Asia/Jakarta</option>
        </select>
        {SAMPLE_SUBMISSIONS_HTML}
        """
        records, detected_tz = parse_ac_submissions_html(html_with_tz)
        self.assertEqual(str(detected_tz), "Asia/Jakarta")
        self.assertEqual(len(records), 3)
        self.assertEqual(records[0][0], "sorttwonumbers")
        self.assertEqual(records[0][2].isoformat(), "2025-01-01T10:00:00+07:00")

    def test_collect_ac_submission_metadata_picks_earliest_ac_across_pages(self):
        page0 = """
        <select id="profile_timezone_identifier">
          <option value="Asia/Jakarta" selected="selected">Asia/Jakarta</option>
        </select>
        <table class="table2 double-rows">
          <tbody>
            <tr>
              <td></td><td>13:21:09</td><td></td>
              <td><a href="/problems/squaredeal">Square Deal</a></td>
              <td>Accepted</td><td>0.01 s</td><td>Python 3</td><td>19/19</td>
              <td><a href="/submissions/2002">Details</a></td>
            </tr>
          </tbody>
        </table>
        """
        page1 = """
        <select id="profile_timezone_identifier">
          <option value="Asia/Jakarta" selected="selected">Asia/Jakarta</option>
        </select>
        <table class="table2 double-rows">
          <tbody>
            <tr>
              <td></td><td>2026-07-11 11:28:42</td><td></td>
              <td><a href="/problems/squaredeal">Square Deal</a></td>
              <td>Accepted</td><td>0.00 s</td><td>C++</td><td>19/19</td>
              <td><a href="/submissions/1001">Details</a></td>
            </tr>
          </tbody>
        </table>
        """
        kt = MagicMock()
        kt.get_max_workers.return_value = 2
        kt.get_base_url.return_value = "https://open.kattis.com"
        kt.get_username.return_value = "testuser"

        def fake_new_get(_url, params=None):
            resp = MagicMock()
            resp.headers = {"Date": "Fri, 20 Nov 2026 07:41:39 GMT"}
            page = params.get("page") if params else 0
            if page == 0:
                resp.content = page0.encode("utf-8")
            elif page == 1:
                resp.content = page1.encode("utf-8")
            else:
                resp.content = b"<html><body></body></html>"
            return resp

        kt.new_get.side_effect = fake_new_get
        langs, first_ac = collect_ac_submission_metadata(kt)
        self.assertEqual(langs, {"squaredeal": ["C++", "Python 3"]})
        self.assertEqual(first_ac, {"squaredeal": "2026-07-11T11:28:42+07:00"})

    def test_collect_ac_submission_metadata_falls_back_to_stats_timestamp(self):
        kt = MagicMock()
        kt.get_max_workers.return_value = 1
        kt.get_base_url.return_value = "https://open.kattis.com"
        kt.get_username.return_value = "testuser"
        kt.new_get.side_effect = RuntimeError("network error")
        kt.stats.return_value = [
            {
                "id": "hello",
                "language": "Python 3",
                "timestamp": "2025-01-01 00:00:01",
            },
        ]

        langs, first_ac = collect_ac_submission_metadata(kt)
        self.assertEqual(langs, {"hello": ["Python 3"]})
        self.assertEqual(first_ac, {"hello": "2025-01-01T07:00:01+07:00"})

    def test_build_solutions_payload_includes_first_accepted_at(self):
        payload = build_solutions_payload(
            username="lintang",
            solved_problems=[
                {"id": "a", "name": "Problem A", "difficulty": 1.2},
                {"id": "b", "name": "Problem B", "difficulty": 2.3},
            ],
            categories={},
            languages_by_problem={"a": ["C++"]},
            first_accepted_by_problem={"a": "2026-07-11T11:28:42+07:00"},
        )
        by_id = {p["id"]: p for p in payload["problems"]}
        self.assertEqual(by_id["a"]["firstAcceptedAt"], "2026-07-11T11:28:42+07:00")
        self.assertIsNone(by_id["b"]["firstAcceptedAt"])

    def test_collect_ac_submission_metadata_falls_back_on_http_error_status(self):
        kt = MagicMock()
        kt.get_max_workers.return_value = 1
        kt.get_base_url.return_value = "https://open.kattis.com"
        kt.get_username.return_value = "testuser"

        error_resp = MagicMock()
        error_resp.status_code = 429
        error_resp.content = b"<html><body>Too Many Requests</body></html>"
        kt.new_get.return_value = error_resp
        kt.stats.return_value = [
            {
                "id": "hello",
                "language": "Rust",
                "timestamp": "2025-01-01 00:00:01",
            },
        ]

        langs, first_ac = collect_ac_submission_metadata(kt)
        self.assertEqual(langs, {"hello": ["Rust"]})
        self.assertEqual(first_ac, {"hello": "2025-01-01T07:00:01+07:00"})


if __name__ == "__main__":
    unittest.main()
