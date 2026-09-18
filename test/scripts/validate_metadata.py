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

"""Validate product-only Header metadata and target-derived case bundles."""

from __future__ import annotations

import argparse
import json
import logging
from pathlib import Path


LOGGER = logging.getLogger(__name__)


APPLICABILITY_KEYS = {
    "host_header",
    "device_header",
    "host_semantic",
    "device_compile",
    "cannsim_runtime",
    "hardware_runtime",
}
FORBIDDEN_MIGRATION_KEYS = {
    "batch",
    "batch_code",
    "delivery_unit_id",
    "execution_code",
    "physical_header_id",
    "wave",
    "wave_code",
}


def case_path(test_root: Path, target: str) -> Path:
    relative = target[:-2] if target.endswith(".h") else target
    return test_root / "cases" / relative


def reject_migration_keys(value: object, location: str = "metadata") -> None:
    if isinstance(value, dict):
        forbidden = sorted(FORBIDDEN_MIGRATION_KEYS & set(value))
        if forbidden:
            raise ValueError(f"{location} contains implementation-scheduling keys: {forbidden}")
        for key, child in value.items():
            reject_migration_keys(child, f"{location}.{key}")
    elif isinstance(value, list):
        for index, child in enumerate(value):
            reject_migration_keys(child, f"{location}[{index}]")


def validate_targets(headers: list[dict], include_root: Path) -> set[str]:
    product_files = sorted(
        path.relative_to(include_root).as_posix()
        for path in include_root.rglob("*")
        if path.is_file() and not path.name.startswith(".")
    )
    targets = [row.get("target") for row in headers]
    if any(not isinstance(target, str) or not target.startswith("asc/") for target in targets):
        raise ValueError("every metadata target must be an asc/ product Header")
    if len(set(targets)) != len(targets):
        raise ValueError("metadata target paths must be unique")
    if sorted(targets) != product_files:
        raise ValueError(f"metadata/Header mismatch: metadata={sorted(targets)}, files={product_files}")
    return set(targets)


def runtime_assets(row: dict, test_root: Path) -> set[Path]:
    applicability = row["applicability"]
    root = case_path(test_root, row.get("runtime_case", row["target"])) / "runtime"
    expected: set[Path] = set()
    if applicability["cannsim_runtime"]:
        expected.add(root / "semantics.h")
        expected.update(
            root / "cannsim" / name
            for name in ("CMakeLists.txt", "kernel.cpp", "launcher.cpp", "main.cpp")
        )
        optional_launcher = root / "cannsim" / "launcher.h"
        if optional_launcher.is_file():
            expected.add(optional_launcher)
    if applicability["hardware_runtime"]:
        expected.update(
            root / "hardware" / name
            for name in ("CMakeLists.txt", "kernel_simd.asc", "kernel_simt.asc", "main.cpp")
        )
    return expected


def validate_negative_languages(row: dict, target: str) -> None:
    negative_languages = row.get("negative_case_languages", {})
    if not isinstance(negative_languages, dict) or set(negative_languages) - set(row.get("negative_cases", [])):
        raise ValueError(f"{target}: negative_case_languages must map registered negative cases")
    for name, languages in negative_languages.items():
        if not isinstance(languages, list) or not languages or set(languages) - {"c++17", "c++20"}:
            raise ValueError(f"{target}: invalid language matrix for negative case {name}")


def validate_applicability(row: dict, target: str) -> dict:
    applicability = row.get("applicability")
    if not isinstance(applicability, dict) or set(applicability) != APPLICABILITY_KEYS:
        raise ValueError(f"{target}: applicability must define exactly {sorted(APPLICABILITY_KEYS)}")
    if any(not isinstance(value, bool) for value in applicability.values()):
        raise ValueError(f"{target}: applicability values must be booleans")
    if not applicability["host_header"] or not applicability["device_header"]:
        raise ValueError(f"{target}: C++17/C++20 Host and Device Header gates are mandatory")
    return applicability


