#!/usr/bin/env python3
# Copyright 2026 湖北多样性算力应用创新研究院 (Hubei Institute for Heterogeneous Computing Applications)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

"""Inventory example registration and verify translated API code remains equivalent."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import re

CPP = re.compile(r"```cpp\n(.*?)\n```", re.DOTALL)
TOKENS = re.compile(
    r'''R"(?P<delimiter>[^ ()\\\t\r\n]{0,16})\(.*?\)(?P=delimiter)"'''
    r'''|"(?:\\.|[^"\\])*"|'(?:\\.|[^'\\])*'|//[^\n]*|/\*.*?\*/|\s+'''
    r'''|[A-Za-z_][A-Za-z_0-9]*|[0-9][A-Za-z_0-9.]*'''
    r'''|<=>|>>=|<<=|->\*|\.\.\.|::|->|\+\+|--|&&|\|\||==|!=|<=|>=|<<|>>|[+*/%&|^!-]=|.''', re.DOTALL)


def code_tokens(source: str) -> tuple[str, ...]:
    return tuple(match.group() for match in TOKENS.finditer(source)
                 if not match.group().isspace() and not match.group().startswith(("//", "/*")))


def mirrored_code_errors(root: Path, source_pages: list[Path]) -> list[str]:
    errors = []
    chinese = root / "docs/zh/api"
    english = root / "docs/en/api"
    for page in source_pages:
        translated = english / page.relative_to(chinese)
        if not translated.is_file():
            errors.append(f"Missing English API page: {translated.relative_to(root)}")
            continue
        left = [code_tokens(block) for block in CPP.findall(page.read_text(encoding="utf-8"))]
        right = [code_tokens(block) for block in CPP.findall(translated.read_text(encoding="utf-8"))]
        if left != right:
            errors.append(f"Translated API code differs: {translated.relative_to(root)}")
    return errors


def registered_page_errors(root: Path, registry: dict, example_pages: set[str]) -> list[str]:
    errors = []
    for page, spec in registry.items():
        if page not in example_pages:
            errors.append(f"Registered page lacks a Chinese API example: {page}")
        if spec.get("mode") not in ("host", "runtime", "simd", "simt"):
            errors.append(f"Unknown example execution mode: {page}")
        if not spec.get("standards") or any(value not in (17, 20, 23) for value in spec["standards"]):
            errors.append(f"Invalid example language standards: {page}")
        if not (root / page).is_file():
            errors.append(f"Registered example page is missing: {page}")
        expected = spec.get("expected_exit", 0)
        marker = spec.get("expected_output", "")
        if expected not in (0, 42) or not isinstance(expected, int):
            errors.append(f"Unsupported expected example exit: {page}")
        if expected == 42:
            if not isinstance(marker, str) or not marker or "\n" in marker:
                errors.append(f"Expected termination requires an exact output marker: {page}")
        if expected == 42 and spec.get("mode") != "host":
            errors.append(f"Expected termination is a Host-only example protocol: {page}")
    return errors


def coverage_inventory(root: Path) -> dict:
    registry_path = root / "test/docs/examples.json"
    registry_bytes = registry_path.read_bytes()
    registry = json.loads(registry_bytes)
    source_pages = sorted((root / "docs/zh/api").rglob("*.md"))
    example_pages = {path.relative_to(root).as_posix() for path in source_pages
                     if "## 调用示例" in path.read_text(encoding="utf-8")}
    registered = set(registry) & example_pages
    errors = registered_page_errors(root, registry, example_pages)
    errors.extend(mirrored_code_errors(root, source_pages))
    return {"scope": "Example page registration; not API semantic or runtime coverage",
            "chinese_api_pages": len(source_pages), "example_pages": len(example_pages),
            "registered_pages": len(registered), "unregistered_pages": sorted(example_pages - registered),
            "registration_fraction": len(registered) / len(example_pages) if example_pages else None,
            "registry_sha256": hashlib.sha256(registry_bytes).hexdigest(),
            "english_code_checked_against_chinese": True, "errors": errors}
