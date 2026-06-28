import { useEffect, useMemo, useState } from "react";
import { Link, useParams } from "react-router-dom";
import { api } from "../api/client";
import { MetricCard } from "../components/MetricCard";
import type { Dataset, Snippet } from "../types";

function SnippetRow({
  datasetId,
  snippet,
}: {
  datasetId: string;
  snippet: Snippet;
}) {
  return (
    <Link
      className="snippet-row"
      to={`/datasets/${datasetId}/snippets/${snippet.id}`}
    >
      <div>
        <strong>{snippet.id}</strong>
        <span>{snippet.file_path}</span>
      </div>

      <span className="tag">{snippet.vulnerability_type}</span>
    </Link>
  );
}

export function DatasetDetailPage() {
  const { datasetId } = useParams();

  const [dataset, setDataset] = useState<Dataset | null>(null);

  useEffect(() => {
    if (!datasetId) return;

    api.dataset(datasetId).then(setDataset).catch(console.error);
  }, [datasetId]);

  const safeSnippets = useMemo(
    () => dataset?.snippets.filter((snippet) => !snippet.is_vulnerable) ?? [],
    [dataset]
  );

  const vulnerableSnippets = useMemo(
    () => dataset?.snippets.filter((snippet) => snippet.is_vulnerable) ?? [],
    [dataset]
  );

  if (!dataset) {
    return <div className="page">Loading dataset</div>;
  }

  return (
    <div className="page">
      <div className="page-header">
        <div>
          <h1>{dataset.name}</h1>
          <p>
            Dataset ID: <strong>{dataset.id}</strong>
          </p>
        </div>

        <Link className="button small" to="/datasets">
          Back to datasets
        </Link>
      </div>

      <div className="metric-grid">
        <MetricCard label="Total snippets" value={dataset.snippets.length} />

        <MetricCard label="Safe" value={safeSnippets.length} />

        <MetricCard label="Vulnerable" value={vulnerableSnippets.length} />

        <MetricCard label="Language" value={dataset.language} />
      </div>

      <div className="panel">
        <div className="panel-header">
          <div>
            <h2>Snippets</h2>
            <span>Safe and vulnerable examples in this dataset</span>
          </div>
        </div>

        <div className="snippet-columns">
          <div>
            <div className="snippet-column-header safe-header">
              <h3>Safe</h3>
              <span>{safeSnippets.length}</span>
            </div>

            <div className="snippet-list">
              {safeSnippets.length ? (
                safeSnippets.map((snippet) => (
                  <SnippetRow
                    key={snippet.id}
                    datasetId={dataset.id}
                    snippet={snippet}
                  />
                ))
              ) : (
                <p className="muted">No safe snippets</p>
              )}
            </div>
          </div>

          <div>
            <div className="snippet-column-header danger-header">
              <h3>Vulnerable</h3>
              <span>{vulnerableSnippets.length}</span>
            </div>

            <div className="snippet-list">
              {vulnerableSnippets.length ? (
                vulnerableSnippets.map((snippet) => (
                  <SnippetRow
                    key={snippet.id}
                    datasetId={dataset.id}
                    snippet={snippet}
                  />
                ))
              ) : (
                <p className="muted">No vulnerable snippets</p>
              )}
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}