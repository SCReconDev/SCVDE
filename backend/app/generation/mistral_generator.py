import os
import re
from typing import Literal

import httpx
from mistralai.client import Mistral

from app.storage.file_store import FileStore


VULNERABILITY_CONFIG = {
    "sql_injection": {
        "aliases": ["sql injection", "sqli"],
        "cwe": "CWE-89",
        "description": "SQL injection",
        "vulnerable_guidance": (
            "Use user-controlled input unsafely in a database query, for example through "
            "string concatenation, interpolation, formatting, or raw query construction."
        ),
        "safe_guidance": (
            "Use parameterized queries, prepared statements, or safe ORM APIs. "
            "Do not construct queries with user-controlled strings."
        ),
    },
    "command_injection": {
        "aliases": ["command injection", "os command injection"],
        "cwe": "CWE-78",
        "description": "command injection",
        "vulnerable_guidance": (
            "Use user-controlled input unsafely in an operating-system command. "
            "Do not include real destructive commands or payloads."
        ),
        "safe_guidance": (
            "Avoid shell execution with user input. Use safe APIs, argument lists, allowlists, "
            "and validation."
        ),
    },
    "xss": {
        "aliases": ["cross site scripting", "cross-site scripting"],
        "cwe": "CWE-79",
        "description": "cross-site scripting",
        "vulnerable_guidance": (
            "Render user-controlled input into an HTML or web response without proper escaping "
            "or sanitization."
        ),
        "safe_guidance": (
            "Escape or sanitize user-controlled output and use framework-safe rendering APIs."
        ),
    },
    "remote_code_execution": {
        "aliases": ["rce", "remote code execution", "code execution"],
        "cwe": "CWE-94",
        "description": "remote code execution",
        "vulnerable_guidance": (
            "Use user-controlled input in dynamic code evaluation or execution. "
            "Keep it synthetic and non-deployable. Do not include exploit payloads."
        ),
        "safe_guidance": (
            "Avoid eval-like behavior. Use fixed dispatch tables, allowlists, and safe parsers."
        ),
    },
    "csrf": {
        "aliases": [
            "xsrf",
            "csrf",
            "cross site request forgery",
            "cross-site request forgery",
        ],
        "cwe": "CWE-352",
        "description": "cross-site request forgery",
        "vulnerable_guidance": (
            "Create a state-changing web action without CSRF protection."
        ),
        "safe_guidance": (
            "Use CSRF tokens, same-site cookies, and framework CSRF protection."
        ),
    },
    "open_redirect": {
        "aliases": ["open redirect", "open ridirect", "unvalidated redirect"],
        "cwe": "CWE-601",
        "description": "open redirect",
        "vulnerable_guidance": (
            "Redirect to a user-controlled URL without validation or allowlisting."
        ),
        "safe_guidance": (
            "Only redirect to relative paths or allowlisted trusted destinations."
        ),
    },
    "path_disclosure": {
        "aliases": [
            "path disclosure",
            "information disclosure path",
            "full path disclosure",
        ],
        "cwe": "CWE-209",
        "description": "path disclosure",
        "vulnerable_guidance": (
            "Expose internal filesystem paths, stack traces, debug paths, or server paths "
            "in responses, logs, or error messages visible to users."
        ),
        "safe_guidance": (
            "Return generic error messages and avoid exposing internal paths or debug details."
        ),
    },
    "path_traversal": {
        "aliases": ["path traversal", "directory traversal"],
        "cwe": "CWE-22",
        "description": "path traversal",
        "vulnerable_guidance": (
            "Use user-controlled paths directly for file reads or writes without safe normalization "
            "and base-directory enforcement."
        ),
        "safe_guidance": (
            "Normalize paths, enforce an allowed base directory, and reject traversal attempts."
        ),
    },
    "ssrf": {
        "aliases": [
            "server side request forgery",
            "server-side request forgery",
        ],
        "cwe": "CWE-918",
        "description": "server-side request forgery",
        "vulnerable_guidance": (
            "Use a user-controlled URL in a server-side request without validation."
        ),
        "safe_guidance": (
            "Use URL allowlists, block internal/private networks, and validate schemes and hosts."
        ),
    },
    "insecure_deserialization": {
        "aliases": ["insecure deserialization", "unsafe deserialization"],
        "cwe": "CWE-502",
        "description": "insecure deserialization",
        "vulnerable_guidance": (
            "Deserialize untrusted user-controlled data using an unsafe deserialization mechanism."
        ),
        "safe_guidance": (
            "Use safe data formats, schema validation, and avoid unsafe object deserialization."
        ),
    },
    "hardcoded_secret": {
        "aliases": [
            "hardcoded secret",
            "hardcoded credential",
            "secret exposure",
        ],
        "cwe": "CWE-798",
        "description": "hardcoded secret",
        "vulnerable_guidance": (
            "Include a fake hardcoded secret, token, password, or API key in the code. "
            "Use obviously fake values only."
        ),
        "safe_guidance": (
            "Load secrets from environment variables or secret-management systems."
        ),
    },
    "memory_safety": {
        "aliases": [
            "memory safety",
            "memory_safety",
            "buffer overflow",
            "out of bounds",
            "use after free",
            "null pointer dereference",
        ],
        "cwe": "CWE-119",
        "description": "Memory safety vulnerability in C or C++ code.",
        "vulnerable_guidance": (
            "The vulnerable version must contain exactly one memory safety issue, "
            "such as a buffer overflow, out-of-bounds access, null pointer dereference, "
            "use-after-free, double free, memory leak, or unsafe string copy. "
            "The issue should be visible to static analysis."
        ),
        "safe_guidance": (
            "The safe version must avoid memory safety issues by using bounds checks, "
            "proper allocation checks, safe string handling, correct ownership, and "
            "valid pointer checks."
        ),
    },
}


