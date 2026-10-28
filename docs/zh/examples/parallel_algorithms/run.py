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

"""Run each example in a bounded, separately recorded process; stop on failure."""

from __future__ import annotations

import argparse
import hashlib
import json
import logging
import math
import os
from pathlib import Path
import signal
import subprocess
import time
from dataclasses import dataclass

LOGGER = logging.getLogger(__name__)
KILL_REAP_TIMEOUT = 5


@dataclass(frozen=True)
class Settings:
    binary: Path
    report_dir: Path
    timeout: float
    grace: float
    standard: int


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def stop_group(process: subprocess.Popen, requested: int) -> None:
    try:
        os.killpg(process.pid, requested)
    except ProcessLookupError:
        return


def collect_after_kill(process: subprocess.Popen, reason: str) -> tuple[str, str]:
    stop_group(process, signal.SIGKILL)
    try:
        return process.communicate(timeout=KILL_REAP_TIMEOUT)[0], reason + ":SIGKILL"
    except subprocess.TimeoutExpired as error:
        # A device ioctl may keep a killed process uninterruptible.
        # Preserve the partial log without claiming process termination.
        output = error.output or ""
        if isinstance(output, bytes):
            output = output.decode(errors="replace")
        if process.stdout is not None:
            process.stdout.close()
        return output, reason + ":SIGKILL_UNREAPED"


def collect(process: subprocess.Popen, settings: Settings) -> tuple[str, str]:
    try:
        return process.communicate(timeout=settings.timeout)[0], "none"
    except (subprocess.TimeoutExpired, KeyboardInterrupt) as error:
        reason = "interrupt" if isinstance(error, KeyboardInterrupt) else "deadline"
        stop_group(process, signal.SIGTERM)
        try:
            output = process.communicate(timeout=settings.grace)[0]
            return output, reason + ":SIGTERM"
        except subprocess.TimeoutExpired:
            return collect_after_kill(process, reason)


def run_case(settings: Settings, case: dict) -> dict:
    started = time.monotonic()
    command = [str(settings.binary), str(case["index"])]
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               text=True, start_new_session=True)
    output, termination = collect(process, settings)
    (settings.report_dir / (case["name"] + ".log")).write_text(output)
    passed = process.returncode == 0 and termination == "none"
    return {"case": case["name"], "command": command, "returncode": process.returncode,
            "termination": termination, "process_exited": process.returncode is not None,
            "seconds": time.monotonic() - started,
            "passed": passed, "log": case["name"] + ".log"}


def preflight(settings: Settings, expected_count: int) -> dict:
    command = [str(settings.binary), "--describe"]
    process = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.STDOUT,
                               text=True, start_new_session=True)
    probe = Settings(settings.binary, settings.report_dir, 10, settings.grace, settings.standard)
    output, termination = collect(process, probe)
    (settings.report_dir / "preflight.log").write_text(output)
    facts = {}
    for line in output.splitlines():
        try:
            value = json.loads(line)
            if isinstance(value, dict) and "case_count" in value:
                facts = value
        except json.JSONDecodeError:
            continue
    expected_mode = 201703 if settings.standard == 17 else 202002
    passed = process.returncode == 0 and termination == "none" and facts.get("case_count") == expected_count
    passed = passed and facts.get("cplusplus") == expected_mode
    return {"passed": passed, "returncode": process.returncode, "facts": facts,
            "termination": termination, "log": "preflight.log", "command": command}


def save_report(settings: Settings, report: dict) -> None:
    (settings.report_dir / "results.json").write_text(json.dumps(report, indent=2) + "\n")


def parse_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--binary", required=True, type=Path)
    parser.add_argument("--report-dir", required=True, type=Path)
    parser.add_argument("--standard", required=True, type=int, choices=(17, 20))
    parser.add_argument("--case", help="Run only this named case; does not claim full coverage")
    parser.add_argument("--process-timeout", type=float, default=40)
    parser.add_argument("--cleanup-grace", type=float, default=15)
    args = parser.parse_args()
    if not math.isfinite(args.process_timeout) or args.process_timeout <= 0:
        parser.error("Deadlines must be finite positive numbers")
    if not math.isfinite(args.cleanup_grace) or args.cleanup_grace <= 0:
        parser.error("Deadlines must be finite positive numbers")
    return args


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    args = parse_arguments()
    manifest = Path(__file__).with_name("cases.json")
    cases = json.loads(manifest.read_text())
    selected = [case for case in cases if not args.case or case["name"] == args.case]
    if not selected:
        raise SystemExit("Unknown case: " + str(args.case))
    settings = Settings(args.binary.resolve(), args.report_dir.resolve(), args.process_timeout,
                        args.cleanup_grace, args.standard)
    settings.report_dir.mkdir(parents=True, exist_ok=False)
    report = {"scope": "single_case" if args.case else "all_cases", "requested": len(selected),
              "standard": args.standard, "binary_sha256": digest(settings.binary),
              "manifest_sha256": digest(manifest), "script_sha256": digest(Path(__file__)), "cases": []}
    save_report(settings, report)
    report["preflight"] = preflight(settings, len(cases))
    save_report(settings, report)
    if not report["preflight"]["passed"]:
        return 1
    for case in selected:
        result = run_case(settings, case)
        report["cases"].append(result)
        report["passed"] = len(report["cases"]) == len(selected) and all(row["passed"] for row in report["cases"])
        save_report(settings, report)
        LOGGER.info("%s: %s", case["name"], "PASS" if result["passed"] else "FAIL; stopping")
        if not result["passed"]:
            return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
