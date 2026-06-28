import { useEffect, useState } from "react";
import { api } from "../api/client";

type Detector = {
  id: string;
  type: string;
  name?: string;
  backend?: string;
  error?: string;
};

export function DetectorsPage() {
  const [detectors, setDetectors] = useState<Detector[]>([]);

  useEffect(() => {
    api.detectors().then(setDetectors);
  }, []);

  return (
    <div className="page">
      <div className="page-header">
        <div>
          <h1>Detectors</h1>
          <p>Available static analysis, and model based detectors.</p>
        </div>
      </div>

      <div className="card-grid">
        {detectors.map((detector) => (
          <div className="dataset-card" key={detector.id}>
            <div className="card-title">{detector.name ?? detector.id}</div>
            <div className="card-subtitle">{detector.id}</div>

            <div className="tag-row">
              <span className="tag">{detector.type}</span>
              {detector.backend && <span className="tag">{detector.backend}</span>}
            </div>

            {detector.error && <div className="alert">{detector.error}</div>}
          </div>
        ))}
      </div>
    </div>
  );
}