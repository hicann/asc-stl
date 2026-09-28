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

"""Install ASC-STL and validate C++17/C++20 out-of-tree consumers."""

from __future__ import annotations

import argparse
import json
import logging
import subprocess
import tempfile
from pathlib import Path


LOGGER = logging.getLogger(__name__)


def run(command: list[str], *, cwd: Path | None = None) -> None:
    subprocess.run(command, cwd=cwd, check=True)


def install_product(source: Path, compiler: str, temporary: Path) -> Path:
    build = temporary / "product-build"
    prefix = temporary / "prefix"
    run([
        "cmake", "-S", str(source), "-B", str(build), "-DBUILD_TESTING=OFF",
        f"-DCMAKE_CXX_COMPILER={compiler}", f"-DCMAKE_INSTALL_PREFIX={prefix}",
    ])
    run(["cmake", "--build", str(build)])
    run(["cmake", "--install", str(build)])
    return prefix


def validate_installed_headers(prefix: Path, expected: set[str]) -> Path:
    root = prefix / "include"
    installed = {
        path.relative_to(root).as_posix()
        for path in (root / "asc").rglob("*")
        if path.is_file() and not path.name.startswith(".")
    }
    if installed != expected:
        raise RuntimeError(
            f"installed Header mismatch: missing={sorted(expected - installed)}, "
            f"extra={sorted(installed - expected)}"
        )
    return root


def run_cxx20_consumer(consumer: Path, compiler: str, prefix: Path, temporary: Path) -> None:
    build = temporary / "consumer-build"
    run([
        "cmake", "-S", str(consumer), "-B", str(build),
        f"-DCMAKE_CXX_COMPILER={compiler}", "-DCMAKE_CXX_STANDARD=20",
        "-DCMAKE_CXX_STANDARD_REQUIRED=ON", f"-DCMAKE_PREFIX_PATH={prefix}",
    ])
    run(["cmake", "--build", str(build)])
    run([str(build / "asc_stl_installed_consumer")])


def run_cxx17_consumer(compiler: str, root: Path, headers: list[str], temporary: Path) -> None:
    source = temporary / "installed-cxx17.cpp"
    source.write_text(
        "".join(f"#include <{header}>\n" for header in headers)
        + """
static_assert(__cplusplus >= 201703L && __cplusplus < 202002L, "expected C++17 mode");
static_assert(asc::std::ratio_equal_v<asc::std::ratio<1, 2>, asc::std::ratio<2, 4>>);
int main()
{
    return asc::std::source_location::current().line() == 0 ? 1 : 0;
}
""",
        encoding="utf-8",
    )
    program = temporary / "installed-cxx17"
    run([
        compiler, "-std=c++17", "-Wall", "-Wextra", "-Werror", "-pedantic",
        f"-I{root}", str(source), "-o", str(program),
    ])
    run([str(program)])


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    parser = argparse.ArgumentParser()
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--consumer", type=Path, required=True)
    parser.add_argument("--metadata", type=Path, required=True)
    parser.add_argument("--compiler", required=True)
    args = parser.parse_args()

    metadata = json.loads(args.metadata.read_text(encoding="utf-8"))
    expected = {row["target"] for row in metadata["headers"]}
    public = sorted(
        row["target"] for row in metadata["headers"] if row["visibility"] == "public"
    )

    with tempfile.TemporaryDirectory(prefix="asc-stl-install-") as value:
        temporary = Path(value)
        prefix = install_product(args.source.resolve(), args.compiler, temporary)
        installed_root = validate_installed_headers(prefix, expected)
        run_cxx20_consumer(args.consumer.resolve(), args.compiler, prefix, temporary)
        run_cxx17_consumer(args.compiler, installed_root, public, temporary)

    LOGGER.info(
        f"PASS: installed tree and C++17/C++20 out-of-tree consumers "
        f"({len(expected)} Headers)"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
