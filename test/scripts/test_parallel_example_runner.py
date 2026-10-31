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

"""Exercise example-runner deadlines without product or device execution."""

import importlib.util
import json
from pathlib import Path
import subprocess
import sys
import tempfile
import unittest
from unittest import mock

ROOT = Path(__file__).resolve().parents[2]
RUNNER = ROOT / "examples/extension/parallel_algorithms/run.py"


class ParallelExampleRunnerTests(unittest.TestCase):
    def test_nonfinite_deadlines_are_rejected(self):
        for option, value in (("--process-timeout", "nan"), ("--process-timeout", "inf"),
                              ("--cleanup-grace", "nan"), ("--cleanup-grace", "inf")):
            arguments = [sys.executable, str(RUNNER), "--binary", "unused", "--report-dir", "unused",
                         "--standard", "17",
                         option, value]
            with self.subTest(option=option, value=value):
                result = subprocess.run(arguments, capture_output=True, text=True, timeout=10, check=False)
                self.assertEqual(result.returncode, 2)
                self.assertIn("Deadlines must be finite positive numbers", result.stderr)

    def invoke(self, mode, only_one=False):
        with tempfile.TemporaryDirectory() as temporary:
            directory = Path(temporary)
            binary = directory / "explicit_offline_fixture.py"
            source = "#!/usr/bin/env python3\nimport json,signal,sys,time\n"
            source += "if sys.argv[1] == '--describe':\n"
            language = 202002 if mode == "wrong_language" else 201703
            source += f" print(json.dumps(dict(case_count=57,cplusplus={language})));sys.exit(0)\n"
            if mode == "timeout":
                source += "signal.signal(signal.SIGTERM,signal.SIG_IGN)\ntime.sleep(10)\n"
            source += "sys.exit(7)\n" if mode == "failure" else "sys.exit(0)\n"
            binary.write_text(source)
            binary.chmod(0o755)
            report = directory / "report"
            command = [sys.executable, str(RUNNER), "--binary", str(binary), "--standard", "17",
                       "--report-dir", str(report), "--process-timeout", "0.1", "--cleanup-grace", "0.1"]
            if only_one:
                command += ["--case", "adjacent_difference"]
            result = subprocess.run(command, capture_output=True, text=True, timeout=15, check=False)
            return result, json.loads((report / "results.json").read_text())

    def test_single_case_success_is_scoped(self):
        result, report = self.invoke("success", only_one=True)
        self.assertEqual(result.returncode, 0)
        self.assertEqual(report["scope"], "single_case")
        self.assertTrue(report["passed"])
        self.assertEqual(len(report["cases"]), 1)

    def test_first_error_stops_full_plan(self):
        result, report = self.invoke("failure")
        self.assertEqual(result.returncode, 1)
        self.assertFalse(report["passed"])
        self.assertEqual(len(report["cases"]), 1)
        self.assertEqual(report["cases"][0]["returncode"], 7)

    def test_ignored_term_is_killed_and_recorded(self):
        result, report = self.invoke("timeout")
        self.assertEqual(result.returncode, 1)
        self.assertFalse(report["cases"][0]["passed"])
        self.assertEqual(report["cases"][0]["termination"], "deadline:SIGKILL")

    def test_wrong_language_prevents_cases(self):
        result, report = self.invoke("wrong_language")
        self.assertEqual(result.returncode, 1)
        self.assertFalse(report["preflight"]["passed"])
        self.assertEqual(report["cases"], [])

    def test_unreapable_killed_process_keeps_a_bounded_control_path(self):
        specification = importlib.util.spec_from_file_location("parallel_example_control_fixture", RUNNER)
        runner = importlib.util.module_from_spec(specification)
        with mock.patch.dict(sys.modules, {specification.name: runner}):
            specification.loader.exec_module(runner)
        process = mock.Mock()
        process.communicate.side_effect = [
            subprocess.TimeoutExpired("offline fixture", 0.1),
            subprocess.TimeoutExpired("offline fixture", 0.1),
            subprocess.TimeoutExpired("offline fixture", 5, output=b"retained log\n"),
        ]
        settings = runner.Settings(Path("offline fixture"), Path("unused"), 0.1, 0.1, 17)
        with mock.patch.object(runner, "stop_group") as stop:
            output, termination = runner.collect(process, settings)
        self.assertEqual(output, "retained log\n")
        self.assertEqual(termination, "deadline:SIGKILL_UNREAPED")
        self.assertEqual(stop.call_count, 2)
        self.assertEqual(process.communicate.call_args.kwargs["timeout"], 5)
        process.stdout.close.assert_called_once()


if __name__ == "__main__":
    unittest.main()
