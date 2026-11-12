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

"""Check feature values, absent revisions, include order and Host isolation."""
import argparse
import json
import logging
import re
import shutil
import subprocess
import tempfile
from pathlib import Path
from dataclasses import dataclass


# Independent expectations from N4861/N4950 [version.syn], not parsed from ASC.
VALUES = {
    "constexpr_numeric": 201911, "raw_memory_algorithms": 201606,
    "robust_nonmodifying_seq_ops": 201304, "sample": 201603, "launder": 201606,
    "apply": 201603, "as_const": 201510, "bitops": 201907, "bool_constant": 201505,
    "bounded_array_traits": 201902, "byte": 201603, "clamp": 201603, "endian": 201907,
    "exchange_function": 201304, "gcd_lcm": 201606, "int_pow2": 202002,
    "integer_comparison_functions": 202002, "integer_sequence": 201304,
    "integral_constant_callable": 201304, "invoke": 201411, "invoke_r": 202106,
    "is_invocable": 201703, "is_nothrow_convertible": 201806, "is_null_pointer": 201309,
    "is_scoped_enum": 202011, "is_swappable": 201603, "logical_traits": 201510,
    "make_from_tuple": 201606, "make_reverse_iterator": 201402, "not_fn": 201603,
    "remove_cvref": 201711, "shift": 201806, "ssize": 201902, "to_address": 201711,
    "to_array": 201907, "to_underlying": 202102, "tuple_element_t": 201402,
    "tuples_by_type": 201304, "type_identity": 201806, "unreachable": 202202,
    "unwrap_ref": 201811, "void_t": 201411,
}
HEADERS = (
    "type_traits", "utility", "tuple", "functional", "bit", "array", "iterator",
    "memory", "cstddef", "numeric", "algorithm", "source_location", "new",
)
WITHHELD = (
    "span", "mdspan", "submdspan", "expected", "optional", "variant", "inplace_vector",
    "allocate_at_least", "format", "ranges", "philox_engine", "math_constants",
    "concepts", "forward_like", "byteswap", "array_constexpr", "to_chars",
    "nonmember_container_access", "transformation_trait_aliases", "type_trait_variable_templates",
)
PREFIX = "CANN_ASC_STL_LIB_"


def includes(headers):
    return "".join(f"#include <{header}>\n" for header in headers)


def family(macros, prefix):
    return {key: value for key, value in macros.items() if key.startswith(prefix)}


LOGGER = logging.getLogger(__name__)


@dataclass(frozen=True)
class Options:
    preprocess: bool = True
    flags: tuple[str, ...] = ()
    failure: bool = False


