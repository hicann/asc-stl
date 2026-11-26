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

"""CPU-only fault regressions for hardware process and ACL lifecycle boundaries."""

import argparse
import importlib.util
import os
from pathlib import Path
import shutil
import signal
import re
import subprocess
import sys
import tempfile
import time
import unittest
from unittest import mock


ROOT = Path(__file__).resolve().parents[2]
RUNNER = ROOT / "scripts/run_hardware_case.py"
FIXTURE = ROOT / "test/fixtures/hardware_runtime"
COMPILER = "c++"


class HardwareSafetyTests(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.directory = Path(self.temporary.name)

    def runner_command(self, program, expected=0):
        command = [sys.executable, str(RUNNER), "--timeout", "0.5", "--grace", "0.5",
                   "--log", str(self.directory / "case.log"), "--expected-exit", str(expected)]
        if expected:
            command.extend(["--expected-marker", "ASC_STL_EXPECTED_WARP_FAILURE_VERIFIED"])
        return command + ["--", sys.executable, "-c", program]

    def run_program(self, program, expected=0):
        return subprocess.run(self.runner_command(program, expected), capture_output=True, text=True, timeout=5)

    def test_expected_failure_requires_exact_code_and_marker(self):
        marker = "print('ASC_STL_EXPECTED_WARP_FAILURE_VERIFIED'); "
        cases = [(marker + "exit(42)", 0), ("exit(42)", 1), (marker + "exit(1)", 1), (marker + "exit(0)", 1)]
        for program, expected in cases:
            with self.subTest(program=program):
                self.assertEqual(self.run_program(program, 42).returncode, expected)

    def test_normal_success_and_failure(self):
        self.assertEqual(self.run_program("print('normal')").returncode, 0)
        self.assertEqual(self.run_program("exit(7)").returncode, 7)

    def test_timeout_remains_failure_after_cooperative_cleanup(self):
        program = ("import signal,time,sys; "
                   "signal.signal(signal.SIGTERM,lambda *_:sys.exit(0)); time.sleep(10)")
        result = self.run_program(program)
        self.assertEqual(result.returncode, 124)
        self.assertIn("case timeout", result.stdout)
        self.assertNotIn("grace expired", result.stdout)

    def test_unresponsive_cleanup_is_killed_after_grace(self):
        program = "import signal,time; signal.signal(signal.SIGTERM,signal.SIG_IGN); time.sleep(10)"
        result = self.run_program(program)
        self.assertEqual(result.returncode, 124)
        self.assertIn("grace expired", result.stdout)

    def test_external_term_reaches_detached_child(self):
        ready = self.directory / "ready"
        cleaned = self.directory / "cleaned"
        program = ("import signal,time,sys; from pathlib import Path; "
                   f"signal.signal(signal.SIGTERM,lambda *_:(Path({str(cleaned)!r}).touch(),sys.exit(0))); "
                   f"Path({str(ready)!r}).touch(); time.sleep(10)")
        process = subprocess.Popen(self.runner_command(program), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        deadline = time.monotonic() + 3
        while not ready.exists() and process.poll() is None and time.monotonic() < deadline:
            time.sleep(0.01)
        self.assertTrue(ready.exists())
        process.send_signal(signal.SIGTERM)
        process.communicate(timeout=5)
        self.assertEqual(process.returncode, 128 + signal.SIGTERM)
        self.assertTrue(cleaned.exists())

    def test_wrapper_exit_preserves_descendant_cleanup_grace(self):
        cleaned = self.directory / "child-cleaned"
        child = ("import signal,time,sys; from pathlib import Path; "
                 "signal.signal(signal.SIGTERM,lambda *_:(time.sleep(0.2),"
                 f"Path({str(cleaned)!r}).touch(),sys.exit(0))); "
                 "print('child-ready',flush=True); time.sleep(10)")
        parent = ("import subprocess,sys; "
                  f"p=subprocess.Popen([sys.executable,'-c',{child!r}],stdout=subprocess.PIPE); "
                  "p.stdout.readline(); print('wrapper-exit',flush=True)")
        result = self.run_program(parent)
        self.assertEqual(result.returncode, 125, result.stdout + result.stderr)
        self.assertTrue(cleaned.exists(), result.stdout)
        self.assertIn("left descendants", result.stdout)

    def test_sigkill_reap_has_a_deadline(self):
        spec = importlib.util.spec_from_file_location("hardware_case_safety", RUNNER)
        runner = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(runner)
        process = mock.Mock(pid=1234)
        process.wait.side_effect = subprocess.TimeoutExpired("fake-case", 2)
        with mock.patch.object(runner, "group_exists", return_value=True), \
                mock.patch.object(runner, "signal_group") as send, mock.patch.object(runner, "LOGGER"):
            runner.stop_process(process, 0.001)
        process.wait.assert_called_once_with(timeout=2)
        self.assertEqual(send.call_args_list,
                         [mock.call(process, signal.SIGTERM), mock.call(process, signal.SIGKILL)])

    def fake_suite(self, failing_body):
        suite = self.directory / "suite"
        scripts = suite / "scripts"
        scripts.mkdir(parents=True)
        for name in ("ci-hardware-check.sh", "cann-env.sh", "run_hardware_case.py"):
            shutil.copyfile(ROOT / "scripts" / name, scripts / name)
        (scripts / "hardware_device.py").write_text("# Explicit CPU-only preflight fixture.\n", encoding="utf-8")
        # Use the same read-only header discovery and metadata as the real suite.
        (suite / "test").symlink_to(ROOT / "test", target_is_directory=True)
        commands = self.directory / "bin"
        commands.mkdir()
        (commands / "bisheng").write_text("#!/bin/sh\nexit 0\n", encoding="utf-8")
        binaries = sorted(set(re.findall(r'/(asc_stl_[a-zA-Z0-9_]+)"',
                                         (scripts / "ci-hardware-check.sh").read_text(encoding="utf-8"))))
        cmake = (f"#!{sys.executable}\nimport sys,pathlib,os\n"
                 "if '--build' in sys.argv:\n"
                 " root=pathlib.Path(sys.argv[sys.argv.index('--build')+1]); root.mkdir(parents=True,exist_ok=True)\n"
                 f" for name in {binaries!r}:\n"
                 "  body='#!/bin/sh\\necho '+name+' >> \"$ASC_STL_FAKE_CALLS\"\\n'\n"
                 f"  body+={failing_body!r} if name=='asc_stl_source_location_simt' else 'exit 0\\n'\n"
                 "  path=root/name; path.write_text(body); path.chmod(0o755)\n")
        (commands / "cmake").write_text(cmake, encoding="utf-8")
        for name in ("bisheng", "cmake"):
            (commands / name).chmod(0o755)
        environment = dict(os.environ, PATH=f"{commands}:{os.environ['PATH']}", ASCEND_HOME_PATH=str(suite),
                           ASC_STL_FAKE_CALLS=str(self.directory / "calls"), ASC_STL_HARDWARE_RUNS="1",
                           ASC_STL_HARDWARE_CASE_TIMEOUT_SECONDS="2", ASC_STL_HARDWARE_CLEANUP_GRACE_SECONDS="0.2")
        environment.pop("ASC_STL_CANN_ENV_SCRIPT", None)
        environment.pop("ASC_STL_HARDWARE_BUILD_DIR", None)
        return scripts / "ci-hardware-check.sh", environment

    def test_suite_stops_after_first_failed_or_timed_out_case(self):
        for body, expected in (("exit 7\n", 7), ("sleep 20\n", 124)):
            with self.subTest(expected=expected), tempfile.TemporaryDirectory() as directory:
                self.directory = Path(directory)
                script, environment = self.fake_suite(body)
                result = subprocess.run(["/bin/bash", str(script)], env=environment, capture_output=True,
                                        text=True, timeout=20)
                self.assertEqual(result.returncode, expected, result.stdout + result.stderr)
                calls = (self.directory / "calls").read_text(encoding="utf-8").splitlines()
                self.assertEqual(calls, ["asc_stl_source_location_simd", "asc_stl_source_location_simt"])
                results = self.directory / "suite/build/hardware/hardware-case-results.csv"
                self.assertEqual(results.read_text(encoding="utf-8").splitlines(),
                                 ["asc/std/source_location,17,simd,1,PASS", "asc/std/source_location,17,simt,1,FAIL"])

    def compile_fixture(self, standard, include):
        binary = self.directory / f"runtime-cxx{standard}"
        result = subprocess.run([COMPILER, f"-std=c++{standard}", "-Wall", "-Wextra", "-Werror", "-pedantic",
                                 "-I", str(include), str(FIXTURE / "main.cpp"), "-o", str(binary)],
                                capture_output=True, text=True, timeout=30)
        return binary, result

    def check_lifecycle(self, binary):
        for failure in range(12):
            with self.subTest(failure=failure):
                result = subprocess.run([str(binary), str(failure)], capture_output=True, text=True, timeout=5)
                self.assertEqual(result.returncode, int(failure != 0), result.stdout + result.stderr)
                self.assertIn(f"ASC_STL_RUNTIME_COMPLETE={int(failure == 0)}", result.stdout)
                if failure == 3:
                    self.assertNotIn("begin=aclrtSynchronizeStream", result.stdout)
                if failure == 11:
                    self.assertNotIn("fixture_launch", result.stdout)
                    self.assertNotIn("begin=aclrtSynchronizeStream", result.stdout)
                if failure == 4:
                    self.assertNotIn("begin=aclrtFree", result.stdout)
                    self.assertNotIn("begin=aclrtDestroyStream", result.stdout)
                if failure >= 2:
                    self.assertIn("end=aclFinalize", result.stdout)
                if failure >= 3:
                    self.assertIn("end=aclrtResetDevice", result.stdout)

    def test_acl_failure_and_cleanup_both_languages(self):
        for standard in (17, 20):
            binary, result = self.compile_fixture(standard, FIXTURE)
            self.assertEqual(result.returncode, 0, result.stderr)
            self.check_lifecycle(binary)

    def test_sdk_without_timeout_api_cannot_fall_back_to_unbounded_wait(self):
        old_sdk = self.directory / "old-sdk"
        shutil.copytree(FIXTURE / "acl", old_sdk / "acl")
        header = old_sdk / "acl/acl.h"
        text = header.read_text(encoding="utf-8")
        retained_lines = []
        for line in text.splitlines():
            if "TimeOut(" in line or "WithTimeout(" in line:
                continue
            retained_lines.append(line)
        header.write_text("\n".join(retained_lines), encoding="utf-8")
        _, result = self.compile_fixture(17, old_sdk)
        self.assertNotEqual(result.returncode, 0)
        self.assertIn("aclrtSetOpExecuteTimeOut", result.stderr)
        self.assertIn("aclrtSynchronizeStreamWithTimeout", result.stderr)


def main():
    global COMPILER
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler", default=os.environ.get("CXX", "c++"))
    args = parser.parse_args()
    COMPILER = args.compiler
    suite = unittest.defaultTestLoader.loadTestsFromTestCase(HardwareSafetyTests)
    result = unittest.TextTestRunner(verbosity=2).run(suite)
    return 0 if result.wasSuccessful() else 1


if __name__ == "__main__":
    raise SystemExit(main())
