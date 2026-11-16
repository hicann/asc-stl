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

"""Ensure invalid or unsupported delivery claims fail the release check."""
import hashlib
import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "scripts"))
import check_product_version as checker


class ProductVersionRecords(unittest.TestCase):
    def setUp(self):
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        self.root = Path(self.directory.name)
        product = Path(__file__).resolve().parents[2]
        self.header = product.joinpath("include/asc/__version/product.h").read_text(encoding="utf-8")
        self.registry = json.loads(product.joinpath("docs/release/extension_features.json").read_text(encoding="utf-8"))
        self.name = "CANN_ASC_STL_HAS_PIPELINE"
        self.row = self.registry["features"][self.name]
        self.write()

    def write(self):
        for relative, text in (("include/asc/__version/product.h", self.header),
                               ("docs/release/extension_features.json", json.dumps(self.registry))):
            path = self.root / relative
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(text, encoding="utf-8")

    def evidence_file(self, name, content):
        path = self.root / "docs/release" / name
        path.write_text(content, encoding="utf-8")
        return {"path": name, "sha256": hashlib.sha256(content.encode()).hexdigest()}

    def enable(self):
        self.header = self.header.replace(f"#define {self.name} 0", f"#define {self.name} 1")
        self.row["value"] = 1
        self.write()
        self.root.joinpath("include/asc/pipeline").write_text("// Fixture module header\n", encoding="utf-8")

    def complete(self):
        self.enable()
        self.row["baseline"] = self.evidence_file("baseline.md", "Fixed API signatures, behavior and acceptance scope")
        self.row["implementation_commit"] = "ab" * 20
        self.row["first_release_date"] = 20261023
        self.acceptance({"name": "applicable-contract", "status": "PASS", "returncode": 0})

    def acceptance(self, case):
        record = {"implementation_commit": self.row["implementation_commit"], "cases": [case]}
        self.row["acceptance"] = self.evidence_file("acceptance.json", json.dumps(record))
        self.write()

    def test_current_package(self):
        self.assertEqual(checker.check(self.root)["CANN_ASC_STL"], 20261023)

    def test_invalid_registry_schema(self):
        self.registry["schema_version"] = True
        self.write()
        with self.assertRaisesRegex(ValueError, "registry schema"):
            checker.check(self.root)

    def test_calendar_boundaries(self):
        for value in (10000101, 20000229, 20261231, 20270101, 99991231):
            self.assertEqual(checker.release_date(value), value)
        for value in (0, True, "20261023", 9991231, 20260001, 20261301, 20260431, 19000229, 20260229):
            with self.subTest(value=value), self.assertRaises(ValueError):
                checker.release_date(value)

    def test_release_date_mismatch(self):
        self.registry["release_date"] = 20261024
        self.write()
        with self.assertRaisesRegex(ValueError, "Release date disagrees"):
            checker.check(self.root)

    def test_flag_mismatch_and_invalid_values(self):
        for value in (1, 2, True, "0"):
            self.row["value"] = value
            self.write()
            with self.subTest(value=value), self.assertRaises(ValueError):
                checker.check(self.root)

    def test_missing_or_extra_header_macro(self):
        original = self.header
        for header in (original.replace("#define CANN_ASC_STL_HAS_CACHE 0", ""),
                       original + "#define CANN_ASC_STL_VERSION 10000\n"):
            self.header = header
            self.write()
            with self.assertRaises(ValueError):
                checker.check(self.root)

    def test_bad_header_value(self):
        self.header = self.header.replace(f"#define {self.name} 0", f"#define {self.name} 2")
        self.write()
        with self.assertRaisesRegex(ValueError, "0 or 1"):
            checker.check(self.root)

    def test_missing_registry_row_and_wrong_issue(self):
        self.row["issue"] = "https://gitcode.com/cann/asc-stl/issues/84"
        self.write()
        with self.assertRaisesRegex(ValueError, "incorrect module Issue"):
            checker.check(self.root)
        del self.registry["features"][self.name]
        self.write()
        with self.assertRaisesRegex(ValueError, "exactly the three"):
            checker.check(self.root)

    def test_no_evidence_cannot_establish_delivery(self):
        self.enable()
        with self.assertRaisesRegex(ValueError, "Delivery evidence requires"):
            checker.check(self.root)

    def test_complete_delivery_and_tampering(self):
        self.complete()
        self.assertEqual(checker.check(self.root)[self.name], 1)
        self.root.joinpath("docs/release/baseline.md").write_text("Changed baseline", encoding="utf-8")
        with self.assertRaisesRegex(ValueError, "SHA256 mismatch"):
            checker.check(self.root)

    def test_records_cannot_cover_a_missing_public_header(self):
        self.complete()
        self.root.joinpath("include/asc/pipeline").unlink()
        with self.assertRaisesRegex(ValueError, "public module header"):
            checker.check(self.root)

    def test_failed_or_skipped_acceptance(self):
        self.complete()
        for status, code in (("FAIL", 1), ("SKIP", 0), ("NOT_APPLICABLE", 77), ("PASS", 1)):
            self.acceptance({"name": "case", "status": status, "returncode": code})
            with self.subTest(status=status, code=code), self.assertRaises(ValueError):
                checker.check(self.root)

    def test_empty_or_unrelated_acceptance(self):
        self.complete()
        for record in ({"implementation_commit": "cd" * 20, "cases": []},
                       {"implementation_commit": "ab" * 20, "cases": []}):
            self.row["acceptance"] = self.evidence_file("acceptance.json", json.dumps(record))
            self.write()
            with self.assertRaises(ValueError):
                checker.check(self.root)

    def test_invalid_first_release_date(self):
        self.complete()
        for value in (None, 20260230, 20261024):
            self.row["first_release_date"] = value
            self.write()
            with self.subTest(value=value), self.assertRaises(ValueError):
                checker.check(self.root)

    def test_evidence_must_ship_inside_package(self):
        self.complete()
        for value in ("../outside.md", "/absolute/baseline.md"):
            self.row["baseline"]["path"] = value
            self.write()
            with self.subTest(value=value), self.assertRaises(ValueError):
                checker.check(self.root)


if __name__ == "__main__":
    unittest.main()
