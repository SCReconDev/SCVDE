import subprocess
import time
import xml.etree.ElementTree as ET
from pathlib import Path

from app.detectors.base import BaseDetector, DetectorPrediction


class CppcheckAdapter(BaseDetector):
    detector_id = "cppcheck"
    detector_type = "static_analyzer"

    def predict(self, snippet_id: str, code: str, file_path: str) -> DetectorPrediction:
        start = time.perf_counter()

        path = Path(file_path)
        if not path.exists():
            raise FileNotFoundError(f"Snippet file not found: {file_path}")

        cmd = [
            "cppcheck",
            "--enable=all",
            "--inconclusive",
            "--xml",
            "--xml-version=2",
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
                "Cppcheck is not installe or not available on PATH . "
            ) from exc

        runtime_ms = int((time.perf_counter() - start) * 1000)

        findings = []
        predicted_lines: set[int] = set()

        xml_text = result.stderr.strip()

        try:
            root = ET.fromstring(xml_text)
            for error in root.findall(".//error"):
                finding = {
                    "id": error.get("id"),
                    "severity": error.get("severity"),
                    "message": error.get("msg"),
                    "verbose": error.get("verbose"),
                    "locations": [],
                }

                for location in error.findall("location"):
                    line_value = location.get("line")

                    location_data = {
                        "file": location.get("file"),
                        "line": line_value,
                    }

                    finding["locations"].append(location_data)

                    if line_value is not None:
                        try:
                            predicted_lines.add(int(line_value))
                        except ValueError:
                            pass

                findings.append(finding)

        except ET.ParseError:
            findings = []

        predicted_vulnerable = len(findings) > 0

        rule_ids = [
            finding["id"]
            for finding in findings
            if finding.get("id")
        ]

        severities = [
            finding["severity"]
            for finding in findings
            if finding.get("severity")
        ]

        return DetectorPrediction(
            snippet_id=snippet_id,
            detector_id=self.detector_id,
            detector_type=self.detector_type,
            predicted_vulnerable=predicted_vulnerable,
            predicted_vulnerability_type="cpp_static_issue"
            if predicted_vulnerable
            else None,
            confidence=None,
            predicted_lines=sorted(predicted_lines),
            runtime_ms=runtime_ms,
            raw_output={
                "returncode": result.returncode,
                "num_findings": len(findings),
                "rule_ids": rule_ids,
                "severities": severities,
                "stdout": result.stdout,
                "stderr": result.stderr,
                "findings": findings,
            },
        )