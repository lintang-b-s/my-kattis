import { NextResponse } from "next/server";

import { getKattisSolutions } from "@/lib/kattis-server";

export const dynamic = "force-dynamic";

export async function GET() {
  try {
    const data = await getKattisSolutions();
    if (!data) {
      return NextResponse.json(
        { error: "No synced Kattis data found yet." },
        { status: 404 },
      );
    }
    return NextResponse.json(data);
  } catch (err) {
    return NextResponse.json(
      { error: (err as Error).message || "Failed to read Kattis data." },
      { status: 500 },
    );
  }
}
