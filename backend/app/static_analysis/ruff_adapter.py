import json
import subprocess
import time
from pathlib import Path

from app.detectors.base import BaseDetector, DetectorPrediction


class RuffSecurityAdapter(BaseDetector):
    detector_id = "ruff_security"
    detector_type = "static_analyzer"

    def predict(self, snippet_id: str, code: str, file_path: str) -> DetectorPrediction:
        start = time.perf_counter()

        path = Path(file_path)
        if not path.exists():
            raise FileNotFoundError(f"Snippet file not found: {file_path}")

        cmd = [
            "ruff",
            "check",
            "--select",
            "S",
            "--output-format",
            "json",
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
                "Ruff is not installed or not available on PATH. "
            ) from exc

        runtime_ms = int((time.perf_counter() - start) * 1000)

        raw_findings = []

        if result.stdout.strip():
            try:
                parsed_output = json.loads(result.stdout)
                if isinstance(parsed_output, list):
                    raw_findings = parsed_output
            except json.JSONDecodeError:
                parsed_output = {
                    "parse_error": "Ruff did not return valid JSON",
                    "stdout": result.stdout,
                    "stderr": result.stderr,
                    "returncode": result.returncode,
                }
        else:
            parsed_output = []

        predicted_lines = sorted(
            {
                finding.get("location", {}).get("row")
                for finding in raw_findings
                if finding.get("location", {}).get("row") is not None
            }
        )

        rule_ids = [
            finding.get("code")
            for finding in raw_findings
            if finding.get("code")
        ]

        messages = [
            finding.get("message")
            for finding in raw_findings
            if finding.get("message")
        ]

        predicted_vulnerable = len(raw_findings) > 0

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
                "num_findings": len(raw_findings),
                "rule_ids": rule_ids,
                "messages": messages,
                "stderr": result.stderr,
                "ruff_output": parsed_output,
            },
        )