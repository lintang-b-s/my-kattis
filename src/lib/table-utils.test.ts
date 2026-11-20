import { describe, expect, it } from "vitest";

import {
  filterAndSortProblems,
  formatDifficulty,
  formatFirstAcceptedWib,
} from "@/lib/table-utils";
import type { SolvedProblem } from "@/types/kattis";

const SAMPLE_PROBLEMS: SolvedProblem[] = [
  {
    id: "sorttwonumbers",
    name: "Sort Two Numbers",
    link: "https://open.kattis.com/problems/sorttwonumbers",
    difficulty: 1.4,
    category: "1.4c, Selection Only, 2 Cases",
    languages: ["C++", "Python 3"],
    firstAcceptedAt: "2025-01-01T17:00:00+07:00",
  },
  {
    id: "hello",
    name: "Hello World!",
    link: "https://open.kattis.com/problems/hello",
    difficulty: 1.2,
    category: "",
    languages: ["Rust"],
    firstAcceptedAt: "2025-01-03T10:00:00Z",
  },
  {
    id: "mystery",
    name: "Mystery Problem",
    link: "https://open.kattis.com/problems/mystery",
    difficulty: null,
    category: "3.5a, Dynamic Programming",
    languages: [],
    firstAcceptedAt: null,
  },
];

describe("formatDifficulty", () => {
  it("formats numeric difficulties to 1 decimal place", () => {
    expect(formatDifficulty(1.2)).toBe("1.2");
    expect(formatDifficulty(5)).toBe("5.0");
  });

  it("returns empty string for null or NaN", () => {
    expect(formatDifficulty(null)).toBe("");
    expect(formatDifficulty(Number.NaN)).toBe("");
  });
});

describe("formatFirstAcceptedWib", () => {
  it("formats WIB ISO timestamps cleanly", () => {
    expect(formatFirstAcceptedWib("2026-07-11T11:28:42+07:00")).toBe(
      "2026-07-11 11:28:42 WIB",
    );
  });

  it("converts UTC timestamps to WIB including date rollover", () => {
    expect(formatFirstAcceptedWib("2026-07-11T20:15:05Z")).toBe(
      "2026-07-12 03:15:05 WIB",
    );
  });

  it("returns empty string for null, undefined, empty, ambiguous, or invalid timestamps", () => {
    expect(formatFirstAcceptedWib(null)).toBe("");
    expect(formatFirstAcceptedWib(undefined)).toBe("");
    expect(formatFirstAcceptedWib("")).toBe("");
    expect(formatFirstAcceptedWib("not-a-date")).toBe("");
    expect(formatFirstAcceptedWib("1")).toBe("");
    expect(formatFirstAcceptedWib("123")).toBe("");
    expect(formatFirstAcceptedWib("2026-07-11 11:28:42")).toBe("");
  });
});

describe("filterAndSortProblems", () => {
  it("filters across name, id, category, languages, and WIB date case-insensitively", () => {
    expect(
      filterAndSortProblems(SAMPLE_PROBLEMS, "python", "name", "asc").map(
        (p) => p.id,
      ),
    ).toEqual(["sorttwonumbers"]);

    expect(
      filterAndSortProblems(SAMPLE_PROBLEMS, "dynamic", "name", "asc").map(
        (p) => p.id,
      ),
    ).toEqual(["mystery"]);

    expect(
      filterAndSortProblems(SAMPLE_PROBLEMS, "HELLO", "name", "asc").map(
        (p) => p.id,
      ),
    ).toEqual(["hello"]);

    expect(
      filterAndSortProblems(SAMPLE_PROBLEMS, "2025-01-03", "name", "asc").map(
        (p) => p.id,
      ),
    ).toEqual(["hello"]);
  });

  it("sorts by difficulty with null values always last", () => {
    expect(
      filterAndSortProblems(SAMPLE_PROBLEMS, "", "difficulty", "asc").map(
        (p) => p.id,
      ),
    ).toEqual(["hello", "sorttwonumbers", "mystery"]);

    expect(
      filterAndSortProblems(SAMPLE_PROBLEMS, "", "difficulty", "desc").map(
        (p) => p.id,
      ),
    ).toEqual(["sorttwonumbers", "hello", "mystery"]);
  });

  it("sorts by category with empty categories always last", () => {
    expect(
      filterAndSortProblems(SAMPLE_PROBLEMS, "", "category", "asc").map(
        (p) => p.id,
      ),
    ).toEqual(["sorttwonumbers", "mystery", "hello"]);

    expect(
      filterAndSortProblems(SAMPLE_PROBLEMS, "", "category", "desc").map(
        (p) => p.id,
      ),
    ).toEqual(["mystery", "sorttwonumbers", "hello"]);
  });

  it("sorts by firstAcceptedAt chronologically with missing values always last", () => {
    expect(
      filterAndSortProblems(SAMPLE_PROBLEMS, "", "firstAcceptedAt", "asc").map(
        (p) => p.id,
      ),
    ).toEqual(["sorttwonumbers", "hello", "mystery"]);

    expect(
      filterAndSortProblems(SAMPLE_PROBLEMS, "", "firstAcceptedAt", "desc").map(
        (p) => p.id,
      ),
    ).toEqual(["hello", "sorttwonumbers", "mystery"]);
  });

  it("handles legacy records missing firstAcceptedAt cleanly", () => {
    const legacy = {
      id: "legacy",
      name: "Legacy Problem",
      link: "https://open.kattis.com/problems/legacy",
      difficulty: 2.0,
      category: "",
      languages: ["C++"],
    } as unknown as SolvedProblem;

    expect(
      filterAndSortProblems(
        [legacy, SAMPLE_PROBLEMS[0]],
        "",
        "firstAcceptedAt",
        "asc",
      ).map((p) => p.id),
    ).toEqual(["sorttwonumbers", "legacy"]);

    expect(
      filterAndSortProblems([legacy], "2025", "firstAcceptedAt", "asc"),
    ).toEqual([]);
  });

  it("handles empty input cleanly", () => {
    expect(filterAndSortProblems([], "abc", "name", "asc")).toEqual([]);
  });
});
