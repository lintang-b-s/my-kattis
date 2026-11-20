import { SolutionsView } from "@/components/SolutionsView";
import {
  getConfiguredUsername,
  getKattisSolutions,
} from "@/lib/kattis-server";
import { getAvailableCodeMap } from "@/lib/solution-code";

export const dynamic = "force-dynamic";

export default async function HomePage() {
  const initialData = await getKattisSolutions();
  const availableCodeByProblem = initialData
    ? await getAvailableCodeMap(initialData.problems)
    : {};

  return (
    <SolutionsView
      initialData={initialData}
      configuredUsername={getConfiguredUsername()}
      availableCodeByProblem={availableCodeByProblem}
    />
  );
}
