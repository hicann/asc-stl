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

import argparse
import json
import logging
import os
from pathlib import Path
import subprocess
import tempfile

LOGGER = logging.getLogger(__name__)
ROOT = Path(__file__).resolve().parents[2]
CASES = {
    "sdk_first": ["-DASC_STL_TEST_SDK_FIRST=1"],
    "sdk_last": ["-DASC_STL_TEST_SDK_LAST=1", "-DASC_STL_TEST_REVERSE_HEADERS=1"],
    "sdk_absent_first": ["-DASC_STL_TEST_SDK_ABSENT=1"],
    "sdk_absent_last": ["-DASC_STL_TEST_SDK_ABSENT=1", "-DASC_STL_TEST_REVERSE_HEADERS=1"],
}
MODES = {"host": [], "simd_macro": ["-D__CCE__=1"],
         "simt_macro": ["-D__NPU_COMPILER_INTERNAL_PURE_SIMT__=1"]}


def checked(command, environment, stage):
    result = subprocess.run(command, capture_output=True, text=True, check=False,
                            timeout=30, env=environment)
    if result.returncode:
        raise RuntimeError(stage + " failed:\n" + result.stderr)
    return result


def check_case(args, standard, name, directory):
    fixture = ROOT / "test/fixtures/runtime_sdk"
    command = [args.compiler, f"-std=c++{standard}", "-I", str(ROOT / "include"), *CASES[name]]
    if not name.startswith("sdk_absent"):
        command += ["-I", str(fixture)]
    environment = dict(os.environ)
    for option in ("CPATH", "CPLUS_INCLUDE_PATH", "C_INCLUDE_PATH"):
        environment.pop(option, None)
    source = fixture / "bindings.cpp"
    if args.preprocess_only:
        for mode, flags in MODES.items():
            checked([*command, *flags, "-E", str(source)], environment, name + "/" + mode)
        stage = "preprocess_only_host_and_simulated_device_macros"
    else:
        binary = directory / (name + str(standard))
        checked([*command, "-O2", "-Wall", "-Wextra", "-Werror", "-pedantic", str(source), "-o", str(binary)],
                environment, name + "/compile")
        checked([str(binary)], environment, name + "/offline_mock_run")
        stage = "host_compile_and_explicit_offline_mock_run"
    LOGGER.info("PASS: C++%s / %s / %s", standard, name, stage)
    return {"standard": standard, "case": name, "status": "PASS", "stage": stage}


def main():
    parser = argparse.ArgumentParser(description="Check typed SDK bindings and SDK-absent fallbacks")
    parser.add_argument("--compiler", required=True)
    parser.add_argument("--preprocess-only", action="store_true")
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    with tempfile.TemporaryDirectory(prefix="asc-stl-runtime-sdk-") as temporary:
        records = [check_case(args, standard, name, Path(temporary))
                   for standard in (17, 20) for name in CASES]
    if args.report:
        args.report.write_text(json.dumps({"explicit_offline_fixture": True, "cases": records,
                                          "actual_sdk_or_device_validation": False}, indent=2) + "\n")
    return 0


if __name__ == "__main__":
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    raise SystemExit(main())
