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

"""Run the build entry point against isolated CMake and Host gate commands."""

import json
import os
from pathlib import Path
import shutil
import subprocess
import sys
import tempfile
import unittest


ROOT = Path(__file__).resolve().parents[2]


class BuildArguments(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.root = Path(self.temporary.name)
        self.counter = 0
        self.bash = shutil.which("bash")
        self.assertIsNotNone(self.bash)
        self.assertTrue(Path(self.bash).is_absolute())

    def run_build(self, arguments):
        self.counter += 1
        case = self.root / str(self.counter)
        self.repo = case / "asc-stl checkout"
        (self.repo / "scripts").mkdir(parents=True)
        shutil.copyfile(ROOT / "build.sh", self.repo / "build.sh")
        self.sentinel = self.repo / "build/sentinel"
        self.sentinel.parent.mkdir()
        self.sentinel.write_text("existing build data")
        self.cmake_log = case / "cmake.jsonl"
        self.gate_log = case / "gates.log"
        tools = case / "tools"
        tools.mkdir()
        cmake = tools / "cmake"
        cmake.write_text(
            "#!" + sys.executable + "\nimport json,os,sys\n"
            "with open(os.environ['CMAKE_TRACE'], 'a') as log:\n"
            "    log.write(json.dumps(sys.argv[1:])+'\\n')\n"
        )
        cmake.chmod(0o755)
        (self.repo / "scripts/ci-quick-check.sh").write_text(
            "printf 'host\\n' >> \"$BUILD_GATE_TRACE\"\n"
        )
        env = dict(os.environ, PATH=str(tools) + os.pathsep + os.environ["PATH"],
                   CMAKE_TRACE=str(self.cmake_log), BUILD_GATE_TRACE=str(self.gate_log))
        return subprocess.run([self.bash, str(self.repo / "build.sh"), *arguments],
                              env=env, capture_output=True, text=True, check=False, timeout=10)

    def cmake_calls(self):
        if not self.cmake_log.exists():
            return []
        return [json.loads(line) for line in self.cmake_log.read_text().splitlines()]

    def test_unexpected_arguments_stop_all_actions(self):
        cases = [
            ["typo"], ["-t", "typo"], ["--make_clean", "typo"],
            ["--prefix", "install path", "typo"], ["--", "--invalid"],
            ["one", "two"], ["unexpected argument"],
        ]
        for arguments in cases:
            with self.subTest(arguments=arguments):
                result = self.run_build(arguments)
                self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
                self.assertIn("Unexpected positional argument:", result.stdout)
                self.assertEqual(self.cmake_calls(), [])
                self.assertFalse(self.gate_log.exists())
                self.assertEqual(self.sentinel.read_text(), "existing build data")

    def test_default_install_preserves_complete_paths(self):
        result = self.run_build([])
        self.assertEqual(result.returncode, 0, result.stderr)
        calls = self.cmake_calls()
        self.assertEqual(len(calls), 3)
        self.assertEqual(calls[0][:4], ["-S", str(self.repo), "-B", str(self.repo / "build/pkg")])
        self.assertEqual(calls[-1], ["--install", str(self.repo / "build/pkg"),
                                    "--prefix", str(self.repo / "build/install")])

    def test_host_gate_runs_without_install(self):
        result = self.run_build(["-t"])
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(self.gate_log.read_text(), "host\n")
        self.assertEqual(self.cmake_calls(), [])

    def test_clean_option_removes_existing_build(self):
        result = self.run_build(["--make_clean"])
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertFalse(self.sentinel.exists())
        self.assertEqual(self.cmake_calls(), [])

    def test_explicit_prefix_remains_one_argument(self):
        prefix = self.root / "installation directory"
        result = self.run_build(["--prefix", str(prefix)])
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(self.cmake_calls()[-1][-2:], ["--prefix", str(prefix)])

    def test_end_of_options_without_extra_arguments_installs(self):
        result = self.run_build(["--"])
        self.assertEqual(result.returncode, 0, result.stderr)
        self.assertEqual(len(self.cmake_calls()), 3)


if __name__ == "__main__":
    unittest.main()
