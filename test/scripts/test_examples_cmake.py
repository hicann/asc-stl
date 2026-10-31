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

"""Check independent and aggregate example builds without requiring CANN or NPU execution."""

import json
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
CMAKE = shutil.which("cmake")
CTEST = shutil.which("ctest")
HOST_NAMES = ("array_statistics", "span_subrange", "mdspan_matrix", "tuple_traits", "bit_flags",
              "allocator_traits", "explicit_allocator_vector", "pointer_alignment")


@unittest.skipUnless(CMAKE and CTEST, "CMake and CTest are required")
class ExampleBuilds(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.directory = Path(self.temporary.name)
        self.environment = dict(os.environ)
        self.environment.pop("ASCEND_HOME_PATH", None)
        self.environment.pop("ASC_STL_CANN_ENV_SCRIPT", None)

    def run_command(self, arguments, success=True):
        result = subprocess.run(arguments, env=self.environment, capture_output=True, text=True,
                                timeout=120, check=False)
        if success:
            self.assertEqual(result.returncode, 0, result.stdout + result.stderr)
        else:
            self.assertNotEqual(result.returncode, 0, result.stdout + result.stderr)
        return result

    def configure(self, source, build, options=(), success=True):
        return self.run_command([CMAKE, "-S", str(source), "-B", str(build),
                                 "-DCMAKE_BUILD_TYPE=Release", *options], success)

    def build_and_test(self, build, expected):
        self.run_command([CMAKE, "--build", str(build), "-j2"])
        result = self.run_command([CTEST, "--test-dir", str(build), "--show-only=json-v1"])
        names = {test["name"] for test in json.loads(result.stdout)["tests"]}
        self.assertEqual(names, {"examples.standard." + name for name in expected})
        self.run_command([CTEST, "--test-dir", str(build), "--output-on-failure"])

    def test_host_bundle_in_both_language_modes(self):
        for standard in (17, 20):
            with self.subTest(standard=standard):
                build = self.directory / str(standard)
                self.configure(ROOT / "examples", build, [f"-DASC_STL_EXAMPLE_STANDARD={standard}"])
                self.build_and_test(build, HOST_NAMES)

    def test_each_host_project_builds_independently(self):
        for standard in (17, 20):
            for name in HOST_NAMES:
                with self.subTest(example=name, standard=standard):
                    build = self.directory / f"{name}-{standard}"
                    self.configure(ROOT / "examples/standard" / name, build,
                                   [f"-DASC_STL_EXAMPLE_STANDARD={standard}"])
                    self.build_and_test(build, (name,))

    def test_root_option_keeps_testing_optional(self):
        build = self.directory / "root"
        self.configure(ROOT, build, ["-DBUILD_TESTING=OFF"])
        self.run_command([CMAKE, "--build", str(build), "--target", "asc_stl_pointer_alignment"], False)
        self.configure(ROOT, build, ["-DBUILD_TESTING=OFF", "-DASC_STL_BUILD_EXAMPLES=ON"])
        self.run_command([CMAKE, "--build", str(build), "--target", "asc_stl_pointer_alignment"])
        self.run_command([str(build / "examples/standard/pointer_alignment/asc_stl_pointer_alignment")])
        result = self.run_command([CTEST, "--test-dir", str(build), "--show-only=json-v1"])
        self.assertEqual(json.loads(result.stdout)["tests"], [])

    def test_unsupported_language_fails_configuration(self):
        for path in ("examples", "examples/standard/allocator_traits", "examples/extension/warp_collectives"):
            with self.subTest(source=path):
                build = self.directory / path
                result = self.configure(ROOT / path, build, ["-DASC_STL_EXAMPLE_STANDARD=23"], False)
                self.assertIn("ASC_STL_EXAMPLE_STANDARD must be 17 or 20", result.stderr)


if __name__ == "__main__":
    unittest.main()
