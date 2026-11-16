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

"""Compile the product version contract in C++17/C++20 and each execution mode."""
import argparse
import json
import logging
from pathlib import Path
import shutil
import tempfile

from test_std_version import Matrix, Options, family, includes

LOGGER = logging.getLogger(__name__)
NAMES = ("CANN_ASC_STL", "CANN_ASC_STL_HAS_PIPELINE", "CANN_ASC_STL_HAS_NUMERIC_TYPES", "CANN_ASC_STL_HAS_CACHE")
RETIRED = ("CANN_ASC_STL_VERSION", "CANN_ASC_STL_VERSION_MAJOR", "CANN_ASC_STL_VERSION_MINOR",
           "CANN_ASC_STL_VERSION_PATCH", "CANN_ASC_STL_HAS_DEVICE_POLICY", "CANN_ASC_STL_HAS_COLLECTIVES")


def exports(macros):
    if any(name in macros for name in RETIRED):
        raise AssertionError("Retired version or extension flags are still exposed")
    return {name: macros.get(name) for name in NAMES}


def contract_source(expected):
    source = includes(["asc/version"])
    for name in NAMES:
        source += f"#if !defined({name}) || {name} != {expected[name]}\n#error \"{name} value\"\n#endif\n"
        source += f"static_assert({name} == {expected[name]});\n"
    for name in NAMES[1:]:
        source += f"#if {name}\nstatic_assert({expected[name]} == 1);\n"
        source += f"#else\nstatic_assert({expected[name]} == 0);\n#endif\n"
    source += "static_assert(CANN_ASC_STL_LIB_type_identity == 201806L);\n"
    source += "static_assert(20261231 < 20270101 && 20260131 < 20260201);\n"
    return source


def check_includes(matrix, standard, expected):
    baseline = matrix.run("standard-version", includes(["asc/std/version"]), standard)
    headers = ("asc/std/version", "asc/__version/product.h", "asc/pipeline")
    for header in headers:
        for order, sequence in enumerate(((header, "asc/version"), ("asc/version", header, "asc/version"))):
            actual = matrix.run(f"include-order-{Path(header).name}-{order}", includes(sequence), standard)
            assert exports(actual) == expected
    for order, source in enumerate((includes(["asc/version"]), includes(["asc/version"] * 2))):
        actual = matrix.run(f"standalone-{order}", source, standard)
        assert exports(actual) == expected
        assert family(actual, "CANN_ASC_STL_LIB_") == family(baseline, "CANN_ASC_STL_LIB_")
    matrix.run("contract", contract_source(expected), standard, Options(preprocess=False))


def check_date_and_host(matrix, standard, expected):
    for index, build_date in enumerate(('"Jan  1 2000"', '"Dec 31 2099"')):
        flags = ("-Wno-builtin-macro-redefined", "-D__DATE__=" + build_date)
        actual = matrix.run(f"build-date-{index}", includes(["asc/version"]), standard, Options(flags=flags))
        assert exports(actual) == expected
    sentinel = "#define __cpp_lib_span 424242L\n" + includes(["asc/version"])
    actual = matrix.run("host-sentinel", sentinel, standard)
    assert actual["__cpp_lib_span"] == "424242L"
    empty = matrix.run("empty", "", standard)
    actual = matrix.run("reserved-macros", includes(["asc/version"]), standard)
    assert family(actual, "__cpp_lib_") == family(empty, "__cpp_lib_")
    if matrix.args.mode == "host":
        baseline = matrix.run("host-version", includes(["version", "span"]), standard)
        for order, headers in enumerate((("version", "span", "asc/version"),
                                         ("asc/version", "version", "span", "asc/version"))):
            actual = matrix.run(f"host-coexist-{order}", includes(headers), standard)
            assert family(actual, "__cpp_lib_") == family(baseline, "__cpp_lib_")
            assert exports(actual) == expected
            matrix.run(f"host-coexist-compile-{order}", includes(headers) + contract_source(expected),
                       standard, Options(preprocess=False))


def check_one_branch(matrix, standard, expected):
    # A private test fixture exercises #if's true branches without claiming module delivery.
    header = (matrix.root / "include/asc/__version/product.h").read_text(encoding="utf-8")
    fixture = matrix.directory / "product-true.h"
    enabled = dict(expected)
    for name in NAMES[1:]:
        header = header.replace(f"#define {name} {expected[name]}", f"#define {name} 1")
        enabled[name] = "1"
    fixture.write_text(header, encoding="utf-8")
    options = Options(preprocess=False, flags=("-include", str(fixture)))
    matrix.run("true-branches-fixture", contract_source(enabled), standard, options)


def parse_arguments():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler", default="c++")
    parser.add_argument("--mode", choices=("host", "simd", "simt"), default="host")
    parser.add_argument("--npu-arch", default="dav-3510")
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    args.compiler = shutil.which(args.compiler) or args.compiler
    return args


def main():
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    args = parse_arguments()
    with tempfile.TemporaryDirectory(prefix="asc-product-version-") as temporary:
        matrix = Matrix(args, Path(temporary))
        registry = json.loads((matrix.root / "docs/release/extension_features.json").read_text(encoding="utf-8"))
        expected = {"CANN_ASC_STL": str(registry["release_date"])}
        expected.update({name: str(row["value"]) for name, row in registry["features"].items()})
        try:
            for standard in (17, 20):
                check_includes(matrix, standard, expected)
                check_date_and_host(matrix, standard, expected)
                check_one_branch(matrix, standard, expected)
            diagnostic = matrix.run("requires-cxx17", includes(["asc/version"]), 14,
                                    Options(preprocess=False, failure=True))
            assert "ASC-STL requires C++17 or newer" in diagnostic
        finally:
            if args.report:
                args.report.parent.mkdir(parents=True, exist_ok=True)
                args.report.write_text(json.dumps(matrix.records, indent=2) + "\n", encoding="utf-8")
        LOGGER.info("PASS: %d product-version checks in %s", len(matrix.records), args.mode)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
