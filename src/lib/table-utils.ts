import type { SolvedProblem, SortDirection, SortKey } from "@/types/kattis";

const WIB_OFFSET_MS = 7 * 60 * 60 * 1000;
const ISO_WITH_OFFSET_RE =
  /^\d{4}-\d{2}-\d{2}T\d{2}:\d{2}(?::\d{2}(?:\.\d+)?)?(?:Z|[+-]\d{2}:\d{2})$/;

function parseIsoTimestampMs(value: string | null | undefined): number {
  if (typeof value !== "string") {
    return Number.NaN;
  }
  const trimmed = value.trim();
  if (!ISO_WITH_OFFSET_RE.test(trimmed)) {
    return Number.NaN;
  }
  return Date.parse(trimmed);
}

export function formatDifficulty(difficulty: number | null): string {
  if (difficulty === null || Number.isNaN(difficulty)) {
    return "";
  }
  return difficulty.toFixed(1);
}

export function formatFirstAcceptedWib(
  firstAcceptedAt: string | null | undefined,
): string {
  const ms = parseIsoTimestampMs(firstAcceptedAt);
  if (Number.isNaN(ms)) {
    return "";
  }
  const wib = new Date(ms + WIB_OFFSET_MS);
  const pad = (n: number) => String(n).padStart(2, "0");
  return (
    `${wib.getUTCFullYear()}-${pad(wib.getUTCMonth() + 1)}-${pad(wib.getUTCDate())} ` +
    `${pad(wib.getUTCHours())}:${pad(wib.getUTCMinutes())}:${pad(wib.getUTCSeconds())} WIB`
  );
}

export function filterAndSortProblems(
  problems: SolvedProblem[],
  query: string,
  sortKey: SortKey,
  sortDir: SortDirection,
): SolvedProblem[] {
  const normalized = query.trim().toLowerCase();

  const filtered = normalized
    ? problems.filter((problem) => {
        const inName = problem.name.toLowerCase().includes(normalized);
        const inId = problem.id.toLowerCase().includes(normalized);
        const inCategory = problem.category.toLowerCase().includes(normalized);
        const inLangs = problem.languages.some((lang) =>
          lang.toLowerCase().includes(normalized),
        );
        const inFirstAccepted = formatFirstAcceptedWib(problem.firstAcceptedAt)
          .toLowerCase()
          .includes(normalized);
        return inName || inId || inCategory || inLangs || inFirstAccepted;
      })
    : problems.slice();

  const multiplier = sortDir === "asc" ? 1 : -1;

  filtered.sort((a, b) => {
    if (sortKey === "difficulty") {
      const aMissing = a.difficulty === null || Number.isNaN(a.difficulty);
      const bMissing = b.difficulty === null || Number.isNaN(b.difficulty);
      if (aMissing && bMissing) {
        return a.id.localeCompare(b.id);
      }
      if (aMissing) return 1;
      if (bMissing) return -1;
      const diff = (a.difficulty as number) - (b.difficulty as number);
      return diff !== 0 ? diff * multiplier : a.id.localeCompare(b.id);
    }

    if (sortKey === "category") {
      const aEmpty = a.category.trim() === "";
      const bEmpty = b.category.trim() === "";
      if (aEmpty && bEmpty) return a.name.localeCompare(b.name);
      if (aEmpty) return 1;
      if (bEmpty) return -1;
      const cmp = a.category.localeCompare(b.category, undefined, {
        numeric: true,
        sensitivity: "base",
      });
      return cmp !== 0 ? cmp * multiplier : a.name.localeCompare(b.name);
    }

    if (sortKey === "firstAcceptedAt") {
      const aMs = parseIsoTimestampMs(a.firstAcceptedAt);
      const bMs = parseIsoTimestampMs(b.firstAcceptedAt);
      const aMissing = Number.isNaN(aMs);
      const bMissing = Number.isNaN(bMs);
      if (aMissing && bMissing) return a.id.localeCompare(b.id);
      if (aMissing) return 1;
      if (bMissing) return -1;
      const diff = aMs - bMs;
      return diff !== 0 ? diff * multiplier : a.id.localeCompare(b.id);
    }

    const aVal = sortKey === "id" ? a.id : a.name;
    const bVal = sortKey === "id" ? b.id : b.name;
    const cmp = aVal.localeCompare(bVal, undefined, { sensitivity: "base" });
    return cmp !== 0 ? cmp * multiplier : a.id.localeCompare(b.id);
  });

  return filtered;
}
