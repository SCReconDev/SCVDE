import { useEffect, useMemo, useState } from "react";
import { Link } from "react-router-dom";
import { api } from "../api/client";
import { MetricCard } from "../components/MetricCard";
import type { DatasetSummary, RunListItem } from "../types";

export function DashboardPage() {
  const [datasets, setDatasets] = useState<DatasetSummary[]>([]);
  const [runs, setRuns] = useState<RunListItem[]>([]);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    Promise.all([api.datasets(), api.runs()])
      .then(([datasetsData, runsData]) => {
        setDatasets(datasetsData);
        setRuns(runsData);
      })
      .catch((err) => setError(err.message));
  }, []);

  const latestRun = runs[0];

  const totalSnippets = useMemo(
    () => datasets.reduce((sum, d) => sum + (d.num_snippets ?? 0), 0),
    [datasets]
  );

  return (
    <div className="page">
      <div className="page-header">
        <div>
          <h1>Dashboard</h1>
          <p>Overview of datasets and evaluation runs.</p>
        </div>
      </div>

      {error && <div className="alert">{error}</div>}

      <div className="metric-grid">
        <MetricCard label="Datasets" value={datasets.length} />
        <MetricCard label="Total snippets" value={totalSnippets} />
        <MetricCard label="Runs" value={runs.length} />
        <MetricCard
          label="Latest run"
          value={latestRun?.status ?? "None"}
          hint={latestRun?.id}
        />
      </div>

      <div className="panel">
        <div className="panel-header">
          <h2>Recent runs</h2>
          <Link className="button" to="/runs">
            View all
          </Link>
        </div>

        <div className="table-wrap">
          <table>
            <thead>
              <tr>
                <th>Run</th>
                <th>Dataset</th>
                <th>Status</th>
                <th>Snippets</th>
              </tr>
            </thead>
            <tbody>
              {runs.slice(0, 5).map((run) => (
                <tr key={run.id}>
                  <td>
                    <Link to={`/runs/${run.id}`}>{run.id}</Link>
                  </td>
                  <td>{run.dataset_id}</td>
                  <td>
                    <span className={`status status-${run.status}`}>
                      {run.status}
                    </span>
                  </td>
                  <td>{run.num_snippets ?? "-"}</td>
                </tr>
              ))}
            </tbody>
          </table>
        </div>
      </div>
    </div>
  );
}