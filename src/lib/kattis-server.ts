import { spawn } from "node:child_process";
import fs from "node:fs/promises";
import path from "node:path";

import type { KattisSolutionsData } from "@/types/kattis";

const DATA_FILE_PATH = path.join(process.cwd(), "data", "kattis-solutions.json");
const FETCH_SCRIPT_PATH = path.join(process.cwd(), "scripts", "fetch_kattis.py");
const SYNC_TIMEOUT_MS = 120_000;

let syncInFlight = false;

export class SyncInProgressError extends Error {
  constructor() {
    super("A Kattis sync is already in progress. Please wait for it to finish.");
    this.name = "SyncInProgressError";
  }
}

export function isSyncInProgress(): boolean {
  return syncInFlight;
}

export function hasEnvCredentials(): boolean {
  return Boolean(
    process.env.KATTIS_USERNAME?.trim() && process.env.KATTIS_PASSWORD,
  );
}

export function getConfiguredUsername(): string {
  const configured = process.env.KATTIS_USERNAME?.trim() ?? "";
  // Kattis allows logging in with an email address, which is not a valid public profile slug.
  if (!configured || configured.includes("@")) {
    return "";
  }
  return configured;
}

export async function getKattisSolutions(
  filePath: string = DATA_FILE_PATH,
): Promise<KattisSolutionsData | null> {
  try {
    const raw = await fs.readFile(
      /*turbopackIgnore: true*/ filePath,
      "utf-8",
    );
    const parsed = JSON.parse(raw) as KattisSolutionsData;
    if (
      !parsed ||
      typeof parsed !== "object" ||
      !Array.isArray(parsed.problems)
    ) {
      return null;
    }
    return parsed;
  } catch (err) {
    const nodeErr = err as NodeJS.ErrnoException;
    if (nodeErr.code === "ENOENT") {
      return null;
    }
    if (err instanceof SyntaxError) {
      console.warn(
        `[kattis-server] Ignoring corrupt cache file at ${filePath}: ${err.message}`,
      );
      return null;
    }
    throw err;
  }
}

export interface SyncCredentials {
  username?: string;
  password?: string;
  showPartial?: boolean;
}

export async function runKattisSync(
  credentials?: SyncCredentials,
): Promise<KattisSolutionsData> {
  if (syncInFlight) {
    throw new SyncInProgressError();
  }

  const pythonBin = process.env.PYTHON_BIN?.trim() || "python3";

  const stdinPayload = JSON.stringify({
    username: credentials?.username?.trim() || undefined,
    password: credentials?.password || undefined,
    showPartial: credentials?.showPartial,
  });

  syncInFlight = true;

  try {
    return await new Promise<KattisSolutionsData>((resolve, reject) => {
      const child = spawn(
        /*turbopackIgnore: true*/ pythonBin,
        [FETCH_SCRIPT_PATH, "--stdin-json", "--output", DATA_FILE_PATH],
        {
          cwd: process.cwd(),
          env: process.env,
          stdio: ["pipe", "pipe", "pipe"],
        },
      );

      let stdout = "";
      let stderr = "";
      let settled = false;

      const timer = setTimeout(() => {
        if (settled) return;
        settled = true;
        child.kill("SIGTERM");
        reject(
          new Error(
            `Kattis sync timed out after ${Math.round(SYNC_TIMEOUT_MS / 1000)} seconds.`,
          ),
        );
      }, SYNC_TIMEOUT_MS);

      const finish = (fn: () => void) => {
        if (settled) return;
        settled = true;
        clearTimeout(timer);
        fn();
      };

      child.stdout.on("data", (chunk: Buffer) => {
        stdout += chunk.toString("utf-8");
      });

      child.stderr.on("data", (chunk: Buffer) => {
        stderr += chunk.toString("utf-8");
      });

      child.on("error", (err) => {
        finish(() =>
          reject(
            new Error(
              `Failed to start Python (${pythonBin}): ${err.message}. Ensure Python 3 with autokattis is installed.`,
            ),
          ),
        );
      });

      child.on("close", (code) => {
        finish(() => {
          if (code !== 0) {
            const message =
              stderr.trim() || `Sync script exited with code ${code}.`;
            reject(new Error(message));
            return;
          }

          try {
            const parsed = JSON.parse(stdout) as KattisSolutionsData;
            resolve(parsed);
          } catch (parseErr) {
            reject(
              new Error(
                `Failed to parse sync output as JSON: ${(parseErr as Error).message}`,
              ),
            );
          }
        });
      });

      child.stdin.write(stdinPayload);
      child.stdin.end();
    });
  } finally {
    syncInFlight = false;
  }
}
