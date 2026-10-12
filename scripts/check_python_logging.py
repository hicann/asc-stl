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

"""Reject direct Python print calls to mirror the official G.LOG.02 rule."""

from __future__ import annotations

import ast
import logging
import sys
from pathlib import Path


LOGGER = logging.getLogger(__name__)


def direct_print_calls(path: Path) -> list[int]:
    tree = ast.parse(path.read_text(encoding="utf-8"), filename=str(path))
    return sorted(
        node.lineno
        for node in ast.walk(tree)
        if isinstance(node, ast.Call)
        and (
            isinstance(node.func, ast.Name)
            and node.func.id == "print"
            or isinstance(node.func, ast.Attribute)
            and isinstance(node.func.value, ast.Name)
            and node.func.value.id == "builtins"
            and node.func.attr == "print"
        )
    )


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    violations = [
        (path, line)
        for value in sys.argv[1:]
        for path in (Path(value),)
        if path.is_file()
        for line in direct_print_calls(path)
    ]
    for path, line in violations:
        LOGGER.error("%s:%d: direct print() call; use the logging module", path, line)
    if violations:
        return 1
    LOGGER.info("Python logging check passed (%d files)", len(sys.argv) - 1)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
