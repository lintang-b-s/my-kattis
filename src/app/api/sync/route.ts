import { NextResponse } from "next/server";

import {
  hasEnvCredentials,
  runKattisSync,
  SyncInProgressError,
} from "@/lib/kattis-server";

export const dynamic = "force-dynamic";

interface SyncRequestBody {
  username?: string;
  password?: string;
  showPartial?: boolean;
}

export async function POST(request: Request) {
  let body: SyncRequestBody = {};
  try {
    const text = await request.text();
    if (text.trim()) {
      const parsed: unknown = JSON.parse(text);
      if (
        parsed === null ||
        typeof parsed !== "object" ||
        Array.isArray(parsed)
      ) {
        return NextResponse.json(
          { error: "Request body must be a JSON object." },
          { status: 400 },
        );
      }
      const record = parsed as Record<string, unknown>;
      if (
        record.username !== undefined &&
        typeof record.username !== "string"
      ) {
        return NextResponse.json(
          { error: "Field 'username' must be a string." },
          { status: 400 },
        );
      }
      if (
        record.password !== undefined &&
        typeof record.password !== "string"
      ) {
        return NextResponse.json(
          { error: "Field 'password' must be a string." },
          { status: 400 },
        );
      }
      if (
        record.showPartial !== undefined &&
        typeof record.showPartial !== "boolean"
      ) {
        return NextResponse.json(
          { error: "Field 'showPartial' must be a boolean." },
          { status: 400 },
        );
      }
      body = {
        username: record.username,
        password: record.password,
        showPartial: record.showPartial,
      };
    }
  } catch {
    return NextResponse.json(
      { error: "Invalid JSON request body." },
      { status: 400 },
    );
  }

  const hasBodyCreds = Boolean(body.username?.trim() && body.password);
  if (!hasBodyCreds && !hasEnvCredentials()) {
    return NextResponse.json(
      {
        error:
          "Kattis credentials are required. Set KATTIS_USERNAME and KATTIS_PASSWORD in .env.local or provide them in the sync form.",
      },
      { status: 400 },
    );
  }

  try {
    const data = await runKattisSync({
      username: body.username,
      password: body.password,
      showPartial: body.showPartial,
    });
    return NextResponse.json(data);
  } catch (err) {
    if (err instanceof SyncInProgressError) {
      return NextResponse.json({ error: err.message }, { status: 409 });
    }
    return NextResponse.json(
      { error: (err as Error).message || "Sync failed." },
      { status: 500 },
    );
  }
}
