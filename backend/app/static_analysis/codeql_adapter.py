import json
import shutil
import subprocess
import tempfile
import time
from pathlib import Path

from app.detectors.base import BaseDetector, DetectorPrediction


class CodeQLAdapter(BaseDetector):
    detector_id = "codeql"
    detector_type = "static_analyzer"

    LANGUAGE_MAP = {
        ".py": "python",
        ".js": "javascript",
        ".jsx": "javascript",
        ".ts": "javascript",
        ".tsx": "javascript",
        ".java": "java",
        ".c": "cpp",
        ".h": "cpp",
        ".cpp": "cpp",
        ".cc": "cpp",
        ".cxx": "cpp",
        ".hpp": "cpp",
        ".cs": "csharp",
        ".go": "go",
        ".rb": "ruby",
    }

    QUERY_SUITES = {
        "python": "python-security-and-quality.qls",
        "javascript": "javascript-security-and-quality.qls",
        "java": "java-security-and-quality.qls",
        "cpp": "cpp-security-and-quality.qls",
        "csharp": "csharp-security-and-quality.qls",
        "go": "go-security-and-quality.qls",
        "ruby": "ruby-security-and-quality.qls",
    }

    def predict(self, snippet_id: str, code: str, file_path: str) -> DetectorPrediction:
        start = time.perf_counter()

        original_path = Path(file_path)
        if not original_path.exists():
            raise FileNotFoundError(f"Snippet file not found: {file_path}")

        language = self._language_from_path(original_path)
        query_suite_name = self.QUERY_SUITES.get(language)

        if query_suite_name is None:
            raise ValueError(
                f"CodeQL does not support this file extension in the adapter: "
                f"{original_path.suffix}"
            )

        try:
            query_suite = self._resolve_query_suite(language, query_suite_name)

            with tempfile.TemporaryDirectory(prefix="scvde_codeql_") as temp_dir:
                temp_root = Path(temp_dir)
                source_root = temp_root / "src"
                database_dir = temp_root / "codeql-db"
                sarif_path = temp_root / "results.sarif"

                source_root.mkdir(parents=True, exist_ok=True)

                snippet_path = source_root / original_path.name
                snippet_path.write_text(code, encoding="utf-8")

                create_cmd = [
                    "codeql",
                    "database",
                    "create",
                    str(database_dir),
                    "--language",
                    language,
                    "--source-root",
                    str(source_root),
                    "--overwrite",
                ]

                if language in {"cpp", "java", "csharp", "go"}:
                    create_cmd.extend(["--command", self._build_command(language)])

                create_result = subprocess.run(
                    create_cmd,
                    capture_output=True,
                    text=True,
                    timeout=120,
                )

                if create_result.returncode != 0:
                    runtime_ms = int((time.perf_counter() - start) * 1000)
                    return self._error_prediction(
                        snippet_id=snippet_id,
                        runtime_ms=runtime_ms,
                        error_type="database_create_failed",
                        command=create_cmd,
                        result=create_result,
                    )

                analyze_cmd = [
                    "codeql",
                    "database",
                    "analyze",
                    str(database_dir),
                    query_suite,
                    "--format",
                    "sarifv2.1.0",
                    "--output",
                    str(sarif_path),
                    "--threads",
                    "0",
                ]

                analyze_result = subprocess.run(
                    analyze_cmd,
                    capture_output=True,
                    text=True,
                    timeout=180,
                )

                if analyze_result.returncode != 0:
                    runtime_ms = int((time.perf_counter() - start) * 1000)
                    return self._error_prediction(
                        snippet_id=snippet_id,
                        runtime_ms=runtime_ms,
                        error_type="database_analyze_failed",
                        command=analyze_cmd,
                        result=analyze_result,
                    )

                sarif = json.loads(sarif_path.read_text(encoding="utf-8"))

        except FileNotFoundError as exc:
            raise RuntimeError(
                "CodeQL CLI or CodeQL query suites are not available. "
            ) from exc

        runtime_ms = int((time.perf_counter() - start) * 1000)

        findings = self._extract_findings(sarif, original_path.name)

        predicted_lines = sorted(
            {
                finding["line"]
                for finding in findings
                if finding.get("line") is not None
            }
        )

        rule_ids = [
            finding["rule_id"]
            for finding in findings
            if finding.get("rule_id")
        ]

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
            predicted_vulnerability_type="codeql_security_issue"
            if predicted_vulnerable
            else None,
            confidence=None,
            predicted_lines=predicted_lines,
            runtime_ms=runtime_ms,
            raw_output={
                "num_findings": len(findings),
                "language": language,
                "query_suite": query_suite,
                "rule_ids": rule_ids,
                "messages": messages,
                "findings": findings,
                "sarif_summary": self._sarif_summary(sarif),
            },
        )

    def _language_from_path(self, path: Path) -> str:
        suffix = path.suffix.lower()
        language = self.LANGUAGE_MAP.get(suffix)

        if language is None:
            raise ValueError(f"Unsupported CodeQL file extension: {suffix}")

        return language

    def _resolve_query_suite(self, language: str, suite_name: str) -> str:
        codeql_path = shutil.which("codeql")

        if codeql_path is None:
            raise RuntimeError(
                "CodeQL CLI is not installed or not available on PATH "
                
            )

        codeql_root = Path(codeql_path).resolve()
        if codeql_root.is_file():
            codeql_root = codeql_root.parent

        direct_path = (
            codeql_root
            / language
            / "ql"
            / "src"
            / "codeql-suites"
            / suite_name
        )
        if direct_path.exists():
            return str(direct_path)

        qlpacks_root = codeql_root / "qlpacks"
        if qlpacks_root.exists():
            matches = sorted(qlpacks_root.rglob(suite_name))
            if matches:
                return str(matches[-1])

        home_codeql = Path.home() / ".codeql"
        if home_codeql.exists():
            matches = sorted(home_codeql.rglob(suite_name))
            if matches:
                return str(matches[-1])

        matches = sorted(codeql_root.rglob(suite_name))
        if matches:
            return str(matches[-1])

        raise FileNotFoundError(
            f"CodeQL query suite not found: {suite_name}. "
            f"Searched under {codeql_root} and {home_codeql}."
        )

    def _build_command(self, language: str) -> str:
        if language == "cpp":
            return "gcc -c *.c || g++ -c *.cpp || true"

        if language == "java":
            return "javac *.java || true"

        if language == "csharp":
            return "dotnet build || true"

        if language == "go":
            return "go build ./... || true"

        return "true"

    def _extract_findings(
        self,
        sarif: dict,
        snippet_filename: str,
    ) -> list[dict]:
        findings: list[dict] = []

        for run in sarif.get("runs", []):
            rules_by_id = {}

            for tool_component in run.get("tool", {}).get("driver", {}).get("rules", []):
                rule_id = tool_component.get("id")
                if rule_id:
                    rules_by_id[rule_id] = tool_component

            for result in run.get("results", []):
                rule_id = result.get("ruleId")
                message = result.get("message", {}).get("text", "")

                locations = result.get("locations", [])

                for location in locations:
                    physical = location.get("physicalLocation", {})
                    artifact = physical.get("artifactLocation", {})
                    region = physical.get("region", {})

                    uri = artifact.get("uri", "")
                    line = region.get("startLine")

                    if snippet_filename not in uri:
                        continue

                    rule = rules_by_id.get(rule_id, {})

                    findings.append(
                        {
                            "rule_id": rule_id,
                            "message": message,
                            "line": line,
                            "uri": uri,
                            "severity": result.get("level"),
                            "rule_name": rule.get("name"),
                            "rule_description": rule.get("shortDescription", {}).get(
                                "text"
                            ),
                        }
                    )

        return findings

    def _sarif_summary(self, sarif: dict) -> dict:
        num_runs = len(sarif.get("runs", []))
        num_results = 0
        num_rules = 0

        for run in sarif.get("runs", []):
            num_results += len(run.get("results", []))
            num_rules += len(run.get("tool", {}).get("driver", {}).get("rules", []))

        return {
            "num_runs": num_runs,
            "num_results": num_results,
            "num_rules": num_rules,
        }

    def _error_prediction(
        self,
        snippet_id: str,
        runtime_ms: int,
        error_type: str,
        command: list[str],
        result: subprocess.CompletedProcess,
    ) -> DetectorPrediction:
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
                "error": error_type,
                "command": command,
                "returncode": result.returncode,
                "stdout": result.stdout,
                "stderr": result.stderr,
            },
        )