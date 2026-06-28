import { useEffect, useMemo, useState } from "react";
import { Link, useParams } from "react-router-dom";
import { api } from "../api/client";
import { MetricCard } from "../components/MetricCard";
import { MetricsChart } from "../components/MetricsChart";
import type {
  Dataset,
  DetectorErrors,
  Prediction,
  RunSummary,
} from "../types";

export function RunDetailPage() {
  const { runId } = useParams();

  const [summary, setSummary] = useState<RunSummary | null>(null);
  const [dataset, setDataset] = useState<Dataset | null>(null);
  const [predictions, setPredictions] = useState<Prediction[]>([]);
  const [errors, setErrors] = useState<Record<string, DetectorErrors>>({});
  const [selectedDetector, setSelectedDetector] = useState<string>("");

  const [showWrongPredictions, setShowWrongPredictions] = useState(false);
  const [showPredictions, setShowPredictions] = useState(false);

  useEffect(() => {
    if (!runId) return;

    Promise.all([
      api.runSummary(runId),
      api.predictions(runId),
      api.errors(runId),
    ]).then(async ([summaryData, predictionsData, errorsData]) => {
      setSummary(summaryData);
      setPredictions(predictionsData);
      setErrors(errorsData);
      setSelectedDetector(summaryData.detectors[0]?.detector_id ?? "");

      const datasetData = await api.dataset(summaryData.dataset_id);
      setDataset(datasetData);
    });
  }, [runId]);

  const groundTruthBySnippetId = useMemo(() => {
    const map = new Map<string, boolean>();

    dataset?.snippets.forEach((snippet) => {
      map.set(snippet.id, snippet.is_vulnerable);
    });

    return map;
  }, [dataset]);

  const bestDetector = useMemo(() => {
    if (!summary?.detectors.length) return null;
    return [...summary.detectors].sort((a, b) => b.f1 - a.f1)[0];
  }, [summary]);

  function isPredictionCorrect(prediction: Prediction): boolean | null {
    const groundTruth = groundTruthBySnippetId.get(prediction.snippet_id);

    if (groundTruth === undefined) {
      return null;
    }

    return prediction.predicted_vulnerable === groundTruth;
  }

  if (!summary) {
    return <div className="page">Loading run...</div>;
  }

  const selectedErrors = selectedDetector ? errors[selectedDetector] : undefined;

  return (
    <div className="page">
      <div className="page-header">
        <div>
          <h1>{summary.run_id}</h1>
          <p>
            Dataset: <strong>{summary.dataset_id}</strong>
          </p>
        </div>

        <span className={`status status-${summary.status}`}>
          {summary.status}
        </span>
      </div>

      <div className="metric-grid">
        <MetricCard label="Snippets" value={summary.num_snippets} />

        <MetricCard label="Detectors" value={summary.detectors.length} />

        <MetricCard
          label="Best F1"
          value={bestDetector ? bestDetector.f1 : "-"}
          hint={bestDetector?.detector_id}
        />

        <MetricCard
          label="Completed"
          value={summary.completed_at ? "Yes" : "No"}
          hint={summary.completed_at}
        />
      </div>

      <MetricsChart metrics={summary.detectors} />

      <div className="panel">
        <div className="panel-header">
          <h2>Metrics</h2>
        </div>

        <div className="table-wrap">
          <table>
            <thead>
              <tr>
                <th>Detector</th>
                <th>Type</th>
                <th>Accuracy</th>
                <th>Precision</th>
                <th>Recall</th>
                <th>F1</th>
                <th>FP</th>
                <th>FN</th>
                <th>Runtime</th>
              </tr>
            </thead>

            <tbody>
              {summary.detectors.map((m) => (
                <tr key={m.detector_id}>
                  <td>{m.detector_id}</td>
                  <td>{m.detector_type}</td>
                  <td>{m.accuracy}</td>
                  <td>{m.precision}</td>
                  <td>{m.recall}</td>
                  <td>
                    <strong>{m.f1}</strong>
                  </td>
                  <td>{m.false_positives}</td>
                  <td>{m.false_negatives}</td>
                  <td>{m.avg_runtime_ms} ms</td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      </div>

      <div className="panel">
        <div className="panel-header clickable-header">
          <button
            className="collapse-button"
            type="button"
            onClick={() => setShowWrongPredictions((value) => !value)}
          >
            <span>{showWrongPredictions ? "▾" : "▸"}</span>
            <h2>Wrong predictions</h2>
          </button>

          {showWrongPredictions && (
            <select
              className="select"
              value={selectedDetector}
              onChange={(e) => setSelectedDetector(e.target.value)}
            >
              {summary.detectors.map((d) => (
                <option key={d.detector_id} value={d.detector_id}>
                  {d.detector_id}
                </option>
              ))}
            </select>
          )}
        </div>

        {showWrongPredictions && (
          <div className="error-columns">
            <div>
              <h3>False positives</h3>

              {selectedErrors?.false_positives?.length ? (
                selectedErrors.false_positives.map((item) => (
                  <Link
                    className="error-card"
                    key={item.snippet.id}
                    to={`/runs/${summary.run_id}/snippets/${item.snippet.id}?dataset=${summary.dataset_id}`}
                  >
                    <strong>{item.snippet.id}</strong>
                    <span>{item.snippet.vulnerability_type}</span>
                  </Link>
                ))
              ) : (
                <p className="muted">No false positives.</p>
              )}
            </div>

            <div>
              <h3>False negatives</h3>

              {selectedErrors?.false_negatives?.length ? (
                selectedErrors.false_negatives.map((item) => (
                  <Link
                    className="error-card"
                    key={item.snippet.id}
                    to={`/runs/${summary.run_id}/snippets/${item.snippet.id}?dataset=${summary.dataset_id}`}
                  >
                    <strong>{item.snippet.id}</strong>
                    <span>{item.snippet.vulnerability_type}</span>
                  </Link>
                ))
              ) : (
                <p className="muted">No false negatives</p>
              )}
            </div>
          </div>
        )}
      </div>

      <div className="panel">
        <div className="panel-header clickable-header">
          <button
            className="collapse-button"
            type="button"
            onClick={() => setShowPredictions((value) => !value)}
          >
            <span>{showPredictions ? "▾" : "▸"}</span>
            <h2>Predictions</h2>
          </button>

          <span>{predictions.length} rows</span>
        </div>

        {showPredictions && (
          <div className="table-wrap compact">
            <table>
              <thead>
                <tr>
                  <th>Snippet</th>
                  <th>Detector</th>
                  <th>Prediction</th>
                  <th>Correct?</th>
                  <th>Confidence</th>
                  <th>Runtime</th>
                </tr>
              </thead>

              <tbody>
                {predictions.map((p, index) => {
                  const correct = isPredictionCorrect(p);

                  return (
                    <tr key={`${p.snippet_id}-${p.detector_id}-${index}`}>
                      <td>
                        <Link
                          to={`/runs/${summary.run_id}/snippets/${p.snippet_id}?dataset=${summary.dataset_id}`}
                        >
                          {p.snippet_id}
                        </Link>
                      </td>

                      <td>{p.detector_id}</td>

                      <td>
                        <span
                          className={
                            p.predicted_vulnerable
                              ? "pill danger"
                              : "pill safe"
                          }
                        >
                          {p.predicted_vulnerable ? "vulnerable" : "safe"}
                        </span>
                      </td>

                      <td>
                        {correct === null ? (
                          <span className="pill neutral">unknown</span>
                        ) : correct ? (
                          <span className="pill safe">correct</span>
                        ) : (
                          <span className="pill danger">wrong</span>
                        )}
                      </td>

                      <td>
                        {p.confidence === null || p.confidence === undefined
                          ? "-"
                          : p.confidence.toFixed(3)}
                      </td>

                      <td>{p.runtime_ms} ms</td>
                    </tr>
                  );
                })}
              </tbody>
            </table>
          </div>
        )}
      </div>
    </div>
  );
}