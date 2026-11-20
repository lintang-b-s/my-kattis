import fs from "node:fs/promises";
import os from "node:os";
import path from "node:path";

import { afterEach, describe, expect, it, vi } from "vitest";

import {
  getConfiguredUsername,
  getKattisSolutions,
  SyncInProgressError,
} from "@/lib/kattis-server";
import * as kattisServer from "@/lib/kattis-server";
import { POST as syncPost } from "@/app/api/sync/route";

describe("getConfiguredUsername", () => {
  const originalUsername = process.env.KATTIS_USERNAME;

  afterEach(() => {
    if (originalUsername === undefined) {
      delete process.env.KATTIS_USERNAME;
    } else {
      process.env.KATTIS_USERNAME = originalUsername;
    }
  });

  it("returns trimmed username for normal Kattis handles", () => {
    process.env.KATTIS_USERNAME = "  lintangbs  ";
    expect(getConfiguredUsername()).toBe("lintangbs");
  });

  it("returns empty string when KATTIS_USERNAME is an email address", () => {
    process.env.KATTIS_USERNAME = "alice@example.com";
    expect(getConfiguredUsername()).toBe("");
  });
});

describe("getKattisSolutions", () => {
  it("returns null instead of throwing when cache file contains corrupt JSON", async () => {
    const tmpDir = await fs.mkdtemp(path.join(os.tmpdir(), "kattis-test-"));
    const corruptFile = path.join(tmpDir, "kattis-solutions.json");
    const warnSpy = vi.spyOn(console, "warn").mockImplementation(() => {});
    try {
      await fs.writeFile(corruptFile, "{corrupt json", "utf-8");
      const result = await getKattisSolutions(corruptFile);
      expect(result).toBeNull();
      expect(warnSpy).toHaveBeenCalledOnce();
    } finally {
      warnSpy.mockRestore();
      await fs.rm(tmpDir, { recursive: true, force: true });
    }
  });

  it("returns null when cache file does not exist", async () => {
    const result = await getKattisSolutions(
      path.join(os.tmpdir(), "non-existent-kattis-cache-12345.json"),
    );
    expect(result).toBeNull();
  });
});

describe("POST /api/sync validation and concurrency", () => {
  afterEach(() => {
    vi.restoreAllMocks();
  });

  it("returns 400 when body is JSON null", async () => {
    const req = new Request("http://localhost/api/sync", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: "null",
    });
    const res = await syncPost(req);
    expect(res.status).toBe(400);
    const json = await res.json();
    expect(json.error).toContain("JSON object");
  });

  it("returns 400 when body is a JSON array", async () => {
    const req = new Request("http://localhost/api/sync", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: "[]",
    });
    const res = await syncPost(req);
    expect(res.status).toBe(400);
  });

  it("returns 400 when username is not a string", async () => {
    const req = new Request("http://localhost/api/sync", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ username: 123, password: "secret" }),
    });
    const res = await syncPost(req);
    expect(res.status).toBe(400);
    const json = await res.json();
    expect(json.error).toContain("username");
  });

  it("returns 400 when password is not a string", async () => {
    const req = new Request("http://localhost/api/sync", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ username: "alice", password: 456 }),
    });
    const res = await syncPost(req);
    expect(res.status).toBe(400);
    const json = await res.json();
    expect(json.error).toContain("password");
  });

  it("returns 409 when a sync is already in progress", async () => {
    vi.spyOn(kattisServer, "runKattisSync").mockRejectedValueOnce(
      new SyncInProgressError(),
    );
    const req = new Request("http://localhost/api/sync", {
      method: "POST",
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ username: "alice", password: "secret" }),
    });
    const res = await syncPost(req);
    expect(res.status).toBe(409);
    const json = await res.json();
    expect(json.error).toContain("already in progress");
  });
});