DIVERSITY_AXES = {
    "sql_injection": [
        "{language} web login handler + query parameter + database lookup",
        "{language} search endpoint + JSON body + dynamic WHERE clause",
        "{language} CLI utility + command-line argument + SQL filter",
        "{language} admin report generator + user-selected ORDER BY",
        "{language} profile lookup service + path parameter + raw query",
        "{language} background import job + CSV value + database insert",
        "{language} class-based repository + method argument + SELECT query",
        "{language} API endpoint + header value + IN clause",
        "{language} config-driven script + config value + database query",
        "{language} delete/update handler + request field + SQL statement",
    ],
    "command_injection": [
        "{language} web endpoint + query parameter + system utility call",
        "{language} CLI tool + command-line argument + shell command",
        "{language} admin maintenance action + form field + subprocess call",
        "{language} file conversion helper + uploaded filename + command string",
        "{language} backup script + config value + archive command",
        "{language} monitoring endpoint + host parameter + ping-like command",
        "{language} deployment helper + branch name + shell execution",
        "{language} log processing job + user-supplied pattern + shell pipeline",
        "{language} image processing wrapper + request field + external tool",
        "{language} service class + method argument + operating-system command",
    ],
    "xss": [
        "{language} web page renderer + query parameter + HTML response",
        "{language} comment preview endpoint + form input + template output",
        "{language} user profile page + display name + rendered HTML",
        "{language} search results page + search term + reflected output",
        "{language} admin dashboard widget + request field + HTML fragment",
        "{language} notification renderer + message text + browser output",
        "{language} markdown preview feature + user content + rendered page",
        "{language} error page + request value + HTML response",
        "{language} client-side route + URL parameter + DOM update",
        "{language} template helper + user-controlled label + page output",
    ],
    "remote_code_execution": [
        "{language} API endpoint + JSON expression field + dynamic evaluation",
        "{language} plugin runner + config value + code evaluation",
        "{language} template processor + user expression + runtime evaluation",
        "{language} rule engine + request field + dynamic code execution",
        "{language} admin console helper + form input + interpreter call",
        "{language} calculator endpoint + query parameter + expression evaluation",
        "{language} workflow automation service + user script + execution path",
        "{language} data transformation job + config expression + eval-like call",
        "{language} test harness + request-provided callback + dynamic execution",
        "{language} class factory + user-controlled class name + dynamic loading",
    ],
    "csrf": [
        "{language} account settings form + state-changing POST endpoint",
        "{language} password change handler + cookie authentication + missing CSRF token",
        "{language} email update endpoint + browser session + no CSRF validation",
        "{language} admin delete action + form submission + missing CSRF protection",
        "{language} payment preference update + authenticated cookie + no CSRF check",
        "{language} profile picture update + multipart form + missing CSRF token",
        "{language} notification settings toggle + POST request + no CSRF middleware",
        "{language} role assignment endpoint + admin cookie + no CSRF validation",
        "{language} address book update + browser form + missing CSRF defense",
        "{language} logout or session action + state-changing request + no CSRF token",
    ],
    "open_redirect": [
        "{language} login redirect handler + next URL parameter",
        "{language} logout endpoint + return URL parameter",
        "{language} OAuth callback-like flow + redirect target value",
        "{language} email verification handler + continue parameter",
        "{language} password reset completion page + redirect parameter",
        "{language} marketing landing route + destination query parameter",
        "{language} download confirmation page + user-controlled redirect",
        "{language} interstitial warning page + target URL parameter",
        "{language} SSO relay endpoint + returnTo parameter",
        "{language} language switcher route + back URL parameter",
    ],
    "path_disclosure": [
        "{language} error handler + exception message containing filesystem path",
        "{language} debug response + server path leakage",
        "{language} file loader + user-visible stack trace",
        "{language} configuration checker + internal path returned to client",
        "{language} upload handler + temporary file path shown in response",
        "{language} template rendering error + absolute template path exposure",
        "{language} log viewer + internal log path displayed to user",
        "{language} diagnostics endpoint + application root path disclosure",
        "{language} report export failure + full output path in error message",
        "{language} plugin loader error + module path exposed in response",
    ],
    "path_traversal": [
        "{language} file download route + filename parameter",
        "{language} document preview endpoint + path parameter",
        "{language} CLI file reader + command-line path argument",
        "{language} report loader + config-provided filename",
        "{language} static file handler + user-controlled relative path",
        "{language} image retrieval endpoint + request field + file path",
        "{language} localization loader + language parameter + resource path",
        "{language} backup viewer + archive entry name + filesystem access",
        "{language} attachment service + message parameter + local file read",
        "{language} template loader + theme parameter + file lookup",
    ],
    "ssrf": [
        "{language} URL preview endpoint + user-provided URL + server-side fetch",
        "{language} webhook tester + request URL field + outbound HTTP request",
        "{language} image proxy service + image URL parameter + HTTP client",
        "{language} document importer + remote URL + server-side download",
        "{language} metadata fetcher + target parameter + internal request risk",
        "{language} link checker job + CSV URL value + server-side request",
        "{language} PDF generator + external asset URL + backend fetch",
        "{language} API integration tester + endpoint field + HTTP request",
        "{language} avatar loader + profile image URL + server request",
        "{language} feed reader + feed URL parameter + backend HTTP client",
    ],
    "insecure_deserialization": [
        "{language} API endpoint + base64 payload + object deserialization",
        "{language} session loader + cookie value + unsafe object decode",
        "{language} cache restore helper + stored blob + deserialization",
        "{language} message queue worker + incoming body + object loading",
        "{language} file import tool + uploaded state file + object deserialization",
        "{language} plugin settings loader + config blob + unsafe deserialize",
        "{language} CLI restore command + input file + object loading",
        "{language} background job + serialized task data + object reconstruction",
        "{language} test fixture loader + external fixture + unsafe parser",
        "{language} preferences importer + user file + object deserialization",
    ],
    "hardcoded_secret": [
        "{language} API client wrapper + fake hardcoded API token",
        "{language} database connector + fake hardcoded password",
        "{language} cloud storage helper + fake access key in source",
        "{language} payment gateway config + fake secret key constant",
        "{language} email sender utility + fake SMTP password",
        "{language} third-party integration + fake bearer token string",
        "{language} test configuration + fake credential committed in code",
        "{language} admin script + fake private key-like string",
        "{language} service class + fake OAuth client secret",
        "{language} deployment helper + fake registry password",
    ],
    "memory_safety": [
        "{language} input handler + fixed-size buffer or collection + unchecked copy",
        "{language} collection access function + externally controlled index + missing bounds check",
        "{language} resource allocation function + allocation result + missing failure handling",
        "{language} resource-owning function + allocated memory or handle + missing cleanup",
        "{language} function + nullable reference or pointer + dereference without validation",
        "{language} iteration logic + collection boundary + off-by-one access",
        "{language} buffer manipulation function + size mismatch + out-of-bounds write",
        "{language} resource lifecycle function + released object + later reuse",
        "{language} object creation function + manual ownership + missing release",
        "{language} parser or decoder helper + supplied length + incorrect range validation",
    ],
}


