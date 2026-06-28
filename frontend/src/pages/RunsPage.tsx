import { useEffect, useState } from "react";
import { Link } from "react-router-dom";
import { api } from "../api/client";
import type { RunListItem } from "../types";

export function RunsPage() {
  const [runs, setRuns] = useState<RunListItem[]>([]);
  const [query, setQuery] = useState("");

  useEffect(() => {
    api.runs().then(setRuns);
  }, []);

  const filtered = runs.filter((run) =>
    `${run.id} ${run.dataset_id} ${run.status} ${run.detectors?.join(" ")}`
      .toLowerCase()
      .includes(query.toLowerCase())
  );

  return (
    <div className="page">
      <div className="page-header">
        <div>
          <h1>Runs</h1>
          <p>Evaluation runs created from the CLI.</p>
        </div>
      </div>

      <input
        className="search"
        placeholder="Search run id"
        value={query}
        onChange={(e) => setQuery(e.target.value)}
      />

      <div className="panel">
        <div className="table-wrap">
          <table>
            <thead>
              <tr>
                <th>Run ID</th>
                <th>Dataset</th>
                <th>Status</th>
                <th>Detectors</th>
                <th>Snippets</th>
              </tr>
            </thead>
            <tbody>
              {filtered.map((run) => (
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
                  <td>{run.detectors?.join(", ")}</td>
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