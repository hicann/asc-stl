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

"""Bound one hardware process, including cleanup, without retrying a failed device."""

import argparse
import logging
import os
from pathlib import Path
import signal
import subprocess
import sys
import time


LOGGER = logging.getLogger(__name__)
STOP_SIGNAL = 0


def request_stop(signum, _frame):
    global STOP_SIGNAL
    STOP_SIGNAL = signum


def positive_seconds(value):
    result = float(value)
    if not 0 < result < float("inf"):
        raise argparse.ArgumentTypeError("must be a finite positive number")
    return result


def signal_group(process, signum):
    try:
        os.killpg(process.pid, signum)
    except ProcessLookupError:
        pass
    except PermissionError as error:
        LOGGER.error("HARDWARE_SAFETY: cannot signal process group: %s", error)


def group_exists(process):
    process.poll()
    try:
        os.killpg(process.pid, 0)
        return True
    except ProcessLookupError:
        return False
    except PermissionError:
        return True


def stop_process(process, grace):
    signal_group(process, signal.SIGTERM)
    deadline = time.monotonic() + grace
    while group_exists(process) and time.monotonic() < deadline:
        time.sleep(min(0.05, max(0, deadline - time.monotonic())))
    if group_exists(process):
        LOGGER.warning("HARDWARE_SAFETY: cleanup grace expired; sending SIGKILL")
        signal_group(process, signal.SIGKILL)
    try:
        process.wait(timeout=2)
    except subprocess.TimeoutExpired:
        LOGGER.error("HARDWARE_SAFETY: process did not exit after SIGKILL; device state unknown")
    if group_exists(process):
        LOGGER.error("HARDWARE_SAFETY: process group remains; device release is not verified")


def wait_process(process, args):
    deadline = time.monotonic() + args.timeout
    while process.poll() is None:
        if STOP_SIGNAL or time.monotonic() >= deadline:
            reason = f"signal={STOP_SIGNAL}" if STOP_SIGNAL else "case timeout"
            LOGGER.warning("HARDWARE_SAFETY: %s; stopping this case and the suite", reason)
            stop_process(process, args.grace)
            return 128 + STOP_SIGNAL if STOP_SIGNAL else 124
        try:
            process.wait(timeout=min(0.1, max(0.001, deadline - time.monotonic())))
        except subprocess.TimeoutExpired:
            continue
    if group_exists(process):
        LOGGER.warning("HARDWARE_SAFETY: process left descendants; stopping the suite")
        stop_process(process, args.grace)
        return 125
    return 128 + STOP_SIGNAL if STOP_SIGNAL else process.returncode


def run_case(args):
    args.log.parent.mkdir(parents=True, exist_ok=True)
    previous = {signum: signal.signal(signum, request_stop) for signum in (signal.SIGTERM, signal.SIGINT)}
    try:
        with args.log.open("wb") as log:
            process = subprocess.Popen(args.command, stdout=log, stderr=subprocess.STDOUT, start_new_session=True)
            LOGGER.info("HARDWARE_SAFETY: pid=%s timeout=%ss log=%s", process.pid, args.timeout, args.log)
            try:
                status = wait_process(process, args)
            except BaseException:
                stop_process(process, args.grace)
                raise
    finally:
        for signum, handler in previous.items():
            signal.signal(signum, handler)
    output = args.log.read_text(encoding="utf-8", errors="replace")
    if output:
        LOGGER.info("%s", output[:-1] if output.endswith("\n") else output)
    if status != args.expected_exit:
        LOGGER.error("FAIL: hardware process exit=%s, expected=%s", status, args.expected_exit)
        return status if 0 < status < 256 else 1
    if args.expected_marker and args.expected_marker not in output.splitlines():
        LOGGER.error("FAIL: expected hardware result marker is absent")
        return 1
    return 0


def main():
    logging.basicConfig(level=logging.INFO, format="%(message)s", stream=sys.stdout)
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--timeout", type=positive_seconds, default=120)
    parser.add_argument("--grace", type=positive_seconds, default=20)
    parser.add_argument("--log", required=True, type=Path)
    parser.add_argument("--expected-exit", type=int, choices=(0, 42), default=0)
    parser.add_argument("--expected-marker", default="")
    parser.add_argument("command", nargs=argparse.REMAINDER)
    args = parser.parse_args()
    if args.command and args.command[0] == "--":
        args.command = args.command[1:]
    if not args.command:
        parser.error("a hardware executable is required")
    if args.expected_exit == 42 and not args.expected_marker:
        parser.error("expected semantic failure requires an exact result marker")
    return run_case(args)


if __name__ == "__main__":
    raise SystemExit(main())
