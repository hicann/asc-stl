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

"""Exercise acquisition, pending-work and cleanup failures without a CANN Runtime."""

import itertools
import os
from pathlib import Path
import shutil
import subprocess
import tempfile
import unittest

ROOT = Path(__file__).resolve().parents[2]
COMPILER = shutil.which(os.environ.get("CXX", "c++"))
ACL_FIXTURE = """#pragma once
#include <cstddef>
using aclrtStream = void*;
constexpr int ACL_SUCCESS = 0;
constexpr int ACL_MEM_MALLOC_HUGE_FIRST = 0;
constexpr int ACL_MEMCPY_HOST_TO_DEVICE = 1;
constexpr int ACL_MEMCPY_DEVICE_TO_HOST = 2;
int aclInit(const char*);
int aclrtSetDevice(int);
int aclrtSetOpExecuteTimeOut(unsigned int);
int aclrtCreateStream(aclrtStream*);
int aclrtMalloc(void**, std::size_t, int);
int aclrtMemcpy(void*, std::size_t, const void*, std::size_t, int);
int aclrtMemset(void*, std::size_t, int, std::size_t);
int aclrtSynchronizeStreamWithTimeout(aclrtStream, int);
int aclrtFree(void*);
int aclrtDestroyStream(aclrtStream);
int aclrtResetDevice(int);
int aclFinalize();
"""
STARTUP_SOURCE = """#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "examples/extension/atomic_operations/example.h"
#include "examples/extension/warp_collectives/warp_example.h"
int record(const char* name)
{
    std::puts(name);
    const char* failure = std::getenv("ASC_STL_EXAMPLE_FAIL");
    return failure && std::strcmp(name, failure) == 0 ? 1 : 0;
}
int unexpected_call() { std::exit(99); }
int aclInit(const char*) { return record("aclInit"); }
int aclrtSetDevice(int) { return record("aclrtSetDevice"); }
int aclrtSetOpExecuteTimeOut(unsigned int) { return record("aclrtSetOpExecuteTimeOut"); }
int aclrtCreateStream(aclrtStream*) { return record("aclrtCreateStream"); }
int aclrtResetDevice(int) { return record("aclrtResetDevice"); }
int aclFinalize() { return record("aclFinalize"); }
int aclrtMalloc(void**, std::size_t, int) { return unexpected_call(); }
int aclrtMemcpy(void*, std::size_t, const void*, std::size_t, int) { return unexpected_call(); }
int aclrtMemset(void*, std::size_t, int, std::size_t) { return unexpected_call(); }
int aclrtSynchronizeStreamWithTimeout(aclrtStream, int) { return unexpected_call(); }
int aclrtFree(void*) { return unexpected_call(); }
int aclrtDestroyStream(aclrtStream) { return unexpected_call(); }
void launch_example(unsigned int*, unsigned int*, aclrtStream) { unexpected_call(); }
void launch_warp_example(unsigned int*, aclrtStream) { unexpected_call(); }
"""
SOURCE = """#include "examples/common/acl_cleanup.h"
int frees = 0;
int destroys = 0;
int resets = 0;
int finalizes = 0;
int fail = 0;
int aclrtFree(void*) { ++frees; return fail == 1 ? 1 : 0; }
int aclrtDestroyStream(aclrtStream) { ++destroys; return fail == 2 ? 1 : 0; }
int aclrtResetDevice(int) { ++resets; return fail == 3 ? 1 : 0; }
int aclFinalize() { ++finalizes; return fail == 4 ? 1 : 0; }
void clear() { frees = destroys = resets = finalizes = 0; }
int main()
{
    int input = 0, output = 0, stream = 0;
    DeviceExampleState state;
    if (!finish_device_example(state, nullptr, nullptr)) return 1;
    if (frees != 0 || destroys != 0 || resets != 0 || finalizes != 0) return 2;
    state.initialized = true;
    if (!finish_device_example(state, nullptr, nullptr)) return 3;
    if (frees != 0 || destroys != 0 || resets != 0 || finalizes != 1) return 4;
    clear();
    state.selected = state.pending = true;
    if (finish_device_example(state, &stream, &output, &input)) return 5;
    if (frees != 0 || destroys != 0 || resets != 1 || finalizes != 1) return 6;
    clear();
    state.pending = false;
    if (!finish_device_example(state, &stream, &output, &input)) return 7;
    if (frees != 2 || destroys != 1 || resets != 1 || finalizes != 1) return 8;
    for (fail = 1; fail <= 4; ++fail) {
        clear();
        if (finish_device_example(state, &stream, &output, &input)) return 9;
        if (frees != 2 || destroys != 1 || resets != 1 || finalizes != 1) return 10;
    }
    return 0;
}
"""


@unittest.skipUnless(COMPILER, "A Host C++ compiler is required")
class CleanupChecks(unittest.TestCase):
    def setUp(self):
        self.temporary = tempfile.TemporaryDirectory()
        self.addCleanup(self.temporary.cleanup)
        self.directory = Path(self.temporary.name)
        (self.directory / "acl").mkdir()
        (self.directory / "acl/acl.h").write_text(ACL_FIXTURE)

    def compile(self, sources, binary, standard):
        command = [COMPILER, f"-std=c++{standard}", "-I", str(self.directory), "-I", str(ROOT),
                   *map(str, sources), "-o", str(binary)]
        result = subprocess.run(command, capture_output=True, text=True, timeout=30, check=False)
        self.assertEqual(result.returncode, 0, result.stderr)

    def test_pending_work_retains_buffers_and_cleanup_errors_propagate(self):
        source = self.directory / "explicit_offline_fixture.cpp"
        source.write_text(SOURCE)
        for standard in (17, 20):
            with self.subTest(standard=standard):
                binary = self.directory / f"cleanup-{standard}"
                self.compile([source], binary, standard)
                result = subprocess.run([str(binary)], capture_output=True, text=True, timeout=10, check=False)
                self.assertEqual(result.returncode, 0, result.stdout + result.stderr)

    def test_startup_failures_release_only_acquired_resources(self):
        runtime = self.directory / "startup_fixture.cpp"
        runtime.write_text(STARTUP_SOURCE)
        cases = (
            ("aclInit", ("aclInit",)),
            ("aclrtSetDevice", ("aclInit", "aclrtSetDevice", "aclFinalize")),
            ("aclrtCreateStream", ("aclInit", "aclrtSetDevice", "aclrtSetOpExecuteTimeOut",
                                   "aclrtCreateStream", "aclrtResetDevice", "aclFinalize")),
        )
        names = ("atomic_operations", "pipeline_copy", "warp_collectives")
        for standard, name in itertools.product((17, 20), names):
            binary = self.directory / f"{name}-{standard}"
            self.compile([ROOT / "examples/extension" / name / "main.cpp", runtime], binary, standard)
            for failure, expected in cases:
                with self.subTest(standard=standard, example=name, failure=failure):
                    self.check_startup_failure(binary, failure, expected)

    def check_startup_failure(self, binary, failure, expected):
        environment = dict(os.environ, ASC_STL_EXAMPLE_FAIL=failure)
        result = subprocess.run([str(binary)], env=environment, capture_output=True,
                                text=True, timeout=10, check=False)
        self.assertEqual(result.returncode, 1, result.stdout + result.stderr)
        calls = tuple(line for line in result.stdout.splitlines() if line.startswith("acl"))
        self.assertEqual(calls, expected)
        self.assertIn("cleanup_passed=1", result.stdout)
        self.assertIn("FAIL:", result.stdout)


if __name__ == "__main__":
    unittest.main()
