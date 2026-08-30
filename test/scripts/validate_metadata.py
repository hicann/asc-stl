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

import argparse
import json
import logging
from pathlib import Path


LOGGER = logging.getLogger(__name__)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument("--include-root", type=Path, required=True)
    parser.add_argument("--metadata", type=Path, required=True)
    return parser.parse_args()


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    args = parse_args()
    document = json.loads(args.metadata.read_text(encoding="utf-8"))
    if document.get("schema_version") != 2:
        raise ValueError("headers.json must use schema_version 2")

    entries = document.get("headers")
    if not isinstance(entries, list):
        raise TypeError("headers must be a list")

    registered = []
    for entry in entries:
        if not isinstance(entry, dict) or not isinstance(entry.get("target"), str):
            raise TypeError("each Header entry must contain a string target")
        target = entry["target"]
        if not target.startswith("asc/"):
            raise ValueError(f"Header target must be below asc/: {target}")
        registered.append(target)

    if len(registered) != len(set(registered)):
        raise ValueError("Header targets must be unique")

    discovered = sorted(
        f"asc/{path.relative_to(args.include_root).as_posix()}"
        for path in args.include_root.rglob("*")
        if path.is_file() and not path.name.startswith(".")
    )
    if sorted(registered) != discovered:
        raise ValueError(
            "Header metadata does not match include/asc: "
            f"registered={sorted(registered)}, discovered={discovered}"
        )

    if not registered:
        LOGGER.info("NOT_APPLICABLE: no product Headers are registered.")
    else:
        LOGGER.info("Validated %d product Headers.", len(registered))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