IMPORTANT_VULNERABILITIES = list(VULNERABILITY_CONFIG.keys())


LANGUAGE_EXTENSIONS = {
    "python": "py",
    "javascript": "js",
    "typescript": "ts",
    "java": "java",
    "c": "c",
    "cpp": "cpp",
    "c++": "cpp",
    "csharp": "cs",
    "c#": "cs",
    "php": "php",
    "ruby": "rb",
    "go": "go",
    "rust": "rs",
    "kotlin": "kt",
    "swift": "swift",
}


def normalize_key(value: str) -> str:
    return value.strip().lower().replace("-", "_").replace(" ", "_")


def normalize_vulnerability_type(value: str) -> str:
    raw = value.strip().lower()
    normalized = normalize_key(value)

    if normalized in VULNERABILITY_CONFIG:
        return normalized

    for key, cfg in VULNERABILITY_CONFIG.items():
        aliases = [normalize_key(alias) for alias in cfg.get("aliases", [])]
        if normalized in aliases or raw in cfg.get("aliases", []):
            return key

    return normalized


def get_vulnerability_config(vulnerability_type: str) -> dict:
    key = normalize_vulnerability_type(vulnerability_type)

    if key in VULNERABILITY_CONFIG:
        return VULNERABILITY_CONFIG[key]

    pretty_name = key.replace("_", " ")

    return {
        "aliases": [],
        "cwe": "unknown",
        "description": pretty_name,
        "vulnerable_guidance": (
            f"Create code containing exactly one clear {pretty_name} vulnerability."
        ),
        "safe_guidance": (
            f"Create a safe version that avoids {pretty_name} and follows secure coding practices."
        ),
    }


