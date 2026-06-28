import { useEffect, useMemo, useState } from "react";
import { Link, useParams, useSearchParams } from "react-router-dom";
import { api } from "../api/client";
import { CodeBlock } from "../components/CodeBlock";
import type { Prediction, SnippetResponse } from "../types";

export function SnippetPage() {
  const { runId, snippetId } = useParams();
  const [params] = useSearchParams();
  const datasetId = params.get("dataset");

  const [snippet, setSnippet] = useState<SnippetResponse | null>(null);
  const [predictions, setPredictions] = useState<Prediction[]>([]);

  useEffect(() => {
    if (!runId || !snippetId || !datasetId) return;

    Promise.all([api.snippet(datasetId, snippetId), api.predictions(runId)]).then(
      ([snippetData, predictionData]) => {
        setSnippet(snippetData);
        setPredictions(
          predictionData.filter((p) => p.snippet_id === snippetId)
        );
      }
    );
  }, [runId, snippetId, datasetId]);

  const rawTruth = snippet?.snippet.is_vulnerable;

  const sortedPredictions = useMemo(
    () => [...predictions].sort((a, b) => a.detector_id.localeCompare(b.detector_id)),
    [predictions]
  );

  if (!snippet) {
    return <div className="page">Loading snippet</div>;
  }

  return (
    <div className="page">
      <div className="page-header">
        <div>
          <h1>{snippet.snippet.id}</h1>
          <p>
            <Link to={`/runs/${runId}`}>Back to run</Link>
          </p>
        </div>
        <span className={rawTruth ? "pill danger" : "pill safe"}>
          ground truth: {rawTruth ? "vulnerable" : "safe"}
        </span>
      </div>

      <div className="metric-grid">
        <div className="metric-card">
          <div className="metric-label">Language</div>
          <div className="metric-value small-value">
            {snippet.snippet.language}
          </div>
        </div>
        <div className="metric-card">
          <div className="metric-label">Vulnerability</div>
          <div className="metric-value small-value">
            {snippet.snippet.vulnerability_type}
          </div>
        </div>
        <div className="metric-card">
          <div className="metric-label">CWE</div>
          <div className="metric-value small-value">{snippet.snippet.cwe}</div>
        </div>
      </div>

      <div className="panel">
        <div className="panel-header">
          <h2>Source code</h2>
        </div>
        <CodeBlock code={snippet.code} />
      </div>

      <div className="panel">
        <div className="panel-header">
          <h2>Detector predictions</h2>
        </div>

        <div className="table-wrap">
          <table>
            <thead>
              <tr>
                <th>Detector</th>
                <th>Prediction</th>
                <th>Correct?</th>
                <th>Confidence</th>
                <th>Lines</th>
                <th>Runtime</th>
              </tr>
            </thead>
            <tbody>
              {sortedPredictions.map((p) => {
                const correct = p.predicted_vulnerable === rawTruth;

                return (
                  <tr key={p.detector_id}>
                    <td>{p.detector_id}</td>
                    <td>
                      <span
                        className={
                          p.predicted_vulnerable ? "pill danger" : "pill safe"
                        }
                      >
                        {p.predicted_vulnerable ? "vulnerable" : "safe"}
                      </span>
                    </td>
                    <td>
                      <span className={correct ? "pill safe" : "pill danger"}>
                        {correct ? "yes" : "no"}
                      </span>
                    </td>
                    <td>
                      {p.confidence === null || p.confidence === undefined
                        ? "-"
                        : p.confidence.toFixed(3)}
                    </td>
                    <td>{p.predicted_lines?.join(", ") || "-"}</td>
                    <td>{p.runtime_ms} ms</td>
                  </tr>
                );
              })}
            </tbody>
          </table>
        </div>
      </div>
    </div>
  );
}