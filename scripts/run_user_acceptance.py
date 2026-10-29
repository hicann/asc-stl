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

"""Run observable Host user workloads and record scoped reference timings."""
from __future__ import annotations

import argparse
import hashlib
import json
import logging
import os
from pathlib import Path
import platform
import shutil
import statistics
import subprocess


LOGGER = logging.getLogger(__name__)
SCENARIOS = {"sort_records_32768", "vector_growth_65536", "matrix_update_256x256"}


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def machine_context() -> dict:
    cpuinfo = Path("/proc/cpuinfo")
    model = platform.processor()
    if cpuinfo.is_file():
        model = next((line.split(":", 1)[1].strip() for line in cpuinfo.read_text().splitlines()
                      if line.startswith("model name")), model)
    return {"hostname": platform.node(), "platform": platform.platform(), "cpu_model": model,
            "cpu_count": os.cpu_count(), "load_average": os.getloadavg() if hasattr(os, "getloadavg") else None,
            "cpu_affinity": sorted(os.sched_getaffinity(0)) if hasattr(os, "sched_getaffinity") else None}


def source_identity(root: Path) -> dict:
    git_executable = shutil.which("git")
    if git_executable is None:
        raise FileNotFoundError("Git executable is unavailable")
    git_executable = str(Path(git_executable).resolve())

    def git(*args):
        return subprocess.check_output([git_executable, "-C", str(root), *args], text=True).strip()
    headers = sorted((root / "include" / "asc").rglob("*"))
    content = hashlib.sha256()
    for path in headers:
        if path.is_file():
            content.update(path.relative_to(root).as_posix().encode() + b"\0" + path.read_bytes())
    return {"commit": git("rev-parse", "HEAD"), "tree": git("rev-parse", "HEAD^{tree}"),
            "git_status": git("status", "--porcelain"), "headers_sha256": content.hexdigest(),
            "workload_sha256": digest(root / "test/acceptance/host_workloads.cpp"),
            "runner_sha256": digest(Path(__file__))}


def execute(command: list[str], log: Path, timeout: float) -> subprocess.CompletedProcess:
    try:
        result = subprocess.run(command, text=True, capture_output=True, check=False, timeout=timeout)
    except subprocess.TimeoutExpired as error:
        chunks = [value.decode(errors="replace") if isinstance(value, bytes) else value or ""
                  for value in (error.stdout, error.stderr)]
        log.write_text("".join(chunks), encoding="utf-8")
        raise RuntimeError(f"command timed out after {timeout}s, see {log}") from error
    log.write_text(result.stdout + result.stderr, encoding="utf-8")
    if result.returncode:
        raise RuntimeError(f"command failed ({result.returncode}), see {log}")
    return result


def validate_samples(text: str, samples: int, implementation: str) -> list[dict]:
    rows = [json.loads(line) for line in text.splitlines()]
    required = {"scenario", "sample", "implementation", "elapsed_ns", "checksum"}
    if any(not isinstance(row, dict) or not required.issubset(row) for row in rows):
        raise ValueError("malformed workload sample")
    if any(not isinstance(row[key], int) for row in rows for key in ("sample", "elapsed_ns", "checksum")):
        raise ValueError("noninteger workload sample")
    expected = {(name, sample) for name in SCENARIOS for sample in range(samples)}
    observed = [(row["scenario"], row["sample"]) for row in rows]
    if len(observed) != len(expected) or set(observed) != expected:
        raise ValueError("missing, duplicate or unexpected workload samples")
    if any(row["elapsed_ns"] <= 0 or row["implementation"] != implementation for row in rows):
        raise ValueError("invalid duration or implementation identity")
    return rows


def run_variant(args: argparse.Namespace, standard: int, reference: bool) -> dict:
    name = "std_and_raw_index" if reference else "asc_stl"
    stem = f"{name}-cxx{standard}"
    binary = args.report_dir / stem
    command = [args.compiler, f"-std=c++{standard}", "-O3", "-Wall", "-Wextra", "-Werror", "-pedantic",
               "-I", str(args.root / "include"), str(args.root / "test/acceptance/host_workloads.cpp"),
               "-o", str(binary)]
    if reference:
        command.append("-DASC_STL_ACCEPTANCE_REFERENCE=1")
    execute(command, args.report_dir / f"{stem}-compile.log", 120)
    run_command = [str(binary), str(args.samples)]
    result = execute(run_command, args.report_dir / f"{stem}-run.log", 120)
    rows = validate_samples(result.stdout, args.samples, name)
    return {"standard": standard, "implementation": name, "compile_command": command,
            "run_command": run_command, "compile_returncode": 0, "run_returncode": result.returncode,
            "binary_sha256": digest(binary), "samples": rows}


def comparisons(runs: list[dict]) -> list[dict]:
    result = []
    for standard in (17, 20):
        for scenario in sorted(SCENARIOS):
            selected = [run for run in runs if run["standard"] == standard]
            rows = {run["implementation"]: [row for row in run["samples"] if row["scenario"] == scenario]
                    for run in selected}
            checksums = {row["checksum"] for values in rows.values() for row in values}
            if len(checksums) != 1:
                raise ValueError(f"differential result mismatch: C++{standard} {scenario}")
            medians = {name: statistics.median(row["elapsed_ns"] for row in values)
                       for name, values in rows.items()}
            result.append({"standard": standard, "scenario": scenario, "median_ns": medians,
                           "asc_over_reference": medians["asc_stl"] / medians["std_and_raw_index"],
                           "checksum": checksums.pop()})
    return result


def arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument("--compiler", default=os.environ.get("CXX", "g++"))
    parser.add_argument("--samples", type=int, default=7)
    parser.add_argument("--report-dir", type=Path, required=True)
    args = parser.parse_args()
    if not 3 <= args.samples <= 101:
        parser.error("--samples must be between 3 and 101")
    args.compiler = shutil.which(args.compiler)
    if not args.compiler:
        parser.error("Host compiler is unavailable")
    args.root = args.root.resolve()
    args.report_dir = args.report_dir.resolve()
    return args


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    args = arguments()
    args.report_dir.mkdir(parents=True, exist_ok=False)
    before = source_identity(args.root)
    report = {"scope": "Host user workloads only; no Device/Runtime or universal performance claim",
              "identity_before": before, "machine": machine_context(), "compiler": args.compiler,
              "compiler_version": subprocess.check_output([args.compiler, "--version"], text=True),
              "timing_scope": "whole workload including allocation, initialization and element/golden checking",
              "performance_threshold": None, "warmups": 1, "samples_per_workload": args.samples,
              "passed": False, "runs": []}
    try:
        for standard in (17, 20):
            for reference in (True, False):
                report["runs"].append(run_variant(args, standard, reference))
        report["comparisons"] = comparisons(report["runs"])
        report["identity_after"] = source_identity(args.root)
        report["passed"] = before == report["identity_after"]
    except (OSError, ValueError, TypeError, KeyError, RuntimeError, subprocess.SubprocessError) as error:
        report["error"] = str(error)
    (args.report_dir / "report.json").write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
    LOGGER.info("Host user acceptance: %s; report: %s", "PASS" if report["passed"] else "FAIL", args.report_dir)
    return 0 if report["passed"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
