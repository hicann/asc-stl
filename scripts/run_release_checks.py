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

"""Run selected supplemental release checks with source-bound, per-stage evidence."""
from __future__ import annotations

import argparse
import json
import logging
import os
from pathlib import Path
import shutil
import subprocess
import sys
import time

LOGGER = logging.getLogger(__name__)


def source_identity(root: Path) -> dict:
    git_executable = shutil.which("git")
    if git_executable is None:
        raise FileNotFoundError("Git executable is unavailable")
    git_executable = str(Path(git_executable).resolve())
    values = {}
    for key, arguments in (("commit", ["rev-parse", "HEAD"]), ("tree", ["rev-parse", "HEAD^{tree}"]),
                           ("git_status", ["status", "--porcelain", "--untracked-files=normal"])):
        result = subprocess.run([git_executable, "-C", str(root), *arguments],
                                capture_output=True, text=True, check=True)
        values[key] = result.stdout.strip()
    return values


def docs_commands(args: argparse.Namespace, modes: tuple[str, ...]) -> list[tuple]:
    commands = []
    checker = args.root / "scripts/check_api_docs.py"
    for standard in (17, 20):
        for mode in modes:
            label = f"docs-{mode}-cxx{standard}"
            compiler = args.compiler if mode in ("host", "runtime") else args.device_compiler
            command = [sys.executable, str(checker), "--examples", "--require-all", "--standard", str(standard),
                       "--mode", mode, "--compiler", compiler, "--jobs", str(args.jobs),
                       "--npu-arch", args.npu_arch, "--report", str(args.report_dir / f"{label}.json")]
            commands.append((label, command))
    return commands


def stage_commands(args: argparse.Namespace) -> list[tuple]:
    commands = []
    if "docs" in args.stage:
        commands.append(("docs-structure", [sys.executable, str(args.root / "scripts/check_api_docs.py"),
                                           "--report", str(args.report_dir / "docs-structure.json")]))
        commands.extend(docs_commands(args, ("host", "simd", "simt")))
    if "memory" in args.stage:
        commands.append(("memory-safety", ["bash", str(args.root / "scripts/ci-memory-safety-check.sh")]))
    if "acceptance" in args.stage:
        commands.append(("user-acceptance", [sys.executable, str(args.root / "scripts/run_user_acceptance.py"),
                                             "--compiler", args.compiler, "--report-dir",
                                             str(args.report_dir / "user-acceptance")]))
    if "runtime" in args.stage:
        commands.append(("hardware-preflight", [sys.executable, str(args.root / "scripts/hardware_device.py")]))
        commands.extend(docs_commands(args, ("runtime",)))
    return commands


def execute_stage(args: argparse.Namespace, label: str, command: list[str]) -> dict:
    log = args.report_dir / f"{label}.log"
    environment = os.environ.copy()
    environment["CXX"] = args.compiler
    environment["ASC_STL_MEMORY_SAFETY_BUILD_DIR"] = str(args.report_dir / "memory-safety")
    started = time.monotonic()
    with log.open("w", encoding="utf-8") as stream:
        result = subprocess.run(command, cwd=args.root, stdout=stream, stderr=subprocess.STDOUT,
                                env=environment, check=False)
    status = "PASS" if result.returncode == 0 else "FAIL"
    output = log.read_text(encoding="utf-8")
    if result.returncode == 77:
        status = "NOT_APPLICABLE"
    elif result.returncode and "BLOCKED_ENVIRONMENT:" in output:
        status = "BLOCKED_ENVIRONMENT"
    return {"name": label, "command": command, "status": status, "returncode": result.returncode,
            "duration_seconds": round(time.monotonic() - started, 3), "log": str(log)}


def run_stages(args: argparse.Namespace, before: dict) -> dict:
    results = []
    stopped = False
    for label, command in stage_commands(args):
        if stopped:
            results.append({"name": label, "command": command, "status": "NOT_RUN"})
            continue
        LOGGER.info("Running supplemental release check: %s", label)
        result = execute_stage(args, label, command)
        results.append(result)
        LOGGER.info("%s: %s (%ss)", result["status"], label, result["duration_seconds"])
        # Selected release stages require complete evidence, including environment prerequisites.
        stopped = result["status"] != "PASS"
    after = source_identity(args.root)
    passed = bool(results) and all(row["status"] == "PASS" for row in results) and before == after
    return {"schema_version": 1, "scope": args.scope, "selected_stages": args.stage, "passed": passed,
            "validation_claim": "Selected supplemental checks only; full product gate is independently required",
            "source_before": before, "source_after": after, "source_unchanged": before == after,
            "results": results}


def parse_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    parser.add_argument("--scope", choices=("software", "hardware"), required=True)
    parser.add_argument("--stage", choices=("docs", "memory", "acceptance", "runtime"), action="append")
    parser.add_argument("--report-dir", type=Path, required=True)
    parser.add_argument("--compiler", default=os.environ.get("CXX", "c++"))
    parser.add_argument("--device-compiler", default="bisheng")
    parser.add_argument("--npu-arch", default=os.environ.get("ASC_STL_NPU_ARCH", "dav-3510"))
    parser.add_argument("--jobs", type=int, default=4)
    args = parser.parse_args()
    args.root = args.root.resolve()
    args.report_dir = args.report_dir.resolve()
    allowed = ("docs", "memory", "acceptance") if args.scope == "software" else ("runtime",)
    args.stage = list(dict.fromkeys(args.stage or allowed))
    if args.jobs < 1 or any(stage not in allowed for stage in args.stage):
        parser.error("positive --jobs and stages matching --scope are required")
    return args


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    args = parse_arguments()
    before = source_identity(args.root)
    if before["git_status"]:
        LOGGER.error("Release checks require a clean, committed product checkout")
        return 2
    args.report_dir.mkdir(parents=True, exist_ok=False)
    report = run_stages(args, before)
    (args.report_dir / "summary.json").write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n")
    LOGGER.info("Supplemental release results: %s", args.report_dir / "summary.json")
    return 0 if report["passed"] else 1


if __name__ == "__main__":
    raise SystemExit(main())
