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

"""Exercise the header guard check through its command-line gate."""

from pathlib import Path
import os
import subprocess
import sys
import tempfile
import unittest


CHECKER = Path(__file__).resolve().parents[2] / "scripts/check_header_layout.py"


class HeaderGuardGateTests(unittest.TestCase):
    def test_non_header_is_not_treated_as_a_header(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get("ASC_STL_TEST_TMPDIR")) as temporary:
            root = Path(temporary)
            (root / "README.md").write_text("documentation\n", encoding="utf-8")
            result = subprocess.run([sys.executable, str(CHECKER), str(root)],
                                    capture_output=True, text=True, check=False)
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_manifest_extensionless_header_is_checked(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get("ASC_STL_TEST_TMPDIR")) as temporary:
            root = Path(temporary)
            (root / "asc").mkdir()
            (root / "asc" / "__config").write_text("int value;\n", encoding="utf-8")
            result = subprocess.run([sys.executable, str(CHECKER), str(root)],
                                    capture_output=True, text=True, check=False)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("missing #ifndef guard", result.stderr)

    def test_missing_guard_fails_gate(self):
        with tempfile.TemporaryDirectory(dir=os.environ.get("ASC_STL_TEST_TMPDIR")) as temporary:
            root = Path(temporary)
            (root / "unguarded.h").write_bytes(b"int value;\n")
            result = subprocess.run(
                [sys.executable, str(CHECKER), str(root)],
                capture_output=True, text=True, check=False,
            )
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("missing #ifndef guard", result.stderr)


if __name__ == "__main__":
    unittest.main()
