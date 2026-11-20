import fs from "node:fs/promises";
import os from "node:os";
import path from "node:path";

import { describe, expect, it } from "vitest";

import { GET as getCodeRoute } from "@/app/api/solutions/[id]/code/route";
import {
  getAvailableCodeMap,
  getExtensionsForLanguage,
  getSolutionCode,
  isValidProblemId,
} from "@/lib/solution-code";
import type { SolvedProblem } from "@/types/kattis";

describe("getExtensionsForLanguage", () => {
  it("maps common Kattis languages to expected file extensions", () => {
    expect(getExtensionsForLanguage("C++")).toContain(".cpp");
    expect(getExtensionsForLanguage("Go")).toContain(".go");
    expect(getExtensionsForLanguage("Python 3")).toContain(".py");
    expect(getExtensionsForLanguage("Python 3 (PyPy)")).toContain(".py");
    expect(getExtensionsForLanguage("Java")).toContain(".java");
    expect(getExtensionsForLanguage("JavaScript (NodeJS)")).toContain(".js");
    expect(getExtensionsForLanguage("Rust")).toContain(".rs");
  });

  it("returns empty array for unknown or blank languages", () => {
    expect(getExtensionsForLanguage("")).toEqual([]);
    expect(getExtensionsForLanguage("   ")).toEqual([]);
    expect(getExtensionsForLanguage("Brainfuck")).toEqual([]);
  });
});

describe("isValidProblemId", () => {
  it("accepts valid problem IDs including digits", () => {
    expect(isValidProblemId("abinitio")).toBe(true);
    expect(isValidProblemId("8queens")).toBe(true);
    expect(isValidProblemId("10kindsofpeople")).toBe(true);
    expect(isValidProblemId("routing_validator")).toBe(true);
  });

  it("rejects empty strings and path traversal characters", () => {
    expect(isValidProblemId("")).toBe(false);
    expect(isValidProblemId("..")).toBe(false);
    expect(isValidProblemId("../secret")).toBe(false);
    expect(isValidProblemId("chap2/abinitio")).toBe(false);
    expect(isValidProblemId("abinitio.cpp")).toBe(false);
    expect(isValidProblemId("a b")).toBe(false);
  });
});

