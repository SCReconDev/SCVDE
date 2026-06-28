import { useEffect, useState } from "react";
import { Link, useParams } from "react-router-dom";
import { api } from "../api/client";
import { CodeBlock } from "../components/CodeBlock";
import type { SnippetResponse } from "../types";

export function DatasetSnippetPage() {
  const { datasetId, snippetId } = useParams();

  const [snippetData, setSnippetData] = useState<SnippetResponse | null>(null);

  useEffect(() => {
    if (!datasetId || !snippetId) return;

    api.snippet(datasetId, snippetId).then(setSnippetData).catch(console.error);
  }, [datasetId, snippetId]);

  if (!snippetData) {
    return <div className="page">Loading snippet</div>;
  }

  const { snippet, code } = snippetData;

  return (
    <div className="page">
      <div className="page-header">
        <div>
          <h1>{snippet.id}</h1>
          <p>
            Dataset: <strong>{snippetData.dataset_id}</strong>
          </p>
        </div>

        <Link className="button small" to={`/datasets/${snippetData.dataset_id}`}>
          Back to dataset
        </Link>
      </div>

      <div className="metric-grid">
        <div className="metric-card">
          <span>Label</span>
          <strong>
            <span className={snippet.is_vulnerable ? "pill danger" : "pill safe"}>
              {snippet.is_vulnerable ? "Vulnerable" : "Safe"}
            </span>
          </strong>
        </div>

        <div className="metric-card">
          <span>Language</span>
          <strong>{snippet.language}</strong>
        </div>

        <div className="metric-card">
          <span>Vulnerability type</span>
          <strong>{snippet.vulnerability_type}</strong>
        </div>

        <div className="metric-card">
          <span>CWE</span>
          <strong>{snippet.cwe ?? "-"}</strong>
        </div>
      </div>

      <div className="panel">
        <div className="panel-header">
          <div>
            <h2>Source code</h2>
            <span>{snippet.file_path}</span>
          </div>
        </div>

        <CodeBlock code={code} />
      </div>
    </div>
  );
}