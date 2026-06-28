import json
import subprocess
import time
from pathlib import Path

from app.detectors.base import BaseDetector, DetectorPrediction


class BanditAdapter(BaseDetector):
    detector_id = "bandit"
    detector_type = "static_analyzer"

    def predict(self, snippet_id: str, code: str, file_path: str) -> DetectorPrediction:
        start = time.perf_counter()

        path = Path(file_path)
        if not path.exists():
            raise FileNotFoundError(f"Snippet file not found: {file_path}")

        cmd = [
            "bandit",
            "-f",
            "json",
            "-q",
            str(path),
        ]

        try:
            result = subprocess.run(
                cmd,
                capture_output=True,
                text=True,
                timeout=45,
            )
        except FileNotFoundError as exc:
            raise RuntimeError(
                "Bandit is not installed or not available on PATH. "
                "Install it with pipx install bandit"
            ) from exc

        runtime_ms = int((time.perf_counter() - start) * 1000)

        if result.stdout.strip():
            try:
                raw_output = json.loads(result.stdout)
            except json.JSONDecodeError:
                raw_output = {
                    "parse_error": "Bandit did not return valid JSON",
                    "stdout": result.stdout,
                    "stderr": result.stderr,
                    "returncode": result.returncode,
                }
        else:
            raw_output = {
                "stdout": result.stdout,
                "stderr": result.stderr,
                "returncode": result.returncode,
            }

        findings = raw_output.get("results", []) if isinstance(raw_output, dict) else []

        predicted_lines = sorted(
            {
                finding.get("line_number")
                for finding in findings
                if finding.get("line_number") is not None
            }
        )

        test_ids = [
            finding.get("test_id")
            for finding in findings
            if finding.get("test_id")
        ]

        severities = [
            finding.get("issue_severity")
            for finding in findings
            if finding.get("issue_severity")
        ]

        predicted_vulnerable = len(findings) > 0

        return DetectorPrediction(
            snippet_id=snippet_id,
            detector_id=self.detector_id,
            detector_type=self.detector_type,
            predicted_vulnerable=predicted_vulnerable,
            predicted_vulnerability_type="python_security_issue"
            if predicted_vulnerable
            else None,
            confidence=None,
            predicted_lines=predicted_lines,
            runtime_ms=runtime_ms,
            raw_output={
                "returncode": result.returncode,
                "num_findings": len(findings),
                "test_ids": test_ids,
                "severities": severities,
                "stderr": result.stderr,
                "bandit_output": raw_output,
            },
        )