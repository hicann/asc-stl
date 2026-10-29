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

"""Failure-path regressions for the executable user acceptance reporter."""
from __future__ import annotations

import json
from pathlib import Path
import sys
import tempfile
import unittest

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "scripts"))
import run_user_acceptance as acceptance


class AcceptanceFailures(unittest.TestCase):
    def test_incomplete_or_corrupt_records_are_rejected(self):
        for text in ("{}\n", "[]\n", "null\n", "invalid\n", ""):
            with self.subTest(text=text), self.assertRaises(ValueError):
                acceptance.validate_samples(text, 3, "asc_stl")

    def test_duplicate_records_cannot_replace_missing_samples(self):
        rows = [{"scenario": scenario, "sample": sample, "implementation": "asc_stl",
                 "elapsed_ns": 10, "checksum": 20}
                for scenario in sorted(acceptance.SCENARIOS) for sample in range(3)]
        rows[-1] = rows[0]
        with self.assertRaisesRegex(ValueError, "duplicate"):
            acceptance.validate_samples("\n".join(json.dumps(row) for row in rows), 3, "asc_stl")

    def test_timeout_preserves_partial_diagnostics(self):
        with tempfile.TemporaryDirectory() as directory:
            log = Path(directory) / "timeout.log"
            command = [sys.executable, "-u", "-c",
                       "import sys,time; sys.stdout.write('partial output\\n'); "
                       "sys.stderr.write('partial error\\n'); time.sleep(10)"]
            with self.assertRaisesRegex(RuntimeError, "timed out"):
                acceptance.execute(command, log, 1)
            self.assertIn("partial output", log.read_text())
            self.assertIn("partial error", log.read_text())

    def test_nonzero_exit_retains_diagnostics(self):
        with tempfile.TemporaryDirectory() as directory:
            log = Path(directory) / "failure.log"
            command = [sys.executable, "-c", "import sys; sys.stderr.write('golden mismatch'); sys.exit(42)"]
            with self.assertRaisesRegex(RuntimeError, "42"):
                acceptance.execute(command, log, 5)
            self.assertEqual(log.read_text(), "golden mismatch")


if __name__ == "__main__":
    unittest.main()
