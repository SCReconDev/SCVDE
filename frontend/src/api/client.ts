import type {
  Dataset,
  DatasetSummary,
  DetectorErrors,
  Prediction,
  RunListItem,
  RunSummary,
  SnippetResponse,
} from "../types";

export type DetectorInfo = {
  id: string;
  type: string;
  name?: string;
  backend?: string;
  error?: string;
};

export type LogsResponse = {
  run_id: string;
  logs: string;
};

const API_BASE_URL =
  import.meta.env.VITE_API_BASE_URL ?? "http://127.0.0.1:8000";

function buildUrl(path: string): string {
  return `${API_BASE_URL}${path}`;
}

async function request<T>(path: string): Promise<T> {
  const response = await fetch(buildUrl(path));

  if (!response.ok) {
    const text = await response.text();
    throw new Error(`API error ${response.status}: ${text}`);
  }

  return response.json() as Promise<T>;
}

function encode(value: string): string {
  return encodeURIComponent(value);
}

export const api = {
  health: () => request<{ status: string }>("/health"),

  datasets: () => request<DatasetSummary[]>("/datasets"),

  dataset: (datasetId: string) =>
    request<Dataset>(`/datasets/${encode(datasetId)}`),

  snippet: (datasetId: string, snippetId: string) =>
    request<SnippetResponse>(
      `/datasets/${encode(datasetId)}/snippets/${encode(snippetId)}`
    ),

  detectors: () => request<DetectorInfo[]>("/detectors"),

  runs: () => request<RunListItem[]>("/runs"),

  run: (runId: string) => request<unknown>(`/runs/${encode(runId)}`),

  runSummary: (runId: string) =>
    request<RunSummary>(`/runs/${encode(runId)}/summary`),

  predictions: (runId: string) =>
    request<Prediction[]>(`/runs/${encode(runId)}/predictions`),

  predictionsForDetector: (runId: string, detectorId: string) =>
    request<Prediction[]>(
      `/runs/${encode(runId)}/predictions?detector_id=${encode(detectorId)}`
    ),

  predictionsForSnippet: (runId: string, snippetId: string) =>
    request<Prediction[]>(
      `/runs/${encode(runId)}/predictions?snippet_id=${encode(snippetId)}`
    ),

  errors: (runId: string) =>
    request<Record<string, DetectorErrors>>(`/runs/${encode(runId)}/errors`),

  errorsForDetector: (runId: string, detectorId: string) =>
    request<DetectorErrors>(
      `/runs/${encode(runId)}/errors/${encode(detectorId)}`
    ),

  logs: (runId: string) =>
    request<LogsResponse>(`/runs/${encode(runId)}/logs`),
};