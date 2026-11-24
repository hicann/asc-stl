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

"""Check Python source input handling for both local style mirrors."""

from pathlib import Path
import subprocess
import sys
import tempfile
import unittest


SCRIPTS = Path(__file__).resolve().parents[2] / "scripts"


class PythonCheckerInputTests(unittest.TestCase):
    def test_missing_source_fails_both_checkers(self):
        missing = Path(__file__).with_name("missing_checker_input_20261027.py")
        self.assertFalse(missing.exists())
        for name in ("check_python_codecheck.py", "check_python_logging.py"):
            with self.subTest(name=name):
                result = subprocess.run(
                    [sys.executable, str(SCRIPTS / name), str(missing)],
                    capture_output=True, text=True, check=False,
                )
                self.assertEqual(result.returncode, 2)
                self.assertIn("missing or not a file", result.stderr)

    def test_python_source_encoding_is_honored(self):
        fixtures = {
            "bom.py": "label = 'café'\n".encode("utf-8-sig"),
            "latin1.py": "# coding: latin-1\nlabel = 'café'\n".encode("latin-1"),
            "utf8.py": "label = 'café'\n".encode("utf-8"),
        }
        directory = tempfile.TemporaryDirectory()
        self.addCleanup(directory.cleanup)
        for filename, content in fixtures.items():
            path = Path(directory.name) / filename
            path.write_bytes(content)
            for name in ("check_python_codecheck.py", "check_python_logging.py"):
                with self.subTest(source=filename, name=name):
                    result = subprocess.run(
                        [sys.executable, str(SCRIPTS / name), str(path)],
                        capture_output=True, text=True, check=False,
                    )
                    self.assertEqual(result.returncode, 0, result.stderr)


if __name__ == "__main__":
    unittest.main()
