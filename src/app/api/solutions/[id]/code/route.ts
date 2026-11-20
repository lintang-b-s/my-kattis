import { NextResponse } from "next/server";

import { getSolutionCode, isValidProblemId } from "@/lib/solution-code";

export const dynamic = "force-dynamic";

export async function GET(
  request: Request,
  context: { params: Promise<{ id: string }> },
) {
  try {
    const { id } = await context.params;
    const problemId = id.trim();

    if (!isValidProblemId(problemId)) {
      return NextResponse.json(
        { error: "Invalid problem ID." },
        { status: 400 },
      );
    }

    const { searchParams } = new URL(request.url);
    const lang = searchParams.get("lang")?.trim() ?? "";
    if (!lang) {
      return NextResponse.json(
        { error: "Query parameter 'lang' is required." },
        { status: 400 },
      );
    }

    const result = await getSolutionCode(problemId, lang);
    if (!result) {
      return NextResponse.json(
        { error: `No ${lang} solution code found for '${problemId}'.` },
        { status: 404 },
      );
    }

    const rawParam = searchParams.get("raw");
    if (rawParam === "1" || rawParam === "true") {
      return new Response(result.code, {
        status: 200,
        headers: {
          "Content-Type": "text/plain; charset=utf-8",
          "X-Content-Type-Options": "nosniff",
        },
      });
    }

    return NextResponse.json(result);
  } catch (err) {
    return NextResponse.json(
      { error: (err as Error).message || "Failed to read solution code." },
      { status: 500 },
    );
  }
}
