#!/usr/bin/env python3

# Copyright 2026 湖北多样性算力应用创新究院 (Hubei Institute for Heterogeneous Computing Applications)
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

"""Run metadata-driven C++17/C++20 D-SIMD and D-SIMT compile gates with BiSheng."""

from __future__ import annotations

import argparse
import json
import logging
import shutil
import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path


LOGGER = logging.getLogger(__name__)


@dataclass(frozen=True)
class CompileOptions:
    standard: str
    simt: bool
    expect_failure: bool = False


@dataclass(frozen=True)
class DeviceCompiler:
    executable: str
    include_root: Path
    test_root: Path
    npu_arch: str

    def compile(self, source: Path, output: Path, options: CompileOptions) -> str:
        command = [
            self.executable,
            "--asc-aicore-lang",
            f"--npu-arch={self.npu_arch}",
            f"-std={options.standard}",
            "-Werror",
            f"-I{self.include_root}",
            f"-I{self.test_root}",
        ]
        if options.simt:
            command.append("--enable-simt")
        command.extend(["-c", str(source), "-o", str(output)])
        process = subprocess.run(command, text=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, check=False)
        if options.expect_failure and process.returncode == 0:
            raise RuntimeError(f"negative Device case unexpectedly compiled: {source}")
        if not options.expect_failure and process.returncode != 0:
            raise RuntimeError(f"Device compile failed: {' '.join(command)}\n{process.stdout}")
        return process.stdout


def case_root(test_root: Path, target: str) -> Path:
    relative = target[:-2] if target.endswith(".h") else target
    return test_root / "cases" / relative


# Negative Device cases must fail with the diagnostic marker their exclusion
# contract defines. The default "deleted" marker covers removal-boundary
# cases; exclusion-specific markers are registered per case file.
NEGATIVE_DIAGNOSTIC_MARKERS = {
    "e_v_double_excluded.fail.asc": "static assertion",
    "e_v_long_double_excluded.fail.asc": "static assertion",
    "runtime_double.fail.asc": "double precision operation is not allowed in aicore function",
    "initializer_list_excluded.fail.asc": "no matching function",
    "simd_excluded.fail.asc": "__host__ function",
    "ub_span_dsimt.fail.asc": "ub_span",
}


def compile_header_matrix(
    device: DeviceCompiler, row: dict, index: int, standards: list[str], build_root: Path
) -> None:
    source = build_root / f"header-{index}.asc"
    source.write_text(f"#include <{row['target']}>\n#include <{row['target']}>\n", encoding="utf-8")
    for standard in standards:
        suffix = standard.replace("+", "x")
        for mode, simt in (("simd", False), ("simt", True)):
            output = build_root / f"header-{index}-{suffix}-{mode}.o"
            device.compile(source, output, CompileOptions(standard, simt))


def compile_semantic(
    device: DeviceCompiler, row: dict, index: int, standards: list[str], build_root: Path
) -> bool:
    if not row["applicability"]["device_compile"]:
        return False
    semantic = case_root(device.test_root, row["target"]) / "device.compile.asc"
    applicable = ["c++20"] if row["target"].startswith("asc/std/__concepts/") else standards
    for standard in applicable:
        suffix = standard.replace("+", "x")
        for mode, simt in (("simd", False), ("simt", True)):
            output = build_root / f"semantic-{index}-{suffix}-{mode}.o"
            device.compile(semantic, output, CompileOptions(standard, simt))
    return True


def negative_modes(target: str, name: str) -> tuple[tuple[str, bool], ...]:
    if name == "simd_excluded.fail.asc" or target == "asc/std/source_location":
        return (("simd", False),)
    if name == "ub_span_dsimt.fail.asc":
        return (("simt", True),)
    return (("simd", False), ("simt", True))


def compile_negatives(device: DeviceCompiler, row: dict, index: int, build_root: Path) -> None:
    target = row["target"]
    for name in row.get("negative_cases", []):
        negative = case_root(device.test_root, target) / name
        for mode, simt in negative_modes(target, name):
            output = device.compile(
                negative,
                build_root / f"negative-{index}-{mode}.o",
                CompileOptions("c++20", simt, expect_failure=True),
            )
            marker = NEGATIVE_DIAGNOSTIC_MARKERS.get(name, "deleted")
            expected = marker.lower() in output.lower()
            if target == "asc/std/source_location":
                expected = "cannot initialize a parameter" in output and "const char *" in output
            if not expected:
                raise RuntimeError(f"unexpected Device negative diagnostic for {negative}:\n{output}")


def run_cases(device: DeviceCompiler, rows: list[dict], standards: list[str]) -> int:
    semantic_count = 0
    with tempfile.TemporaryDirectory(prefix="asc-stl-device-") as value:
        build_root = Path(value)
        for index, row in enumerate(rows):
            compile_header_matrix(device, row, index, standards, build_root)
            semantic_count += compile_semantic(device, row, semantic_count, standards, build_root)
            compile_negatives(device, row, index, build_root)
    return semantic_count


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--include-root", type=Path, required=True)
    parser.add_argument("--test-root", type=Path, required=True)
    parser.add_argument("--npu-arch", required=True)
    parser.add_argument("--standards", nargs="+", default=["c++17", "c++20"])
    return parser.parse_args()


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    args = parse_args()

    compiler = shutil.which("bisheng")
    if compiler is None:
        raise RuntimeError("BiSheng compiler is unavailable in the loaded CANN environment")
    rows = json.loads(args.manifest.read_text(encoding="utf-8"))["headers"]
    device = DeviceCompiler(compiler, args.include_root, args.test_root, args.npu_arch)
    semantic_count = run_cases(device, rows, args.standards)

    LOGGER.info(
        f"PASS: {len(rows)} Headers self-include in C++17/C++20 D-SIMD/D-SIMT and "
        f"{semantic_count} target-derived Device semantic cases generate code in applicable modes"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
