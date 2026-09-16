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

"""Validate language-baseline and explicitly empty compatibility boundaries."""

from __future__ import annotations

import argparse
import logging
import subprocess
import tempfile
from pathlib import Path


LOGGER = logging.getLogger(__name__)


def compile_source(
    compiler: str, include: Path, source: Path, output: Path, standard: str
) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        [
            compiler, f"-std={standard}", "-Wall", "-Wextra", "-Werror",
            f"-I{include}", "-c", str(source), "-o", str(output),
        ],
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        check=False,
    )


def validate_compile_failures(compiler: str, include: Path, test_root: Path, temporary: Path) -> None:
    cases = (
        ("cases/asc/__atomic/scoped_atomic/unsupported_type.fail.cpp", "supports exactly"),
        ("cases/asc/atomic/host_call.fail.cpp", "deleted"),
        ("cases/asc/std/__functional/reference_wrapper/rvalue.fail.cpp", "deleted"),
        ("cases/asc/std/__variant/variant_constraints/reference_alternative.fail.cpp", "static assertion"),
        ("cases/asc/std/__complex/arg/unsupported_double.fail.cpp", "static assertion"),
        ("cases/asc/execution.require/invalid_requirement_type.fail.cpp", "no matching function"),
        ("cases/asc/execution.policy/implicit_resource.fail.cpp", "no matching function"),
        ("cases/asc/hierarchy/host_query.fail.cpp", "block_index"),
        ("cases/asc/std/__charconv/to_chars/float.fail.cpp", "ambiguous"),
        ("cases/asc/std/__charconv/to_chars/chars_format.fail.cpp", "chars_format"),
        ("cases/asc/std/__charconv/to_chars/result_bool.fail.cpp", "convert"),
    )
    for index, (relative, marker) in enumerate(cases):
        negative = test_root / relative
        process = compile_source(compiler, include, negative, temporary / f"negative-{index}.o", "c++20")
        if process.returncode == 0 or marker not in process.stdout.lower():
            raise RuntimeError(f"negative boundary was not rejected ({marker}): {negative}\n{process.stdout}")


def validate_empty_headers(compiler: str, include: Path, temporary: Path) -> None:
    source = temporary / "empty_compat.cpp"
    source.write_text(
        """
#include <asc/std/ciso646>
#include <asc/std/cstdalign>
#include <asc/std/cstdbool>
#if defined(__alignas_is_defined) || defined(__bool_true_false_are_defined)
#  error "legacy C compatibility macro leaked into C++20"
#endif
int main() { return 0; }
""",
        encoding="utf-8",
    )
    subprocess.run(
        [
            compiler, "-std=c++20", "-Wall", "-Wextra", "-Werror",
            f"-I{include}", str(source), "-o", str(temporary / "empty_compat"),
        ],
        check=True,
    )


def main() -> int:
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    parser = argparse.ArgumentParser()
    parser.add_argument("--include", type=Path, required=True)
    parser.add_argument("--test-root", type=Path, required=True)
    parser.add_argument("--compiler", required=True)
    args = parser.parse_args()

    with tempfile.TemporaryDirectory(prefix="asc-stl-negative-") as value:
        temporary = Path(value)
        source = temporary / "cxx17.cpp"
        source.write_text("#include <asc/__config>\nint main() { return 0; }\n", encoding="utf-8")
        process = compile_source(args.compiler, args.include, source, source.with_suffix(".o"), "c++17")
        if process.returncode != 0:
            raise RuntimeError(f"C++17 consumer was rejected by the minimum baseline:\n{process.stdout}")

        source.write_text("#include <asc/__config>\nint main() { return 0; }\n", encoding="utf-8")
        process = compile_source(args.compiler, args.include, source, source.with_suffix(".o"), "c++14")
        if process.returncode == 0 or "ASC-STL requires C++17 or newer" not in process.stdout:
            raise RuntimeError("pre-C++17 consumer was not rejected by the frozen baseline")

        validate_empty_headers(args.compiler, args.include, temporary)
        validate_compile_failures(args.compiler, args.include, args.test_root, temporary)

    LOGGER.info(
        "PASS: C++17 baseline, pre-C++17 rejection, empty compatibility, and compile-failure boundaries"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
