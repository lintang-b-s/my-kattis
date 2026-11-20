export interface SolvedProblem {
  id: string;
  name: string;
  link: string;
  difficulty: number | null;
  category: string;
  languages: string[];
  firstAcceptedAt: string | null;
}

export interface KattisSolutionsData {
  username: string;
  profileUrl: string;
  fetchedAt: string;
  problems: SolvedProblem[];
}

export type SortKey =
  | "name"
  | "id"
  | "difficulty"
  | "category"
  | "firstAcceptedAt";
export type SortDirection = "asc" | "desc";
