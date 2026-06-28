export type Snippet = {
  id: string;
  file_path: string;
  language: string;
  vulnerability_type: string;
  cwe?: string;
  is_vulnerable: boolean;
  expected_vulnerable_lines?: number[];
  difficulty?: string;
};

export type DatasetSummary = {
  id: string;
  name?: string;
  language?: string;
  vulnerability_types?: string[];
  num_snippets?: number;
  num_safe?: number;
  num_vulnerable?: number;
  error?: string;
};

export type Dataset = {
  id: string;
  name: string;
  language: string;
  vulnerability_types: string[];
  snippets: Snippet[];
  created_at?: string;
  updated_at?: string;
};

export type SnippetResponse = {
  dataset_id: string;
  snippet: Snippet;
  code: string;
};

export type DetectorMetric = {
  detector_id: string;
  detector_type: string;
  num_evaluated: number;
  true_positives: number;
  false_positives: number;
  true_negatives: number;
  false_negatives: number;
  accuracy: number;
  precision: number;
  recall: number;
  f1: number;
  false_positive_rate: number;
  false_negative_rate: number;
  avg_runtime_ms: number;
};

export type RunSummary = {
  run_id: string;
  dataset_id: string;
  status: string;
  created_at: string;
  completed_at?: string;
  num_snippets: number;
  detectors: DetectorMetric[];
};

export type RunListItem = {
  id: string;
  dataset_id?: string;
  status?: string;
  created_at?: string;
  completed_at?: string;
  detectors?: string[];
  num_snippets?: number;
  error?: string;
};

export type Prediction = {
  snippet_id: string;
  detector_id: string;
  detector_type: string;
  predicted_vulnerable: boolean;
  predicted_vulnerability_type: string | null;
  confidence: number | null;
  predicted_lines: number[];
  runtime_ms: number;
  raw_output: unknown;
};

export type ErrorItem = {
  snippet: Snippet;
  prediction: Prediction;
};

export type DetectorErrors = {
  false_positives: ErrorItem[];
  false_negatives: ErrorItem[];
};