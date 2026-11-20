import fs from "node:fs/promises";
import path from "node:path";

import type { SolvedProblem } from "@/types/kattis";

const DEFAULT_SOLVED_DIR = path.join(
  /*turbopackIgnore: true*/ process.cwd(),
  "data",
  "solved",
);
const VALID_PROBLEM_ID_RE = /^[a-zA-Z0-9_-]+$/;

const LANGUAGE_EXTENSIONS: Record<string, string[]> = {
  "c++": [".cpp", ".cc", ".cxx", ".c++", ".hpp", ".h"],
  cpp: [".cpp", ".cc", ".cxx", ".c++", ".hpp", ".h"],
  c: [".c", ".h"],
  go: [".go"],
  golang: [".go"],
  python: [".py"],
  "python 2": [".py"],
  "python 3": [".py"],
  java: [".java"],
  rust: [".rs"],
  javascript: [".js", ".mjs", ".cjs"],
  "javascript (nodejs)": [".js", ".mjs", ".cjs"],
  "javascript (spidermonkey)": [".js", ".mjs", ".cjs"],
  typescript: [".ts"],
  "c#": [".cs"],
  kotlin: [".kt", ".kts"],
  ruby: [".rb"],
  php: [".php"],
  swift: [".swift"],
  haskell: [".hs"],
  scala: [".scala"],
  dart: [".dart"],
  pascal: [".pas"],
  ocaml: [".ml"],
  bash: [".sh"],
  lua: [".lua"],
  perl: [".pl"],
  zig: [".zig"],
};

const IGNORED_EXTENSIONS = new Set([".out", ".exe", ".o", ".obj", ".class"]);

export interface SolutionCodeResult {
  problemId: string;
  language: string;
  filename: string;
  relativePath: string;
  code: string;
}

export function isValidProblemId(problemId: string): boolean {
  return VALID_PROBLEM_ID_RE.test(problemId);
}

export function getExtensionsForLanguage(language: string): string[] {
  const normalized = language.trim().toLowerCase();
  if (!normalized) {
    return [];
  }

  if (LANGUAGE_EXTENSIONS[normalized]) {
    return LANGUAGE_EXTENSIONS[normalized];
  }

  // Handle versioned or runtime-qualified Kattis language labels (e.g. "Python 3 (PyPy)", "C++ 20").
  if (normalized.startsWith("c++")) return LANGUAGE_EXTENSIONS["c++"];
  if (normalized.startsWith("python")) return LANGUAGE_EXTENSIONS.python;
  if (normalized.startsWith("javascript")) return LANGUAGE_EXTENSIONS.javascript;
  if (normalized.startsWith("typescript")) return LANGUAGE_EXTENSIONS.typescript;
  if (normalized.startsWith("java")) return LANGUAGE_EXTENSIONS.java;
  if (normalized.startsWith("c#")) return LANGUAGE_EXTENSIONS["c#"];
  if (normalized.startsWith("go ") || normalized.startsWith("go(")) {
    return LANGUAGE_EXTENSIONS.go;
  }

  return [];
}

/**
 * Recursively scans `solvedDir` and indexes source files as:
 *   problemIdLower -> Map<extLower, relativePathFromSolvedDir>
 */
async function indexSolvedFiles(
  solvedDir: string,
): Promise<Map<string, Map<string, string>>> {
  const index = new Map<string, Map<string, string>>();
  const rootResolved = path.resolve(/*turbopackIgnore: true*/ solvedDir);

  async function walk(currentDir: string): Promise<void> {
    let entries;
    try {
      entries = await fs.readdir(
        /*turbopackIgnore: true*/ currentDir,
        { withFileTypes: true },
      );
    } catch (err) {
      const nodeErr = err as NodeJS.ErrnoException;
      if (nodeErr.code === "ENOENT" || nodeErr.code === "ENOTDIR") {
        return;
      }
      throw err;
    }

    entries.sort((a, b) => a.name.localeCompare(b.name));

    for (const entry of entries) {
      if (entry.name.startsWith(".") || entry.isSymbolicLink()) {
        continue;
      }

      const fullPath = path.join(currentDir, entry.name);
      if (entry.isDirectory()) {
        await walk(fullPath);
        continue;
      }

      if (!entry.isFile()) {
        continue;
      }

      const ext = path.extname(entry.name).toLowerCase();
      if (!ext || IGNORED_EXTENSIONS.has(ext)) {
        continue;
      }

      const stem = path.basename(entry.name, path.extname(entry.name)).toLowerCase();
      if (!stem) {
        continue;
      }

      const relPath = path.relative(rootResolved, fullPath);
      let byExt = index.get(stem);
      if (!byExt) {
        byExt = new Map<string, string>();
        index.set(stem, byExt);
      }
      if (!byExt.has(ext)) {
        byExt.set(ext, relPath);
      }
    }
  }

  await walk(rootResolved);
  return index;
}

function findMatchingRelativePath(
  index: Map<string, Map<string, string>>,
  problemId: string,
  language: string,
): string | null {
  if (!isValidProblemId(problemId)) {
    return null;
  }

  const extensions = getExtensionsForLanguage(language);
  if (extensions.length === 0) {
    return null;
  }

  const byExt = index.get(problemId.toLowerCase());
  if (!byExt) {
    return null;
  }

  for (const ext of extensions) {
    const match = byExt.get(ext);
    if (match) {
      return match;
    }
  }

  return null;
}

export async function getAvailableCodeMap(
  problems: SolvedProblem[],
  solvedDir: string = DEFAULT_SOLVED_DIR,
): Promise<Record<string, string[]>> {
  const index = await indexSolvedFiles(solvedDir);
  const available: Record<string, string[]> = {};

  for (const problem of problems) {
    const matchedLangs = problem.languages.filter(
      (lang) => findMatchingRelativePath(index, problem.id, lang) !== null,
    );
    if (matchedLangs.length > 0) {
      available[problem.id] = matchedLangs;
    }
  }

  return available;
}

export async function getSolutionCode(
  problemId: string,
  language: string,
  solvedDir: string = DEFAULT_SOLVED_DIR,
): Promise<SolutionCodeResult | null> {
  if (!isValidProblemId(problemId)) {
    return null;
  }

  const index = await indexSolvedFiles(solvedDir);
  const relPath = findMatchingRelativePath(index, problemId, language);
  if (!relPath) {
    return null;
  }

  const rootResolved = path.resolve(/*turbopackIgnore: true*/ solvedDir);
  const fullPath = path.resolve(/*turbopackIgnore: true*/ rootResolved, relPath);
  if (!fullPath.startsWith(`${rootResolved}${path.sep}`)) {
    return null;
  }

  const code = await fs.readFile(/*turbopackIgnore: true*/ fullPath, "utf-8");
  return {
    problemId,
    language,
    filename: path.basename(fullPath),
    relativePath: relPath.split(path.sep).join("/"),
    code,
  };
}
