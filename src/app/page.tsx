import { SolutionsView } from "@/components/SolutionsView";
import {
  getConfiguredUsername,
  getKattisSolutions,
  hasEnvCredentials,
} from "@/lib/kattis-server";

export const dynamic = "force-dynamic";

export default async function HomePage() {
  const initialData = await getKattisSolutions();

  return (
    <SolutionsView
      initialData={initialData}
      configuredUsername={getConfiguredUsername()}
      hasEnvCredentials={hasEnvCredentials()}
    />
  );
}