def extension_for_language(language: str) -> str:
    key = language.strip().lower()
    return LANGUAGE_EXTENSIONS.get(key, key.replace(" ", "_") or "txt")


def strip_markdown_fences(text: str) -> str:
    text = text.strip()

    if text.startswith("```"):
        lines = text.splitlines()

        if lines and lines[0].startswith("```"):
            lines = lines[1:]

        if lines and lines[-1].startswith("```"):
            lines = lines[:-1]

        return "\n".join(lines).strip()

    return text


def split_samples(text: str) -> list[str]:
    parts = re.split(r"\$\$\$Sample\s+\d+\$\$\$", text)
    return [strip_markdown_fences(part) for part in parts if part.strip()]


class MistralDatasetGenerator:
    def __init__(
        self,
        store: FileStore | None = None,
        model: str = "mistral-medium-latest",
    ):
        self.store = store or FileStore()
        self.model = model

        timeout = httpx.Timeout(
            connect=20.0,
            read=600.0,
            write=120.0,
            pool=20.0,
        )
        self.http_client = httpx.Client(timeout=timeout)

    def generate_dataset(
        self,
        dataset_id: str,
        name: str,
        vulnerability_type: str,
        language: str = "python",
        num_vulnerable: int = 10,
        num_safe: int = 10,
        batch_size: int = 5,
        overwrite: bool = False,
    ) -> dict:
        vulnerability_key = normalize_vulnerability_type(vulnerability_type)
        cfg = get_vulnerability_config(vulnerability_key)

        dataset = self.store.create_dataset(
            dataset_id=dataset_id,
            name=name,
            language=language,
            vulnerability_types=[vulnerability_key],
            overwrite=overwrite,
        )

        vulnerable_samples = self._generate_samples(
            vulnerability_type=vulnerability_key,
            language=language,
            label="vulnerable",
            count=num_vulnerable,
            batch_size=batch_size,
        )

        safe_samples = self._generate_samples(
            vulnerability_type=vulnerability_key,
            language=language,
            label="safe",
            count=num_safe,
            batch_size=batch_size,
        )

        snippets = []
        index = 1
        file_ext = extension_for_language(language)

        for is_vulnerable, samples in [
            (True, vulnerable_samples),
            (False, safe_samples),
        ]:
            for code in samples:
                snippet_id = f"snippet_{index:04d}"
                filename = f"{snippet_id}.{file_ext}"

                relative_path = self.store.save_snippet_code(
                    dataset_id=dataset_id,
                    filename=filename,
                    code=code,
                )

                snippets.append(
                    {
                        "id": snippet_id,
                        "file_path": relative_path,
                        "language": language,
                        "vulnerability_type": vulnerability_key,
                        "cwe": cfg["cwe"],
                        "is_vulnerable": is_vulnerable,
                        "expected_vulnerable_lines": [],
                        "difficulty": "generated",
                        "source": "mistral",
                    }
                )

                index += 1

        dataset["snippets"] = snippets
        self.store.save_dataset(dataset_id, dataset)
        return dataset

    def _generate_samples(
        self,
        vulnerability_type: str,
        language: str,
        label: Literal["vulnerable", "safe"],
        count: int,
        batch_size: int,
    ) -> list[str]:
        if count <= 0:
            return []

        if "MISTRAL_API_KEY" not in os.environ:
            raise RuntimeError("Missing environment variable: MISTRAL_API_KEY")

        samples: list[str] = []

        with Mistral(
            api_key=os.environ["MISTRAL_API_KEY"],
            client=self.http_client,
        ) as mistral:
            while len(samples) < count:
                remaining = count - len(samples)
                current_batch_size = min(batch_size, remaining)

                messages = self._build_messages(
                    vulnerability_type=vulnerability_type,
                    language=language,
                    label=label,
                    batch_size=current_batch_size,
                    start_index=len(samples) + 1,
                )

                response_text = ""

                stream = mistral.chat.stream(
                    model=self.model,
                    messages=messages,
                    temperature=0.7,
                    top_p=0.9,
                    max_tokens=15000,
                )

                for chunk in stream:
                    delta = chunk.data.choices[0].delta.content
                    if delta:
                        response_text += delta

                batch_samples = split_samples(response_text)

                if not batch_samples:
                    raise RuntimeError(
                        "Mistral returned no parseable samples. "
                        "Check sample separator format."
                    )

                samples.extend(batch_samples[:remaining])

        return samples[:count]

    def _build_messages(
        self,
        vulnerability_type: str,
        language: str,
        label: Literal["vulnerable", "safe"],
        batch_size: int,
        start_index: int,
    ) -> list[dict]:
        cfg = get_vulnerability_config(vulnerability_type)

        diversity_plan = self._build_diversity_plan(
            vulnerability_type=vulnerability_type,
            language=language,
            batch_size=batch_size,
            start_index=start_index,
        )

        other_vulnerabilities = [
            get_vulnerability_config(v)["description"]
            for v in IMPORTANT_VULNERABILITIES
            if v != vulnerability_type
        ]

        other_vuln_text = "\n".join(f"- {v}" for v in other_vulnerabilities)

        if label == "vulnerable":
            label_instruction = (
                f"Generate samples that contain exactly one intentional vulnerability type: "
                f"{cfg['description']}.\n"
                f"Required vulnerable pattern: {cfg['vulnerable_guidance']}\n\n"
                "Isolation rule:\n"
                f"- The code must contain the requested vulnerability: {cfg['description']}.\n"
                f"- The code must NOT contain any other intentional vulnerability besides {cfg['description']}.\n"
                "- Do not include additional weaknesses such as hardcoded secrets, path traversal, "
                "open redirects, XSS, command injection, insecure deserialization, SSRF, debug leakage, "
                "missing authentication, unsafe file access, or unsafe cryptography unless that is the "
                "requested vulnerability.\n"
                "- Do not include exploit payloads, attack strings, malware behavior, or instructions.\n"
            )
        else:
            label_instruction = (
                f"Generate safe/non-vulnerable samples related to {cfg['description']}.\n"
                f"Required safe pattern: {cfg['safe_guidance']}\n\n"
                "Safe-code rule:\n"
                "- The code must contain no intentional security vulnerability at all.\n"
                "- It must avoid the requested vulnerability and also avoid these vulnerability classes:\n"
                f"{other_vuln_text}\n"
                "- Do not include hardcoded real-looking secrets, debug leakage, unsafe file access, "
                "unsafe redirects, unsafe deserialization, shell execution with user input, unescaped output, "
                "missing authorization, missing authentication, or unsafe cryptography.\n"
            )

        return [
            {
                "role": "system",
                "content": (
                    f"You create synthetic {language} code samples for a university benchmark for "
                    "static-analysis and ML vulnerability detection. "
                    "Output only code samples separated by the requested markers. "
                    "Do not explain. Do not use markdown. Do not include exploit payloads."
                ),
            },
            {
                "role": "user",
                "content": (
                    f"Generate {batch_size} {language} samples.\n\n"
                    f"{label_instruction}\n"
                    "Separate samples exactly like this:\n"
                    "$$$Sample 1$$$\n"
                    "<code>\n"
                    "$$$Sample 2$$$\n"
                    "<code>\n\n"
                    "Use this diversity plan:\n"
                    f"{diversity_plan}\n\n"
                    "General rules:\n"
                    "- Make each sample structurally distinct.\n"
                    "- Keep samples self-contained.\n"
                    "- The samples should be long enough for proper evaluation.\n"
                    "- Do not repeat the same framework/library/input/pattern combination.\n"
                    "- Do not add comments that reveal whether the sample is safe or vulnerable.\n"
                    "- Output only code separated by the required sample markers."
                    "- The samples must be long.\n"
                ),
            },
        ]

    def _build_diversity_plan(
        self,
        vulnerability_type: str,
        language: str,
        batch_size: int,
        start_index: int,
    ) -> str:
        cfg = get_vulnerability_config(vulnerability_type)
        desc = cfg["description"]

        axes = DIVERSITY_AXES.get(vulnerability_type)

        if axes is None:
            axes = [
                "{language} web handler + request parameter + {desc}",
                "{language} API endpoint + JSON body + {desc}",
                "{language} CLI utility + command-line argument + {desc}",
                "{language} background job + config value + {desc}",
                "{language} class-based service + method parameter + {desc}",
                "{language} file-processing script + external input + {desc}",
                "{language} admin action + form field + {desc}",
                "{language} report generator + user option + {desc}",
                "{language} middleware/helper function + header value + {desc}",
                "{language} route/controller + path parameter + {desc}",
            ]

        return "\n".join(
            f"{start_index + i}. "
            f"{axes[i % len(axes)].format(language=language, desc=desc)}"
            for i in range(batch_size)
        )