def validate_dependencies(row: dict, target: str, registered: set[str]) -> list:
    dependencies = row.get("dependencies")
    if not isinstance(dependencies, list) or len(dependencies) != len(set(dependencies)):
        raise ValueError(f"{target}: dependencies must be a unique list")
    unknown = sorted(set(dependencies) - registered)
    if unknown:
        raise ValueError(f"{target}: dependencies are not registered product Headers: {unknown}")
    return dependencies


def validate_mapped_targets(row: dict, target: str, registered: set[str]) -> None:
    for field in ("semantic_case", "runtime_case"):
        mapped = row.get(field, target)
        if not isinstance(mapped, str) or mapped not in registered:
            raise ValueError(f"{target}: {field} must name a registered product Header")


def semantic_case_assets(row: dict, target: str, semantic_root: Path) -> set[Path]:
    expected: set[Path] = set()
    applicability = row["applicability"]
    if applicability["host_semantic"]:
        expected.add(semantic_root / "host.pass.cpp")
    if applicability["device_compile"]:
        device_cases = row.get("device_compile_cases", ["device.compile.asc"])
        if not isinstance(device_cases, list) or not device_cases:
            raise ValueError(f"{target}: device_compile_cases must be a non-empty list")
        for name in device_cases:
            if Path(name).name != name:
                raise ValueError(f"{target}: invalid device_compile_cases entry: {name!r}")
            expected.add(semantic_root / name)
    return expected


def listed_case_assets(row: dict, target: str, root: Path) -> set[Path]:
    expected: set[Path] = set()
    for field in ("negative_cases", "additional_cases"):
        for name in row.get(field, []):
            if Path(name).name != name:
                raise ValueError(f"{target}: {field} entry must be a case-local filename: {name}")
            expected.add(root / name)
    return expected


def validate_row(row: dict, registered: set[str], test_root: Path) -> tuple[int, set[Path]]:
    target = row["target"]
    applicability = validate_applicability(row, target)
    dependencies = validate_dependencies(row, target, registered)
    validate_mapped_targets(row, target, registered)
    root = case_path(test_root, target)
    semantic_root = case_path(test_root, row.get("semantic_case", target))
    expected = semantic_case_assets(row, target, semantic_root)
    expected.update(runtime_assets(row, test_root))
    expected.update(listed_case_assets(row, target, root))
    validate_negative_languages(row, target)
    return len(dependencies), expected


def validate_case_inventory(test_root: Path, expected: set[Path]) -> None:
    missing = sorted(str(path.relative_to(test_root)) for path in expected if not path.is_file())
    if missing:
        raise ValueError(f"metadata-applicable case assets are missing: {missing}")
    suffixes = (".pass.cpp", ".fail.cpp", ".compile.asc", ".fail.asc")
    observed = {
        path for path in (test_root / "cases").rglob("*")
        if path.is_file() and (path.name.endswith(suffixes) or "runtime" in path.parts)
    }
    unexpected = sorted(str(path.relative_to(test_root)) for path in observed - expected)
    if unexpected:
        raise ValueError(f"case assets lack an applicable metadata mapping: {unexpected}")


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    parser = argparse.ArgumentParser()
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--include-root", type=Path, required=True)
    parser.add_argument("--test-root", type=Path, required=True)
    args = parser.parse_args()
    payload = json.loads(args.manifest.read_text(encoding="utf-8"))
    reject_migration_keys(payload)
    if payload.get("schema_version") != 2:
        raise ValueError("Header metadata schema_version must be 2")
    headers = payload.get("headers")
    if not isinstance(headers, list) or not headers:
        raise ValueError("metadata.headers must be a non-empty list")

    registered = validate_targets(headers, args.include_root)
    expected_case_files: set[Path] = set()
    dependency_count = 0
    for row in headers:
        count, expected = validate_row(row, registered, args.test_root)
        dependency_count += count
        expected_case_files.update(expected)
    validate_case_inventory(args.test_root, expected_case_files)

    LOGGER.info(
        f"PASS: {len(registered)} product Headers, {dependency_count} dependencies, "
        f"and {len(expected_case_files)} target-derived case assets"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