describe("getAvailableCodeMap & getSolutionCode (temp fixtures)", () => {
  it("finds nested source files, ignores .out binaries, and handles multi-language problems", async () => {
    const tmpDir = await fs.mkdtemp(path.join(os.tmpdir(), "kattis-solved-"));
    try {
      await fs.mkdir(path.join(tmpDir, "chap2"), { recursive: true });
      await fs.mkdir(path.join(tmpDir, "chap3", "dp"), { recursive: true });

      const cppSource = "#include <iostream>\nint main() { return 0; }\n";
      const pySource = "print('hello')\n";

      await fs.writeFile(
        path.join(tmpDir, "chap2", "alpha.cpp"),
        cppSource,
        "utf-8",
      );
      // Compiled .out binary should be ignored even when stem matches
      await fs.writeFile(
        path.join(tmpDir, "chap2", "binaryonly.out"),
        "ELF_BINARY",
        "utf-8",
      );
      await fs.writeFile(
        path.join(tmpDir, "chap3", "dp", "Beta.py"),
        pySource,
        "utf-8",
      );

      const problems: SolvedProblem[] = [
        {
          id: "alpha",
          name: "Alpha",
          link: "https://open.kattis.com/problems/alpha",
          difficulty: 2.0,
          category: "Easy",
          languages: ["C++", "Go"],
          firstAcceptedAt: null,
        },
        {
          id: "beta",
          name: "Beta",
          link: "https://open.kattis.com/problems/beta",
          difficulty: 3.0,
          category: "Medium",
          languages: ["Python 3"],
          firstAcceptedAt: null,
        },
        {
          id: "binaryonly",
          name: "Binary Only",
          link: "https://open.kattis.com/problems/binaryonly",
          difficulty: 1.5,
          category: "Easy",
          languages: ["C++"],
          firstAcceptedAt: null,
        },
      ];

      const available = await getAvailableCodeMap(problems, tmpDir);
      expect(available).toEqual({
        alpha: ["C++"],
        beta: ["Python 3"],
      });

      const alphaCpp = await getSolutionCode("alpha", "C++", tmpDir);
      expect(alphaCpp).toEqual({
        problemId: "alpha",
        language: "C++",
        filename: "alpha.cpp",
        relativePath: "chap2/alpha.cpp",
        code: cppSource,
      });

      const alphaGo = await getSolutionCode("alpha", "Go", tmpDir);
      expect(alphaGo).toBeNull();

      const betaPy = await getSolutionCode("beta", "Python 3", tmpDir);
      expect(betaPy).toEqual({
        problemId: "beta",
        language: "Python 3",
        filename: "Beta.py",
        relativePath: "chap3/dp/Beta.py",
        code: pySource,
      });

      const binaryOnly = await getSolutionCode("binaryonly", "C++", tmpDir);
      expect(binaryOnly).toBeNull();
    } finally {
      await fs.rm(tmpDir, { recursive: true, force: true });
    }
  });

  it("handles missing solved directory gracefully", async () => {
    const missingDir = path.join(os.tmpdir(), "non-existent-solved-dir-99999");
    const problems: SolvedProblem[] = [
      {
        id: "alpha",
        name: "Alpha",
        link: "https://open.kattis.com/problems/alpha",
        difficulty: 2.0,
        category: "Easy",
        languages: ["C++"],
        firstAcceptedAt: null,
      },
    ];

    expect(await getAvailableCodeMap(problems, missingDir)).toEqual({});
    expect(await getSolutionCode("alpha", "C++", missingDir)).toBeNull();
  });

  it("ignores symlinks inside the solved directory", async () => {
    const tmpDir = await fs.mkdtemp(path.join(os.tmpdir(), "kattis-symlink-"));
    const outsideFile = path.join(os.tmpdir(), `outside-${Date.now()}.cpp`);
    try {
      await fs.writeFile(outsideFile, "// secret outside file\n", "utf-8");
      await fs.symlink(outsideFile, path.join(tmpDir, "linked.cpp"));

      const problems: SolvedProblem[] = [
        {
          id: "linked",
          name: "Linked",
          link: "https://open.kattis.com/problems/linked",
          difficulty: 2.0,
          category: "Easy",
          languages: ["C++"],
          firstAcceptedAt: null,
        },
      ];

      expect(await getAvailableCodeMap(problems, tmpDir)).toEqual({});
      expect(await getSolutionCode("linked", "C++", tmpDir)).toBeNull();
    } finally {
      await fs.rm(tmpDir, { recursive: true, force: true });
      await fs.rm(outsideFile, { force: true });
    }
  });
});

describe("GET /api/solutions/[id]/code", () => {
  it("returns 200 JSON with raw source code for an existing solved problem", async () => {
    const req = new Request(
      "http://localhost/api/solutions/abinitio/code?lang=C%2B%2B",
    );
    const res = await getCodeRoute(req, {
      params: Promise.resolve({ id: "abinitio" }),
    });
    expect(res.status).toBe(200);
    const json = await res.json();
    expect(json.problemId).toBe("abinitio");
    expect(json.language).toBe("C++");
    expect(json.filename).toBe("abinitio.cpp");
    expect(json.relativePath).toBe("chap2/abinitio.cpp");
    expect(typeof json.code).toBe("string");
    expect(json.code.length).toBeGreaterThan(0);
  });

  it("returns 200 text/plain when raw=1 is passed", async () => {
    const req = new Request(
      "http://localhost/api/solutions/abinitio/code?lang=C%2B%2B&raw=1",
    );
    const res = await getCodeRoute(req, {
      params: Promise.resolve({ id: "abinitio" }),
    });
    expect(res.status).toBe(200);
    expect(res.headers.get("content-type")).toContain("text/plain");
    const text = await res.text();
    expect(text.length).toBeGreaterThan(0);
  });

  it("returns 400 when lang query param is missing", async () => {
    const req = new Request("http://localhost/api/solutions/abinitio/code");
    const res = await getCodeRoute(req, {
      params: Promise.resolve({ id: "abinitio" }),
    });
    expect(res.status).toBe(400);
  });

  it("returns 400 for invalid problem ID / path traversal", async () => {
    const req = new Request(
      "http://localhost/api/solutions/..%2Fpackage.json/code?lang=C%2B%2B",
    );
    const res = await getCodeRoute(req, {
      params: Promise.resolve({ id: "../package.json" }),
    });
    expect(res.status).toBe(400);
  });

  it("returns 404 when language file does not exist for a solved problem", async () => {
    const req = new Request(
      "http://localhost/api/solutions/findmyfamily/code?lang=Go",
    );
    const res = await getCodeRoute(req, {
      params: Promise.resolve({ id: "findmyfamily" }),
    });
    expect(res.status).toBe(404);
  });
});
