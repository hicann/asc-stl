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

import argparse
import json
import logging
import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path


LOGGER = logging.getLogger(__name__)


SHARED_ROOTS = {
    "asc/__detail/attributes.h",
    "asc/__detail/builtin.h",
    "asc/__detail/compiler.h",
    "asc/__detail/diagnostics.h",
    "asc/__detail/execution_space.h",
    "asc/__detail/feature_detection.h",
    "asc/__detail/preprocessor.h",
    "asc/__detail/visibility.h",
}

SYSTEM_HEADER_START = "#if defined(CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC)"


def validate_system_header_contract(include_root: Path, header: str) -> None:
    if header in SHARED_ROOTS:
        return
    lines = (include_root / header).read_text(encoding="utf-8").splitlines()
    anchor = (
        "#include <asc/__detail/compiler.h>"
        if header == "asc/__config"
        else "#include <asc/__config>"
    )
    if anchor not in lines or SYSTEM_HEADER_START not in lines:
        raise ValueError(f"{header}: missing system-header anchor or conditional block")
    if lines.index(SYSTEM_HEADER_START) != lines.index(anchor) + 2:
        raise ValueError(f"{header}: conditional system-header block is misplaced")


@dataclass(frozen=True)
class HostCompiler:
    executable: str
    include_root: Path

    def compile(self, standard: str, source: Path, output: Path, definitions: list[str]) -> None:
        command = [
            self.executable,
            f"-std={standard}",
            "-Wall",
            "-Wextra",
            "-Werror",
            "-pedantic",
            f"-I{self.include_root}",
            *[f"-D{definition}" for definition in definitions],
            "-c",
            str(source),
            "-o",
            str(output),
        ]
        subprocess.run(command, check=True)


def run_header_checks(
    compiler: HostCompiler, headers: list[dict], standards: list[str], root: Path
) -> None:
    for index, row in enumerate(headers):
        header = row["target"]
        validate_system_header_contract(compiler.include_root, header)
        source = root / f"header_{index}.cpp"
        source.write_text(
            f"#include <{header}>\n#include <{header}>\nint main() {{ return 0; }}\n",
            encoding="utf-8",
        )
        for standard in standards:
            suffix = standard.replace("+", "x")
            compiler.compile(standard, source, root / f"header_{index}_{suffix}.o", [])
            if header not in SHARED_ROOTS:
                definitions = ["CANN_ASC_STL_DETAIL_IMPLICIT_SYSTEM_HEADER_GCC=1"]
                compiler.compile(standard, source, root / f"system_{index}_{suffix}.o", definitions)


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    parser = argparse.ArgumentParser()
    parser.add_argument("--metadata", type=Path, required=True)
    parser.add_argument("--include", type=Path, required=True)
    parser.add_argument("--compiler", required=True)
    parser.add_argument("--standards", nargs="+", default=["c++17", "c++20"])
    args = parser.parse_args()
    headers = json.loads(args.metadata.read_text(encoding="utf-8"))["headers"]
    compiler = HostCompiler(args.compiler, args.include)

    with tempfile.TemporaryDirectory(prefix="asc_stl_self_contained_") as value:
        run_header_checks(compiler, headers, args.standards, Path(value))
    modes = ", ".join(args.standards)
    LOGGER.info(
        "PASS: %d repeated-include and system-header Host checks in %s",
        len(headers),
        modes,
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
