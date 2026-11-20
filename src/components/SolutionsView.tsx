"use client";

import { FormEvent, useMemo, useState } from "react";

import {
  filterAndSortProblems,
  formatDifficulty,
  formatFirstAcceptedWib,
} from "@/lib/table-utils";
import type {
  KattisSolutionsData,
  SortDirection,
  SortKey,
} from "@/types/kattis";

interface SolutionsViewProps {
  initialData: KattisSolutionsData | null;
  configuredUsername: string;
  hasEnvCredentials: boolean;
}

export function SolutionsView({
  initialData,
  configuredUsername,
  hasEnvCredentials,
}: SolutionsViewProps) {
  const [data, setData] = useState<KattisSolutionsData | null>(initialData);
  const [query, setQuery] = useState("");
  const [sortKey, setSortKey] = useState<SortKey>("name");
  const [sortDir, setSortDir] = useState<SortDirection>("asc");

  const [syncing, setSyncing] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const [showAuthForm, setShowAuthForm] = useState(
    !initialData && !hasEnvCredentials,
  );
  const [usernameInput, setUsernameInput] = useState(configuredUsername);
  const [passwordInput, setPasswordInput] = useState("");

  const displayUsername = data?.username || configuredUsername;
  const profileUrl =
    data?.profileUrl ||
    (displayUsername
      ? `https://open.kattis.com/users/${encodeURIComponent(displayUsername)}`
      : "");

  const problems = useMemo(
    () =>
      filterAndSortProblems(data?.problems ?? [], query, sortKey, sortDir),
    [data, query, sortKey, sortDir],
  );

  function handleSort(nextKey: SortKey) {
    if (sortKey === nextKey) {
      setSortDir((prev) => (prev === "asc" ? "desc" : "asc"));
    } else {
      setSortKey(nextKey);
      setSortDir("asc");
    }
  }

  function sortIndicator(key: SortKey) {
    if (sortKey !== key) return null;
    return sortDir === "asc" ? " ↑" : " ↓";
  }

  async function triggerSync(credentials?: {
    username: string;
    password: string;
  }) {
    setSyncing(true);
    setError(null);
    try {
      const response = await fetch("/api/sync", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(credentials ?? {}),
      });
      const json = await response.json();
      if (!response.ok) {
        throw new Error(json.error || "Failed to sync with Open Kattis.");
      }
      setData(json as KattisSolutionsData);
      setPasswordInput("");
      setShowAuthForm(false);
    } catch (err) {
      setError((err as Error).message);
    } finally {
      setSyncing(false);
    }
  }

  async function handleFormSubmit(event: FormEvent<HTMLFormElement>) {
    event.preventDefault();
    if (!usernameInput.trim() || !passwordInput) {
      setError("Please enter both your Open Kattis username and password.");
      return;
    }
    await triggerSync({
      username: usernameInput.trim(),
      password: passwordInput,
    });
  }

  return (
    <main className="mx-auto max-w-6xl px-4 py-10 sm:px-6 lg:px-8">
      <header className="mb-8 flex flex-col gap-4 border-b border-neutral-200 pb-6 sm:flex-row sm:items-end sm:justify-between">
        <div>
          <h1 className="text-3xl font-semibold tracking-tight text-neutral-900">
            My Kattis Solutions
          </h1>
          <p className="mt-1.5 text-base text-neutral-600">
            {displayUsername ? (
              <a
                href={profileUrl}
                target="_blank"
                rel="noopener noreferrer"
                className="font-medium text-blue-700 underline decoration-blue-300 underline-offset-4 hover:text-blue-900 hover:decoration-blue-600"
              >
                {displayUsername}
              </a>
            ) : (
              <span className="text-neutral-500">
                Not synced yet — connect your Open Kattis account below
              </span>
            )}
          </p>
        </div>

        <div className="flex items-center gap-3">
          {data && (
            <span className="text-sm text-neutral-500">
              {problems.length === data.problems.length
                ? `${data.problems.length} solved`
                : `${problems.length} of ${data.problems.length} solved`}
            </span>
          )}
          <button
            type="button"
            disabled={syncing}
            onClick={() => {
              if (hasEnvCredentials) {
                void triggerSync();
              } else {
                setShowAuthForm((prev) => !prev);
              }
            }}
            className="rounded-md border border-neutral-300 bg-white px-3.5 py-1.5 text-sm font-medium text-neutral-700 shadow-xs transition hover:bg-neutral-50 disabled:cursor-not-allowed disabled:opacity-50"
          >
            {syncing ? "Syncing..." : "Sync"}
          </button>
        </div>
      </header>

      {error && (
        <div
          role="alert"
          className="mb-6 rounded-md border border-red-200 bg-red-50 px-4 py-3 text-sm text-red-700"
        >
          {error}
        </div>
      )}

      {showAuthForm && (
        <form
          onSubmit={handleFormSubmit}
          className="mb-6 rounded-lg border border-neutral-200 bg-white p-4 shadow-xs"
        >
          <p className="mb-3 text-sm text-neutral-600">
            Sign in with your Open Kattis credentials to fetch your solved
            problems via <code className="font-mono text-xs">autokattis</code>{" "}
            (or set <code className="font-mono text-xs">KATTIS_USERNAME</code>{" "}
            and <code className="font-mono text-xs">KATTIS_PASSWORD</code> in{" "}
            <code className="font-mono text-xs">web/.env.local</code>).
          </p>
          <div className="flex flex-col gap-3 sm:flex-row">
            <input
              type="text"
              value={usernameInput}
              onChange={(e) => setUsernameInput(e.target.value)}
              placeholder="Kattis username or email"
              autoComplete="username"
              className="flex-1 rounded-md border border-neutral-300 px-3 py-1.5 text-sm focus:border-blue-500 focus:outline-none"
            />
            <input
              type="password"
              value={passwordInput}
              onChange={(e) => setPasswordInput(e.target.value)}
              placeholder="Kattis password"
              autoComplete="current-password"
              className="flex-1 rounded-md border border-neutral-300 px-3 py-1.5 text-sm focus:border-blue-500 focus:outline-none"
            />
            <button
              type="submit"
              disabled={syncing}
              className="rounded-md bg-neutral-900 px-4 py-1.5 text-sm font-medium text-white transition hover:bg-neutral-800 disabled:opacity-50"
            >
              {syncing ? "Fetching..." : "Fetch Solutions"}
            </button>
          </div>
        </form>
      )}

      <div className="mb-4 flex flex-col gap-2 sm:flex-row sm:items-center sm:justify-between">
        <input
          type="search"
          value={query}
          onChange={(e) => setQuery(e.target.value)}
          placeholder="Filter by name, ID, category, language, or date..."
          aria-label="Filter problems"
          className="w-full rounded-md border border-neutral-300 bg-white px-3 py-1.5 text-sm text-neutral-900 placeholder:text-neutral-400 focus:border-blue-500 focus:outline-none sm:max-w-sm"
        />
        {data?.fetchedAt && (
          <p className="text-xs text-neutral-400">
            Last synced:{" "}
            <time dateTime={data.fetchedAt} suppressHydrationWarning>
              {new Date(data.fetchedAt).toLocaleString()}
            </time>
          </p>
        )}
      </div>

      <div className="overflow-x-auto rounded-lg border border-neutral-200 bg-white shadow-xs">
        <table className="min-w-full divide-y divide-neutral-200 text-left text-sm">
          <thead className="bg-neutral-50 text-xs font-semibold uppercase tracking-wide text-neutral-600">
            <tr>
              <th
                scope="col"
                aria-sort={
                  sortKey === "name"
                    ? sortDir === "asc"
                      ? "ascending"
                      : "descending"
                    : "none"
                }
                className="px-4 py-3"
              >
                <button
                  type="button"
                  onClick={() => handleSort("name")}
                  className="hover:text-neutral-900"
                >
                  Problem Name{sortIndicator("name")}
                </button>
              </th>
              <th
                scope="col"
                aria-sort={
                  sortKey === "id"
                    ? sortDir === "asc"
                      ? "ascending"
                      : "descending"
                    : "none"
                }
                className="px-4 py-3"
              >
                <button
                  type="button"
                  onClick={() => handleSort("id")}
                  className="hover:text-neutral-900"
                >
                  Problem ID{sortIndicator("id")}
                </button>
              </th>
              <th
                scope="col"
                aria-sort={
                  sortKey === "difficulty"
                    ? sortDir === "asc"
                      ? "ascending"
                      : "descending"
                    : "none"
                }
                className="px-4 py-3"
              >
                <button
                  type="button"
                  onClick={() => handleSort("difficulty")}
                  className="hover:text-neutral-900"
                >
                  Difficulty{sortIndicator("difficulty")}
                </button>
              </th>
              <th
                scope="col"
                aria-sort={
                  sortKey === "category"
                    ? sortDir === "asc"
                      ? "ascending"
                      : "descending"
                    : "none"
                }
                className="px-4 py-3"
              >
                <button
                  type="button"
                  onClick={() => handleSort("category")}
                  className="hover:text-neutral-900"
                >
                  Category{sortIndicator("category")}
                </button>
              </th>
              <th scope="col" className="px-4 py-3">
                Programming Languages
              </th>
              <th
                scope="col"
                aria-sort={
                  sortKey === "firstAcceptedAt"
                    ? sortDir === "asc"
                      ? "ascending"
                      : "descending"
                    : "none"
                }
                className="whitespace-nowrap px-4 py-3"
              >
                <button
                  type="button"
                  onClick={() => handleSort("firstAcceptedAt")}
                  className="hover:text-neutral-900"
                >
                  First Accepted (WIB){sortIndicator("firstAcceptedAt")}
                </button>
              </th>
            </tr>
          </thead>
          <tbody className="divide-y divide-neutral-100">
            {problems.length === 0 ? (
              <tr>
                <td
                  colSpan={6}
                  className="px-4 py-10 text-center text-sm text-neutral-500"
                >
                  {data
                    ? data.problems.length === 0
                      ? "No solved problems found for this account yet."
                      : "No problems match your filter."
                    : "No solved problems loaded yet. Click Sync to fetch your Open Kattis solutions."}
                </td>
              </tr>
            ) : (
              problems.map((problem) => {
                const firstAcceptedWib = formatFirstAcceptedWib(
                  problem.firstAcceptedAt,
                );
                return (
                  <tr
                    key={problem.id}
                    className="transition-colors hover:bg-neutral-50"
                  >
                    <td className="px-4 py-3 font-medium text-neutral-900">
                      <a
                        href={problem.link}
                        target="_blank"
                        rel="noopener noreferrer"
                        className="text-blue-700 hover:text-blue-900 hover:underline"
                      >
                        {problem.name}
                      </a>
                    </td>
                    <td className="px-4 py-3 font-mono text-xs text-neutral-600">
                      {problem.id}
                    </td>
                    <td className="px-4 py-3 tabular-nums text-neutral-700">
                      {formatDifficulty(problem.difficulty)}
                    </td>
                    <td className="px-4 py-3 text-neutral-700">
                      {problem.category}
                    </td>
                    <td className="px-4 py-3 text-neutral-700">
                      {problem.languages.length > 0 ? (
                        <div className="flex flex-wrap gap-1.5">
                          {problem.languages.map((lang) => (
                            <span
                              key={lang}
                              className="inline-block rounded bg-neutral-100 px-2 py-0.5 text-xs font-medium text-neutral-700"
                            >
                              {lang}
                            </span>
                          ))}
                        </div>
                      ) : (
                        ""
                      )}
                    </td>
                    <td className="whitespace-nowrap px-4 py-3 tabular-nums text-neutral-700">
                      {firstAcceptedWib && problem.firstAcceptedAt ? (
                        <time dateTime={problem.firstAcceptedAt}>
                          {firstAcceptedWib}
                        </time>
                      ) : (
                        ""
                      )}
                    </td>
                  </tr>
                );
              })
            )}
          </tbody>
        </table>
      </div>
    </main>
  );
}