class Matrix:
    def __init__(self, args, directory):
        self.args = args
        self.directory = directory
        self.records = []
        self.root = Path(__file__).resolve().parents[2]

    @staticmethod
    def interleaved_headers(host_headers):
        result = includes(["version"]) if "version" in host_headers else ""
        for header in HEADERS:
            if header in host_headers:
                result += includes([header])
            result += includes(["asc/std/" + header])
        return result

    def run(self, name, source, standard, options=Options()):
        path = self.directory / (name + (".cpp" if self.args.mode == "host" else ".asc"))
        path.write_text(source, encoding="utf-8")
        command = [self.args.compiler, f"-std=c++{standard}", "-I" + str(self.root / "include"),
                   "-I" + str(self.root / "test")]
        if self.args.mode != "host":
            command += ["--asc-aicore-lang", f"--npu-arch={self.args.npu_arch}"]
        if self.args.mode == "simt":
            command += ["--enable-simt", "-Wno-error=ignored-attributes"]
        command += list(options.flags)
        if options.preprocess:
            command += ["-E", "-dM", str(path)]
        else:
            command += ["-Werror", "-c", str(path), "-o", str(path.with_suffix(".o"))]
        result = subprocess.run(command, capture_output=True, text=True, check=False, timeout=90)
        self.records.append({"case": name, "standard": standard, "mode": self.args.mode,
                             "command": command, "returncode": result.returncode,
                             "expected_failure": options.failure, "stderr": result.stderr})
        if (result.returncode != 0) != options.failure:
            raise AssertionError(f"{name}: exit {result.returncode}\n{result.stderr}")
        if options.failure:
            return result.stderr
        return dict(re.findall(r"^#define (\w+) (.*)$", result.stdout, re.MULTILINE))

    def check_values(self, standard):
        macros = self.run("version", includes(["asc/std/version"]), standard)
        for name, value in VALUES.items():
            assert macros.get(PREFIX + name) == f"{value}L", name
        conditional = {"addressof_constexpr": 201603, "bit_cast": 201806,
                       "has_unique_object_representations": 201606, "is_aggregate": 201703,
                       "is_final": 201402, "is_constant_evaluated": 201811, "source_location": 201907}
        for name, value in conditional.items():
            if PREFIX + name in macros:
                assert macros[PREFIX + name] == f"{value}L", name
        for name in WITHHELD:
            assert PREFIX + name not in macros, name
        baseline = self.run("compiler-empty", "", standard)
        assert family(macros, "__cpp_lib_") == family(baseline, "__cpp_lib_")
        # These older revisions are supported; their newer additions are absent.
        self.run("thresholds", includes(["asc/std/version"]) + """
#if CANN_ASC_STL_LIB_not_fn < 201603L || CANN_ASC_STL_LIB_not_fn >= 202306L
#error "stateless not_fn must not be reported"
#endif
#if CANN_ASC_STL_LIB_raw_memory_algorithms >= 202411L
#error "constexpr raw memory algorithms must not be reported"
#endif
#if CANN_ASC_STL_LIB_shift < 201806L || CANN_ASC_STL_LIB_shift >= 202202L
#error "ranges shift overloads must not be reported"
#endif
static_assert(CANN_ASC_STL_LIB_type_identity >= 201806L);
""", standard, Options(preprocess=False))
        self.run("no-stateless-not-fn", includes(["asc/std/functional"]) + """
bool predicate(int value) { return value != 0; }
auto newer = asc::std::not_fn<predicate>();
""", standard, Options(preprocess=False, failure=True))
        self.run("no-ranges-shift", includes(["asc/std/algorithm"]) + """
void newer(int* begin, int* end) { asc::std::ranges::shift_left(begin, end, 1); }
""", standard, Options(preprocess=False, failure=True))
        return family(macros, PREFIX)

    def check_order(self, standard, expected):
        for header in HEADERS:
            product = "asc/std/" + header
            for index, headers in enumerate(((product,), ("asc/std/version", product),
                                              (product, "asc/std/version", product, "asc/std/version"))):
                actual = self.run(f"{header}-{index}", includes(headers), standard)
                assert family(actual, PREFIX) == expected, (header, index)
        repeated = self.run("repeated", includes(["asc/std/version"] * 2), standard)
        assert family(repeated, PREFIX) == expected

    def check_host_isolation(self, standard, expected):
        self.check_reserved_macros(standard)
        host_headers = self.available_host_headers(standard)
        if not host_headers:
            self.not_applicable("host-coexistence", standard, "No Host feature headers are available")
            return
        product_headers = ["asc/std/" + name for name in HEADERS]
        host = includes(host_headers)
        product = includes(product_headers)
        baseline = self.run("host-baseline", host, standard)
        for name, source in (("host-first", host + product), ("asc-first", product + host),
                             ("interleaved", self.interleaved_headers(host_headers) + host)):
            actual = self.run(name, source, standard)
            assert family(actual, "__cpp_lib_") == family(baseline, "__cpp_lib_"), name
            assert family(actual, PREFIX) == expected, name

    def not_applicable(self, name, standard, reason):
        self.records.append({"case": name, "standard": standard, "mode": self.args.mode,
                             "status": "NOT_APPLICABLE", "reason": reason})
        LOGGER.info("NOT_APPLICABLE: %s C++%d: %s", self.args.mode, standard, reason)

    def available_host_headers(self, standard):
        headers = ["version", *HEADERS]
        source = "".join(f"#if !__has_include(<{header}>)\n"
                         f"#define ASC_STL_TEST_MISSING_HOST_HEADER_{index} 1\n#endif\n"
                         for index, header in enumerate(headers))
        missing = self.run("host-header-availability", source, standard)
        available = []
        for index, header in enumerate(headers):
            # A marker from any CCE compilation pass makes this header inapplicable.
            if f"ASC_STL_TEST_MISSING_HOST_HEADER_{index}" in missing:
                self.not_applicable("host-header." + header, standard,
                                    f"Host <{header}> is unavailable to the selected compiler")
            else:
                available.append(header)
        return available

    def check_reserved_macros(self, standard):
        legacy = self.run("retired-switch", "#define CANN_ASC_STL_ENABLE_LEGACY_STD_FEATURE_MACROS 1\n"
                          + includes(["asc/std/version"]), standard)
        empty = self.run("legacy-empty", "", standard)
        assert family(legacy, "__cpp_lib_") == family(empty, "__cpp_lib_")
        sentinel = self.run("host-sentinel", "#define __cpp_lib_source_location 424242L\n"
                            "#define __cpp_lib_unreachable 434343L\n" + includes(["asc/std/version"]), standard)
        assert sentinel["__cpp_lib_source_location"] == "424242L"
        assert sentinel["__cpp_lib_unreachable"] == "434343L"

    def check_gates(self, standard, expected):
        # A real compiler-capability probe, before including ASC configuration.
        probes = self.run("compiler-probes", """
#if __has_builtin(__builtin_bit_cast)
#define TEST_BIT_CAST 1
#endif
#if __has_builtin(__is_aggregate)
#define TEST_AGGREGATE 1
#endif
#if __has_builtin(__is_final)
#define TEST_FINAL 1
#endif
#if __has_builtin(__has_unique_object_representations)
#define TEST_UNIQUE 1
#endif
""", standard)
        for feature, probe in (("bit_cast", "TEST_BIT_CAST"), ("is_aggregate", "TEST_AGGREGATE"),
                               ("is_final", "TEST_FINAL"), ("has_unique_object_representations", "TEST_UNIQUE")):
            assert (PREFIX + feature in expected) == (probe in probes), feature
        disabled = self.run("no-bit-cast", """
#include <asc/__config>
#undef CANN_ASC_STL_DETAIL_HAS_BUILTIN
#define CANN_ASC_STL_DETAIL_HAS_BUILTIN(x) 0
#include <asc/std/bit>
#include <asc/std/version>
#ifdef CANN_ASC_STL_LIB_bit_cast
#error "memcpy fallback is not constexpr bit_cast"
#endif
static_assert(!CANN_ASC_STL_DETAIL_HAS_CONSTEXPR_BIT_CAST());
""", standard, Options(preprocess=False))
        assert disabled == {}
        self.run("no-constant-evaluation-builtin", """
#include <asc/__config>
#undef CANN_ASC_STL_DETAIL_HAS_BUILTIN
#define CANN_ASC_STL_DETAIL_HAS_BUILTIN(x) 0
#undef __GNUC__
#define __GNUC__ 8
#include <asc/std/__type_traits/is_constant_evaluated.h>
#include <asc/std/version>
#ifdef CANN_ASC_STL_LIB_is_constant_evaluated
#error "constant false fallback must not be reported as standard support"
#endif
static_assert(CANN_ASC_STL_HAS_IS_CONSTANT_EVALUATED == 0);
static_assert(!asc::std::is_constant_evaluated());
""", standard, Options(preprocess=False))
        if self.args.mode == "host":
            self.check_source_location(standard, expected)
        else:
            assert PREFIX + "source_location" not in expected

    def check_source_location(self, standard, expected):
        source = includes(["asc/std/source_location"]) + """
asc::std::source_location capture(unsigned line) {
    return asc::std::source_location::current("file", "function", line, 0);
}
"""
        immediate = PREFIX + "source_location" in expected
        assert immediate == (standard == 20)
        options = Options(preprocess=False, failure=immediate)
        diagnostic = self.run("source-location-immediate", source, standard, options)
        if immediate:
            assert "constant expression" in diagnostic
        disabled = self.run("no-consteval", includes(["asc/std/source_location"]), standard,
                            Options(flags=("-U__cpp_consteval",)))
        assert PREFIX + "source_location" not in disabled
        self.run("no-consteval-interface", source, standard, Options(preprocess=False, flags=("-U__cpp_consteval",)))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler", required=True)
    parser.add_argument("--mode", choices=("host", "simd", "simt"), default="host")
    parser.add_argument("--npu-arch", default="dav-3510")
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    compiler = shutil.which(args.compiler)
    if compiler is None:
        parser.error(f"Compiler is unavailable in the loaded environment: {args.compiler}")
    args.compiler = compiler
    with tempfile.TemporaryDirectory(prefix="asc-stl-version-") as directory:
        matrix = Matrix(args, Path(directory))
        try:
            for standard in (17, 20):
                expected = matrix.check_values(standard)
                matrix.check_order(standard, expected)
                matrix.check_host_isolation(standard, expected)
                matrix.check_gates(standard, expected)
                matrix.run("feature-interfaces", '''
#include "support/std_feature_semantics.h"
CANN_ASC_STL_API bool check_feature_interfaces() {
    return std_feature_tests::semantics() && std_feature_tests::numeric_semantics() &&
        std_feature_tests::storage_semantics();
}
''', standard, Options(preprocess=False))
            diagnostic = matrix.run("cxx14-rejected", includes(["asc/std/version"]), 14,
                                    Options(preprocess=False, failure=True))
            assert "ASC-STL requires C++17 or newer" in diagnostic
        finally:
            if args.report:
                args.report.parent.mkdir(parents=True, exist_ok=True)
                args.report.write_text(json.dumps(matrix.records, indent=2) + "\n", encoding="utf-8")
        compiled = sum("command" in row for row in matrix.records)
        inapplicable = len(matrix.records) - compiled
        LOGGER.info("PASS: %s: %d compiler checks; %d Host scenarios NOT_APPLICABLE",
                    args.mode, compiled, inapplicable)
    return 0


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    raise SystemExit(main())
