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


"""Regressions for supplemental release-stage reporting and source identity."""
import argparse
from pathlib import Path
import sys
import tempfile
import unittest
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / "scripts"))


class SupplementalReleaseChecks(unittest.TestCase):
    def setUp(self):
        import run_release_checks
        self.runner = run_release_checks
        self.directory = tempfile.TemporaryDirectory()
        self.addCleanup(self.directory.cleanup)
        root = Path(self.directory.name)
        self.args = argparse.Namespace(root=root, report_dir=root, compiler="c++", scope="software", stage=["memory"])

    def test_exit_two_needs_explicit_environment_diagnostic(self):
        command = [sys.executable, "-c", "raise SystemExit(2)"]
        failed = self.runner.execute_stage(self.args, "compile-failure", command)
        self.assertEqual((failed["status"], failed["returncode"]), ("FAIL", 2))
        body = "import sys; sys.stderr.write('BLOCKED_ENVIRONMENT: missing SDK'); sys.exit(2)"
        command = [sys.executable, "-c", body]
        blocked = self.runner.execute_stage(self.args, "missing-sdk", command)
        self.assertEqual((blocked["status"], blocked["returncode"]), ("BLOCKED_ENVIRONMENT", 2))

    def test_failed_stage_prevents_later_execution(self):
        commands = [(name, [sys.executable, "-c", "raise SystemExit(1)"]) for name in ("first", "second")]
        identity = {"commit": "selected", "tree": "tree", "git_status": ""}
        with patch.object(self.runner, "stage_commands", return_value=commands):
            with patch.object(self.runner, "source_identity", return_value=identity):
                report = self.runner.run_stages(self.args, identity)
        self.assertFalse(report["passed"])
        self.assertEqual([item["status"] for item in report["results"]], ["FAIL", "NOT_RUN"])
        self.assertFalse((self.args.report_dir / "second.log").exists())

    def test_source_mutation_invalidates_successful_commands(self):
        commands = [("success", [sys.executable, "-c", "raise SystemExit(0)"])]
        before = {"commit": "selected", "tree": "tree", "git_status": ""}
        after = dict(before, git_status=" M include/asc/example")
        with patch.object(self.runner, "stage_commands", return_value=commands):
            with patch.object(self.runner, "source_identity", return_value=after):
                report = self.runner.run_stages(self.args, before)
        self.assertEqual(report["results"][0]["status"], "PASS")
        self.assertFalse(report["source_unchanged"])
        self.assertFalse(report["passed"])

    def test_unavailable_stages_preserve_status_and_stop_strict_release(self):
        cases = [("raise SystemExit(77)", "NOT_APPLICABLE"),
                 ("print('BLOCKED_ENVIRONMENT: missing SDK'); raise SystemExit(2)", "BLOCKED_ENVIRONMENT")]
        identity = {"commit": "selected", "tree": "tree", "git_status": ""}
        for body, expected in cases:
            commands = [("unavailable", [sys.executable, "-c", body]),
                        ("later", [sys.executable, "-c", "print('must not run')"])]
            with self.subTest(status=expected):
                with patch.object(self.runner, "stage_commands", return_value=commands), \
                        patch.object(self.runner, "source_identity", return_value=identity):
                    report = self.runner.run_stages(self.args, identity)
                self.assertEqual([row["status"] for row in report["results"]], [expected, "NOT_RUN"])
                self.assertFalse(report["passed"])
                self.assertTrue(report["source_unchanged"])
                self.assertFalse((self.args.report_dir / "later.log").exists())

    def test_missing_git_has_an_explicit_diagnostic(self):
        import run_user_acceptance
        for runner in (self.runner, run_user_acceptance):
            with self.subTest(runner=runner.__name__):
                with patch.object(runner.shutil, "which", return_value=None), \
                        self.assertRaisesRegex(FileNotFoundError, "Git executable is unavailable"):
                    runner.source_identity(self.args.root)



if __name__ == "__main__":
    unittest.main()
