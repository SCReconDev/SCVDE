import csv
import io
import subprocess
import time
from pathlib import Path

from app.detectors.base import BaseDetector, DetectorPrediction


class FlawfinderAdapter(BaseDetector):
    detector_id = "flawfinder"
    detector_type = "static_analyzer"

    SUPPORTED_EXTENSIONS = {
        ".c",
        ".h",
        ".cc",
        ".cpp",
        ".cxx",
        ".hpp",
    }

    def predict(
        self,
        snippet_id: str,
        code: str,
        file_path: str,
    ) -> DetectorPrediction:
        start = time.perf_counter()

        path = Path(file_path)

        if not path.exists():
            raise FileNotFoundError(f"Snippet file not found: {file_path}")

        if path.suffix.lower() not in self.SUPPORTED_EXTENSIONS:
            raise ValueError(
                f"Flawfinder only supports C/C++ files. "
                f"Received extension: {path.suffix}"
            )

        command = [
            "flawfinder",
            "--csv",
            "--quiet",
            str(path),
        ]

        try:
            result = subprocess.run(
                command,
                capture_output=True,
                text=True,
                timeout=45,
            )
        except FileNotFoundError as exc:
            raise RuntimeError(
                "Flawfinder is not installed or is not available on PATH. "
            ) from exc
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
                    "error": "flawfinder_timeout",
                    "timeout_seconds": 45,
                    "command": command,
                },
            )

        runtime_ms = int((time.perf_counter() - start) * 1000)

        findings = self._parse_csv(result.stdout)

        predicted_lines = sorted(
            {
                finding["line"]
                for finding in findings
                if finding.get("line") is not None
            }
        )

        rule_ids = [
            finding["name"]
            for finding in findings
            if finding.get("name")
        ]

        cwes = sorted(
            {
                finding["cwe"]
                for finding in findings
                if finding.get("cwe")
            }
        )

        predicted_vulnerable = len(findings) > 0

        return DetectorPrediction(
            snippet_id=snippet_id,
            detector_id=self.detector_id,
            detector_type=self.detector_type,
            predicted_vulnerable=predicted_vulnerable,
            predicted_vulnerability_type=(
                "c_cpp_security_issue" if predicted_vulnerable else None
            ),
            confidence=None,
            predicted_lines=predicted_lines,
            runtime_ms=runtime_ms,
            raw_output={
                "returncode": result.returncode,
                "num_findings": len(findings),
                "rule_ids": rule_ids,
                "cwes": cwes,
                "findings": findings,
                "stdout": result.stdout,
                "stderr": result.stderr,
                "command": command,
            },
        )

    def _parse_csv(self, csv_text: str) -> list[dict]:
        if not csv_text.strip():
            return []

        findings: list[dict] = []
        reader = csv.DictReader(io.StringIO(csv_text))

        for row in reader:
            line_value = self._to_int(
                row.get("Line")
                or row.get("line")
                or row.get("Line number")
            )

            level_value = self._to_int(
                row.get("Level")
                or row.get("level")
                or row.get("Risk")
            )

            findings.append(
                {
                    "file": (
                        row.get("File")
                        or row.get("file")
                        or row.get("Filename")
                    ),
                    "line": line_value,
                    "column": self._to_int(
                        row.get("Column") or row.get("column")
                    ),
                    "level": level_value,
                    "name": (
                        row.get("Name")
                        or row.get("name")
                        or row.get("Function")
                    ),
                    "category": (
                        row.get("Category")
                        or row.get("category")
                    ),
                    "warning": (
                        row.get("Warning")
                        or row.get("warning")
                        or row.get("Message")
                    ),
                    "suggestion": (
                        row.get("Suggestion")
                        or row.get("suggestion")
                    ),
                    "cwe": (
                        row.get("CWEs")
                        or row.get("CWE")
                        or row.get("cwe")
                    ),
                    "raw": dict(row),
                }
            )

        return findings

    @staticmethod
    def _to_int(value: str | None) -> int | None:
        if value is None:
            return None

        try:
            return int(value)
        except (TypeError, ValueError):
            return None