import type { NextConfig } from "next";

const SOLVED_SOURCE_GLOB =
  "./data/solved/**/*.{cpp,cc,cxx,c++,hpp,h,c,go,py,java,rs,js,mjs,cjs,ts,cs,kt,kts,rb,hs,ml,php,pas,swift,scala,dart,zig,lua,pl,sh}";

const nextConfig: NextConfig = {
  outputFileTracingIncludes: {
    "/": ["./data/kattis-solutions.json", SOLVED_SOURCE_GLOB],
    "/api/solutions": ["./data/kattis-solutions.json"],
    "/api/solutions/[id]/code": [SOLVED_SOURCE_GLOB],
  },
  outputFileTracingExcludes: {
    "/*": ["./data/solved/**/*.out", "data/solved/**/*.out", "**/*.out"],
  },
};

export default nextConfig;
