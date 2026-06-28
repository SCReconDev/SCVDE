import re
import subprocess
import time
from pathlib import Path

from app.detectors.base import BaseDetector, DetectorPrediction


class ClangTidySecurityAdapter(BaseDetector):
    detector_id = "clang_tidy_security"
    detector_type = "static_analyzer"

    SUPPORTED_EXTENSIONS = {
        ".c",
        ".h",
        ".cc",
        ".cpp",
        ".cxx",
        ".hpp",
    }

    CHECKS = "clang-analyzer-*,cert-*,bugprone-*"

    FINDING_PATTERN = re.compile(
        r"^(?P<file>.*?):(?P<line>\d+):(?P<column>\d+): "
        r"(?P<severity>warning|error|note): "
        r"(?P<message>.*?)(?: \[(?P<check>[^\]]+)\])?$"
    )

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

        suffix = path.suffix.lower()

        if suffix not in self.SUPPORTED_EXTENSIONS:
            raise ValueError(
                "Clang-Tidy only supports C/C++ files. "
                f"Received extension: {suffix}"
            )

        standard = "c11" if suffix in {".c", ".h"} else "c++17"

        command = [
            "clang-tidy",
            str(path),
            f"--checks={self.CHECKS}",
            "--quiet",
            "--",
            f"-std={standard}",
        ]

        try:
            result = subprocess.run(
                command,
                capture_output=True,
                text=True,
                timeout=90,
            )
        except FileNotFoundError as exc:
            raise RuntimeError(
                "clang tidy is not installed or not available on PATH. "
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
                    "error": "clang_tidy_timeout",
                    "timeout_seconds": 90,
                    "command": command,
                },
            )

        runtime_ms = int((time.perf_counter() - start) * 1000)

        combined_output = "\n".join(
            part for part in [result.stdout, result.stderr] if part
        )

        findings = self._parse_findings(
            output=combined_output,
            snippet_path=path,
        )

        predicted_lines = sorted(
            {
                finding["line"]
                for finding in findings
                if finding.get("line") is not None
            }
        )

        check_ids = sorted(
            {
                finding["check"]
                for finding in findings
                if finding.get("check")
            }
        )

        messages = [
            finding["message"]
            for finding in findings
            if finding.get("message")
        ]

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
                "check_ids": check_ids,
                "messages": messages,
                "findings": findings,
                "stdout": result.stdout,
                "stderr": result.stderr,
                "command": command,
                "checks": self.CHECKS,
            },
        )

    def _parse_findings(
        self,
        output: str,
        snippet_path: Path,
    ) -> list[dict]:
        findings: list[dict] = []
        seen: set[tuple[str, int, int, str, str | None]] = set()

        expected_path = str(snippet_path.resolve())

        for raw_line in output.splitlines():
            line = raw_line.strip()
            match = self.FINDING_PATTERN.match(line)

            if not match:
                continue

            file_value = match.group("file")

            try:
                resolved_file = str(Path(file_value).resolve())
            except OSError:
                resolved_file = file_value

            if resolved_file != expected_path:
                continue

            severity = match.group("severity")

            if severity == "note":
                continue

            line_number = int(match.group("line"))
            column_number = int(match.group("column"))
            message = match.group("message").strip()
            check_id = match.group("check")

            finding_key = (
                resolved_file,
                line_number,
                column_number,
                message,
                check_id,
            )

            if finding_key in seen:
                continue

            seen.add(finding_key)

            findings.append(
                {
                    "file": file_value,
                    "line": line_number,
                    "column": column_number,
                    "severity": severity,
                    "message": message,
                    "check": check_id,
                }
            )

        return findings