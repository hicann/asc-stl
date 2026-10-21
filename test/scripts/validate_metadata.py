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


def hardware_assets(runtime_root: Path) -> set[Path]:
    root = runtime_root / "runtime" / "hardware"
    result = {
        root / name
        for name in ("CMakeLists.txt", "kernel_simd.asc", "kernel_simt.asc", "main.cpp")
    }
    launch_header = root / "launch.h"
    if launch_header.is_file():
        result.add(launch_header)
    return result


def explicit_runtime_assets(runtime_root: Path, category: str, manifest_name: str) -> set[Path]:
    manifest = runtime_root / manifest_name
    payload = json.loads(manifest.read_text(encoding="utf-8"))
    if not isinstance(payload, dict) or set(payload) != {"common", "cannsim", "hardware"}:
        raise ValueError(f"{manifest}: runtime assets must define common, cannsim and hardware")
    expected = {manifest}
    for group, names in payload.items():
        if not isinstance(names, list) or not names or not all(isinstance(name, str) for name in names):
            raise ValueError(f"{manifest}: {group} must list unique runtime asset paths")
        if len(names) != len(set(names)):
            raise ValueError(f"{manifest}: {group} has duplicate runtime asset paths")
        for name in names:
            if not name or Path(name).is_absolute() or ".." in Path(name).parts:
                raise ValueError(f"{manifest}: invalid runtime asset path {name!r}")
            if group in ("common", category):
                expected.add(manifest.parent / name)
    return expected


def applicable_runtime_assets(applicability: dict, runtime_root: Path, manifest: str | None) -> set[Path]:
    expected: set[Path] = set()
    for category in ("cannsim", "hardware"):
        if not applicability[f"{category}_runtime"]:
            continue
        if manifest:
            expected.update(explicit_runtime_assets(runtime_root, category, manifest))
        elif category == "hardware":
            expected.update(hardware_assets(runtime_root))
        else:
            expected.add(runtime_root / "runtime" / "semantics.h")
            expected.update(runtime_root / "runtime" / category / name
                            for name in ("CMakeLists.txt", "kernel.cpp", "launcher.cpp", "main.cpp"))
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


def validate_dependencies(row: dict, registered: set[str]) -> list:
    target = row["target"]
    dependencies = row.get("dependencies")
    if not isinstance(dependencies, list) or len(dependencies) != len(set(dependencies)):
        raise ValueError(f"{target}: dependencies must be a unique list")
    unknown = sorted(set(dependencies) - registered)
    if unknown:
        raise ValueError(f"{target}: dependencies are not registered product Headers: {unknown}")
    return dependencies


def validate_case_mappings(row: dict, registered: set[str]) -> None:
    target = row["target"]
    for field in ("semantic_case", "runtime_case"):
        mapped = row.get(field, target)
        if not isinstance(mapped, str) or mapped not in registered:
            raise ValueError(f"{target}: {field} must name a registered product Header")


def semantic_case_assets(row: dict, semantic_root: Path, applicability: dict) -> set[Path]:
    target = row["target"]
    expected: set[Path] = set()
    if applicability["host_semantic"]:
        expected.add(semantic_root / "host.pass.cpp")
    if applicability["device_compile"]:
        device_cases = row.get("device_compile_cases", ["device.compile.asc"])
        if not isinstance(device_cases, list) or not device_cases:
            raise ValueError(f"{target}: device_compile_cases must be a non-empty list")
        for name in device_cases:
            if not isinstance(name, str) or Path(name).name != name or not name.endswith(".compile.asc"):
                raise ValueError(f"{target}: invalid device_compile_cases entry: {name!r}")
            expected.add(semantic_root / name)
    return expected


def local_case_assets(row: dict, root: Path) -> set[Path]:
    target = row["target"]
    expected: set[Path] = set()
    for field in ("negative_cases", "additional_cases"):
        for name in row.get(field, []):
            if Path(name).name != name:
                raise ValueError(f"{target}: {field} entry must be a case-local filename: {name}")
            expected.add(root / name)
    return expected


def validate_row(row: dict, registered: set[str], test_root: Path, runtime_manifests: dict) -> tuple[int, set[Path]]:
    target = row["target"]
    applicability = validate_applicability(row, target)
    dependencies = validate_dependencies(row, registered)
    validate_case_mappings(row, registered)
    root = case_path(test_root, target)
    semantic_root = case_path(test_root, row.get("semantic_case", target))
    runtime_root = case_path(test_root, row.get("runtime_case", target))
    runtime_manifest = runtime_manifests.get(row.get("runtime_case", target))
    expected = semantic_case_assets(row, semantic_root, applicability)
    expected.update(applicable_runtime_assets(applicability, runtime_root, runtime_manifest))
    expected.update(local_case_assets(row, root))
    validate_negative_languages(row, target)
    return len(dependencies), expected


def validate_case_inventory(test_root: Path, expected: set[Path]) -> None:
    missing = sorted(str(path.relative_to(test_root)) for path in expected if not path.is_file())
    if missing:
        raise ValueError(f"metadata-applicable case assets are missing: {missing}")
    canonical_suffixes = (".pass.cpp", ".fail.cpp", ".compile.asc", ".fail.asc")
    observed = {
        path for path in (test_root / "cases").rglob("*")
        if path.is_file() and (path.name.endswith(canonical_suffixes) or "runtime" in path.parts)
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
    runtime_manifests = payload.get("runtime_asset_manifests", {})
    if not isinstance(runtime_manifests, dict) or set(runtime_manifests) - registered:
        raise ValueError("runtime_asset_manifests must map registered runtime targets")
    for name in runtime_manifests.values():
        if not isinstance(name, str) or Path(name).is_absolute() or ".." in Path(name).parts:
            raise ValueError("runtime asset manifests must use product case-relative paths")
    expected_case_files: set[Path] = set()
    dependency_count = 0
    for row in headers:
        count, expected = validate_row(row, registered, args.test_root, runtime_manifests)
        dependency_count += count
        expected_case_files.update(expected)
    hardware_levels_path = args.manifest.with_name("hardware_levels.json")
    hardware_levels = json.loads(hardware_levels_path.read_text(encoding="utf-8"))
    if hardware_levels.get("schema_version") != 1:
        raise ValueError("hardware level metadata schema_version must be 1")
    runtime_cases = {
        row.get("runtime_case", row["target"])
        for row in headers
        if row["applicability"]["hardware_runtime"]
    }
    levels = hardware_levels.get("runtime_cases")
    if not isinstance(levels, dict) or set(levels) != runtime_cases or set(levels.values()) - {"HW0", "HW1"}:
        raise ValueError("hardware level metadata must classify every applicable runtime_case exactly once")
    validate_case_inventory(args.test_root, expected_case_files)

    LOGGER.info(
        f"PASS: {len(registered)} product Headers, {dependency_count} dependencies, "
        f"and {len(expected_case_files)} target-derived case assets"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
