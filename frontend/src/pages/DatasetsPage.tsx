import { useEffect, useMemo, useState } from "react";
import { Link } from "react-router-dom";
import { api } from "../api/client";
import type { Dataset, DatasetSummary } from "../types";

type DatasetCardData = DatasetSummary & {
  num_safe: number;
  num_vulnerable: number;
};

function countDataset(dataset: Dataset): DatasetCardData {
  const numVulnerable = dataset.snippets.filter((s) => s.is_vulnerable).length;
  const numSafe = dataset.snippets.length - numVulnerable;

  return {
    id: dataset.id,
    name: dataset.name,
    language: dataset.language,
    vulnerability_types: dataset.vulnerability_types,
    num_snippets: dataset.snippets.length,
    num_safe: numSafe,
    num_vulnerable: numVulnerable,
  };
}

export function DatasetsPage() {
  const [datasets, setDatasets] = useState<DatasetCardData[]>([]);
  const [query, setQuery] = useState("");

  useEffect(() => {
    api
      .datasets()
      .then(async (summaries) => {
        const detailedDatasets = await Promise.all(
          summaries.map(async (summary) => {
            try {
              const dataset = await api.dataset(summary.id);
              return countDataset(dataset);
            } catch {
              return {
                ...summary,
                num_safe: 0,
                num_vulnerable: 0,
              };
            }
          })
        );

        setDatasets(detailedDatasets);
      })
      .catch(console.error);
  }, []);

  const filtered = useMemo(
    () =>
      datasets.filter((dataset) =>
        `${dataset.id} ${dataset.name ?? ""} ${dataset.language ?? ""} ${
          dataset.vulnerability_types?.join(" ") ?? ""
        }`
          .toLowerCase()
          .includes(query.toLowerCase())
      ),
    [datasets, query]
  );

  return (
    <div className="page">
      <div className="page-header">
        <div>
          <h1>Datasets</h1>
          <p>Generated and manual datasets</p>
        </div>
      </div>

      <input
        className="search"
        placeholder="Search datasets"
        value={query}
        onChange={(e) => setQuery(e.target.value)}
      />

      <div className="card-grid">
        {filtered.map((dataset) => (
          <Link
            to={`/datasets/${dataset.id}`}
            className="dataset-card dataset-card-link"
            key={dataset.id}
          >
            <div className="card-title">{dataset.name ?? dataset.id}</div>
            <div className="card-subtitle">{dataset.id}</div>

            <div className="tag-row">
              {dataset.language && (
                <span className="tag">{dataset.language}</span>
              )}

              {dataset.vulnerability_types?.map((vulnerabilityType) => (
                <span className="tag" key={vulnerabilityType}>
                  {vulnerabilityType}
                </span>
              ))}
            </div>

            <div className="dataset-count-grid">
              <div>
                <strong>{dataset.num_snippets ?? 0}</strong>
                <span>Total</span>
              </div>

              <div>
                <strong>{dataset.num_safe ?? 0}</strong>
                <span>Safe</span>
              </div>

              <div>
                <strong>{dataset.num_vulnerable ?? 0}</strong>
                <span>Vulnerable</span>
              </div>
            </div>

            {dataset.error && <div className="alert">{dataset.error}</div>}
          </Link>
        ))}
      </div>
    </div>
  );
}