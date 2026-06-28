import { useMemo, useState } from "react";
import {
  Bar,
  BarChart,
  CartesianGrid,
  Cell,
  LabelList,
  ResponsiveContainer,
  Tooltip,
  XAxis,
  YAxis,
} from "recharts";
import type { DetectorMetric } from "../types";

type Props = {
  metrics: DetectorMetric[];
};

type MetricKey = "f1" | "accuracy" | "precision" | "recall";

const METRIC_OPTIONS: { key: MetricKey; label: string }[] = [
  { key: "f1", label: "F1 score" },
  { key: "accuracy", label: "Accuracy" },
  { key: "precision", label: "Precision" },
  { key: "recall", label: "Recall" },
];

const DETECTOR_COLORS = [
  "#38bdf8",
  "#818cf8",
  "#34d399",
  "#fbbf24",
  "#fb7185",
  "#a78bfa",
  "#2dd4bf",
  "#f97316",
  "#60a5fa",
  "#f472b6",
  "#22c55e",
  "#e879f9",
  "#14b8a6",
  "#facc15",
  "#c084fc",
];

function shortName(name: string): string {
  return name
    .replace("dummy_", "")
    .replace("_demo_", "_")
    .replace(/_/g, " ");
}

function buildDetectorColorMap(detectorIds: string[]): Record<string, string> {
  const sortedIds = [...new Set(detectorIds)].sort();

  return Object.fromEntries(
    sortedIds.map((id, index) => [
      id,
      DETECTOR_COLORS[index % DETECTOR_COLORS.length],
    ])
  );
}

function formatScore(value: unknown): string {
  const numberValue = Number(value);
  return Number.isFinite(numberValue) ? numberValue.toFixed(2) : "";
}

export function MetricsChart({ metrics }: Props) {
  const [selectedMetric, setSelectedMetric] = useState<MetricKey>("f1");

  const selectedLabel =
    METRIC_OPTIONS.find((option) => option.key === selectedMetric)?.label ??
    "Metric";

  const data = useMemo(() => {
    const colorMap = buildDetectorColorMap(metrics.map((m) => m.detector_id));

    return [...metrics]
      .sort((a, b) => b[selectedMetric] - a[selectedMetric])
      .map((m) => ({
        detector_id: m.detector_id,
        detector: shortName(m.detector_id),
        value: Number(m[selectedMetric].toFixed(4)),
        color: colorMap[m.detector_id],
        f1: m.f1,
        accuracy: m.accuracy,
        precision: m.precision,
        recall: m.recall,
      }));
  }, [metrics, selectedMetric]);

  if (data.length === 0) {
    return (
      <div className="panel">
        <div className="panel-header">
          <h2>Detector ranking</h2>
        </div>
        <p className="muted">No metrics available.</p>
      </div>
    );
  }

  return (
    <div className="panel chart-panel">
      <div className="panel-header">
        <div>
          <h2>Detector ranking</h2>
          <span>Ranked by {selectedLabel.toLowerCase()}</span>
        </div>

        <select
          className="select metric-select"
          value={selectedMetric}
          onChange={(event) => setSelectedMetric(event.target.value as MetricKey)}
        >
          {METRIC_OPTIONS.map((option) => (
            <option key={option.key} value={option.key}>
              {option.label}
            </option>
          ))}
        </select>
      </div>

      <div className="rank-chart-wrap">
        <ResponsiveContainer width="100%" height={Math.max(260, data.length * 54)}>
          <BarChart
            data={data}
            layout="vertical"
            margin={{ top: 8, right: 56, bottom: 8, left: 24 }}
          >
            <CartesianGrid horizontal={false} strokeDasharray="3 3" />

            <XAxis
              type="number"
              domain={[0, 1]}
              tickFormatter={(value) => Number(value).toFixed(1)}
              axisLine={false}
              tickLine={false}
            />

            <YAxis
              type="category"
              dataKey="detector"
              width={180}
              axisLine={false}
              tickLine={false}
            />

            <Tooltip
              cursor={{ fill: "rgba(255,255,255,0.08)" }}
              formatter={(value) => [formatScore(value), selectedLabel]}
              labelFormatter={(_, payload) => {
                const item = payload?.[0]?.payload;
                return item?.detector_id ?? "";
              }}
              contentStyle={{
                background: "#020617",
                border: "1px solid rgba(148, 163, 184, 0.35)",
                borderRadius: "14px",
                color: "#e5e7eb",
                boxShadow: "0 18px 50px rgba(0,0,0,0.45)",
              }}
              itemStyle={{
                color: "#e5e7eb",
              }}
              labelStyle={{
                color: "#f8fafc",
                fontWeight: 800,
                marginBottom: "6px",
              }}
            />

            <Bar dataKey="value" name={selectedLabel} radius={[0, 12, 12, 0]}>
              {data.map((entry) => (
                <Cell key={entry.detector_id} fill={entry.color} />
              ))}

              <LabelList
                dataKey="value"
                position="right"
                formatter={(value) => formatScore(value)}
              />
            </Bar>
          </BarChart>
        </ResponsiveContainer>
      </div>
    </div>
  );
}