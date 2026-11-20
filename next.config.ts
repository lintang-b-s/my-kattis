import type { NextConfig } from "next";

const nextConfig: NextConfig = {
  outputFileTracingIncludes: {
    "/*": ["./data/kattis-solutions.json"],
  },
};

export default nextConfig;
