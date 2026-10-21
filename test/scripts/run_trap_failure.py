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

"""Require an assertion/trap signal from an isolated Host boundary case."""

from __future__ import annotations

import logging
import resource
import signal
import subprocess
import sys


LOGGER = logging.getLogger(__name__)


def disable_core_dump() -> None:
    resource.setrlimit(resource.RLIMIT_CORE, (0, 0))


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    process = subprocess.run(
        [sys.argv[1]], stdout=subprocess.PIPE, stderr=subprocess.PIPE,
        check=False, timeout=10, preexec_fn=disable_core_dump,
    )
    expected = {-signal.SIGABRT, -signal.SIGILL, -signal.SIGTRAP}
    if process.returncode not in expected:
        LOGGER.error("Expected an assertion/trap signal, observed return code %d", process.returncode)
        return 1
    LOGGER.info("PASS: isolated boundary terminated with signal %d", -process.returncode)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
