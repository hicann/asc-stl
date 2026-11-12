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

"""Regress missing Host headers without suppressing ASC or compiler failures."""
import re
import subprocess
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace

from test_std_version import HEADERS, PREFIX, Matrix, Options


EXPECTED = {PREFIX + "fixture": "201907L"}


class HeaderFixture(Matrix):
    def __init__(self, directory, missing=()):
        super().__init__(SimpleNamespace(mode="simd"), directory)
        self.missing = set(missing)
        self.calls = {}
        self.broken = ""
        self.pollution = False
        self.asc_changed = False

    def run(self, name, source, standard, options=Options()):
        self.calls[name] = source
        if name == "host-header-availability":
            return {f"ASC_STL_TEST_MISSING_HOST_HEADER_{index}": "1"
                    for index, header in enumerate(["version", *HEADERS]) if header in self.missing}
        host_headers = re.findall(r"^#include <([^>]+)>$", source, re.MULTILINE)
        unavailable = self.missing.intersection(host_headers)
        if unavailable:
            raise AssertionError(f"Host header unavailable: {sorted(unavailable)}")
        if self.broken and self.broken in host_headers:
            raise AssertionError("Present Host header failed to preprocess")
        if name in ("retired-switch", "legacy-empty"):
            return {}
        if name == "host-sentinel":
            return {"__cpp_lib_source_location": "424242L", "__cpp_lib_unreachable": "434343L"}
        result = {**EXPECTED, "__cpp_lib_fixture": "202002L"}
        if name == "asc-first" and self.pollution:
            result["__cpp_lib_fixture"] = "1L"
        if name == "asc-first" and self.asc_changed:
            result[PREFIX + "fixture"] = "1L"
        return result


class HostAvailabilityTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory(prefix="asc-std-version-regressions-")
        self.addCleanup(self.temporary.cleanup)
        self.directory = Path(self.temporary.name)

    def test_ci_missing_modern_headers_retains_legacy_coexistence(self):
        missing = ("version", "bit", "source_location")
        for standard in (17, 20):
            with self.subTest(standard=standard):
                matrix = HeaderFixture(self.directory, missing)
                matrix.check_host_isolation(standard, EXPECTED)
                self.assertIn("#include <utility>", matrix.calls["host-baseline"])
                for header in missing:
                    self.assertNotIn(f"#include <{header}>", "\n".join(matrix.calls.values()))
                self.assertEqual(len(matrix.records), len(missing))
                self.assertTrue(all(row["status"] == "NOT_APPLICABLE" for row in matrix.records))
                self.assertEqual(set(matrix.calls).intersection(("host-first", "asc-first", "interleaved")),
                                 {"host-first", "asc-first", "interleaved"})

    def test_no_host_headers_preserves_reserved_macro_checks(self):
        matrix = HeaderFixture(self.directory, ("version", *HEADERS))
        matrix.check_host_isolation(17, EXPECTED)
        for name in ("retired-switch", "legacy-empty", "host-sentinel"):
            self.assertIn(name, matrix.calls)
        self.assertNotIn("host-baseline", matrix.calls)
        scenarios = [row for row in matrix.records if row["case"] == "host-coexistence"]
        self.assertEqual(len(scenarios), 1)
        self.assertEqual(scenarios[0]["status"], "NOT_APPLICABLE")

    def test_present_but_broken_header_is_a_failure(self):
        matrix = HeaderFixture(self.directory)
        matrix.broken = "memory"
        with self.assertRaisesRegex(AssertionError, "failed to preprocess"):
            matrix.check_host_isolation(20, EXPECTED)
        self.assertFalse(matrix.records)

    def test_host_macro_pollution_remains_a_failure_with_missing_headers(self):
        matrix = HeaderFixture(self.directory, ("version", "bit"))
        matrix.pollution = True
        with self.assertRaises(AssertionError):
            matrix.check_host_isolation(20, EXPECTED)

    def test_asc_macro_changes_remain_a_failure_with_missing_headers(self):
        matrix = HeaderFixture(self.directory, ("version", "source_location"))
        matrix.asc_changed = True
        with self.assertRaises(AssertionError):
            matrix.check_host_isolation(20, EXPECTED)

    def test_complete_host_headers_keep_all_coexistence_checks(self):
        matrix = HeaderFixture(self.directory)
        matrix.check_host_isolation(20, EXPECTED)
        self.assertIn("#include <version>", matrix.calls["host-baseline"])
        self.assertIn("#include <source_location>", matrix.calls["interleaved"])
        self.assertFalse(matrix.records)

    def test_missing_compiler_fails_at_runtime(self):
        checker = Path(__file__).with_name("test_std_version.py")
        result = subprocess.run([sys.executable, str(checker), "--mode", "simd", "--compiler",
                                 "asc-stl-nonexistent-fixture-compiler"],
                                text=True, capture_output=True, check=False)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("Compiler is unavailable", result.stderr)


if __name__ == "__main__":
    unittest.main()
