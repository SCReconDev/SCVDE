import json
import subprocess
import time
from pathlib import Path

from app.detectors.base import BaseDetector, DetectorPrediction


class SemgrepAdapter(BaseDetector):
    detector_id = "semgrep"
    detector_type = "static_analyzer"

    def predict(self, snippet_id: str, code: str, file_path: str) -> DetectorPrediction:
        start = time.perf_counter()

        path = Path(file_path)

        if not path.exists():
            raise FileNotFoundError(f"Snippet file not found: {file_path}")

        cmd = [
            "semgrep",
            "--config",
            "auto",
            "--json",
            "--quiet",
            str(path),
        ]

        try:
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=30,
            )

            runtime_ms = int((time.perf_counter() - start) * 1000)

            if result.stdout.strip():
                raw_output = json.loads(result.stdout)
            else:
                raw_output = {}

            findings = raw_output.get("results", [])

            predicted_vulnerable = len(findings) > 0

            predicted_lines = sorted(
                {
                    finding.get("start", {}).get("line")
                    for finding in findings
                    if finding.get("start", {}).get("line") is not None
                }
            )

            rule_ids = [
                finding.get("check_id")
                for finding in findings
                if finding.get("check_id")
            ]

            return DetectorPrediction(
                snippet_id=snippet_id,
                detector_id=self.detector_id,
                detector_type=self.detector_type,
                predicted_vulnerable=predicted_vulnerable,
                predicted_vulnerability_type="unknown" if predicted_vulnerable else None,
                confidence=None,
                predicted_lines=predicted_lines,
                runtime_ms=runtime_ms,
                raw_output={
                    "returncode": result.returncode,
                    "rule_ids": rule_ids,
                    "num_findings": len(findings),
                    "stderr": result.stderr,
                    "semgrep_output": raw_output,
                },
            )

        except subprocess.TimeoutExpired:
            runtime_ms = int((time.perf_counter() - start) * 1000)

            return DetectorPrediction(
                snippet_id=snippet_id,
                detector_id=self.detector_id,
                detector_type=self.detector_type,
                predicted_vulnerable=False,
                predicted_vulnerability_type=None,
                confidence=None,
                predicted_lines=[],
                runtime_ms=runtime_ms,
                raw_output={
                    "error": "semgrep_timeout",
                    "timeout_seconds": 30,
                },
            )