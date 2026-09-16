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

"""Compare observed product includes with product-only dependency metadata."""

from __future__ import annotations

import argparse
import json
import logging
import re
from pathlib import Path


LOGGER = logging.getLogger(__name__)


INCLUDE_PATTERN = re.compile(r"^\s*#\s*include\s*<(?P<target>asc/[^>]+)>", re.MULTILINE)


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    parser = argparse.ArgumentParser()
    parser.add_argument("--headers", type=Path, required=True)
    parser.add_argument("--include", type=Path, required=True)
    args = parser.parse_args()

    header_data = json.loads(args.headers.read_text(encoding="utf-8"))
    registered = {row["target"] for row in header_data["headers"]}
    expected = {
        (row["target"], dependency)
        for row in header_data["headers"]
        for dependency in row["dependencies"]
    }
    observed: set[tuple[str, str]] = set()
    for source in registered:
        text = (args.include / source).read_text(encoding="utf-8")
        observed.update((source, match.group("target")) for match in INCLUDE_PATTERN.finditer(text))

    if observed != expected:
        missing = sorted(expected - observed)
        extra = sorted(observed - expected)
        raise RuntimeError(f"observed dependency mismatch: missing={missing}, extra={extra}")
    LOGGER.info("PASS: %d observed product Header dependency edges", len(expected))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
