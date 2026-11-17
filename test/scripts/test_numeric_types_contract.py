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

"""Compile numeric_types standalone headers, negative cases and configuration queries."""
import argparse
import json
import logging
import os
from pathlib import Path
import resource
import shutil
import subprocess
import tempfile

LOGGER = logging.getLogger(__name__)
ROOT = Path(__file__).resolve().parents[2]
CASE = ROOT / "test/cases/asc/numeric_types"


class Contract:
    def __init__(self, compiler, mode, temporary):
        self.compiler = compiler
        self.mode = mode
        self.temporary = temporary
        self.results = []

    def check(self, source, standard, expected=True, flags=()):
        suffix = ".cpp" if self.mode == "host" else ".asc"
        path = self.temporary / ("probe" + suffix)
        path.write_text(source, encoding="utf-8")
        command = [self.compiler, f"-std=c++{standard}", "-Werror", "-I", str(ROOT / "include")]
        if self.mode != "host":
            command += ["--asc-aicore-lang", "--npu-arch=dav-3510", "--cce-aicore-only"]
        if self.mode == "simt":
            command.append("--enable-simt")
        command += ["-fsyntax-only", *flags, str(path)]
        result = subprocess.run(command, capture_output=True, text=True, timeout=90, check=False)
        self.results.append({"command": command, "returncode": result.returncode, "expected_success": expected is True})
        diagnostic_matches = expected is True or expected in result.stderr + result.stdout
        if (result.returncode == 0) != (expected is True) or result.returncode < 0 or not diagnostic_matches:
            raise RuntimeError(f"Unexpected compilation outcome: {command}\n{result.stdout}\n{result.stderr}")

    def headers(self, standard):
        headers = ["asc/numeric_types"] + [str(p.relative_to(ROOT / "include"))
                                         for p in sorted((ROOT / "include/asc/__numeric_types").glob("*.h"))]
        for header in headers:
            self.check(f"#include <{header}>\n", standard)
        self.check('#include <asc/type_traits>\n#include <asc/numeric_types>\n'
                   'static_assert(asc::is_extended_floating_point_v<asc::float16>);\n'
                   'static_assert(!asc::is_extended_floating_point_v<asc::float8_e8m0>);\n', standard)

        self.check('#include <asc/version>\n#include <asc/numeric_types>\n'
                   'static_assert(CANN_ASC_STL_HAS_NUMERIC_TYPES == 1);\n', standard)

    def negatives(self, standard):
        suffix = "cpp" if self.mode == "host" else "asc"
        for path in sorted(CASE.glob(f"*.fail.{suffix}")):
            marker = "terminate" if path.name.startswith("invalid_") else "no matching function"
            if path.name == "host_native.fail.cpp":
                marker = "native_type"
            self.check(path.read_text(encoding="utf-8"), standard, expected=marker)

    def configuration(self, standard):
        self.check('#include <asc/numeric_types>\n'
                   'static_assert(!asc::is_numeric_conversion_supported_v<asc::float16, float>);\n'
                   'static_assert(asc::is_numeric_conversion_supported_v<asc::int4, int, '
                   'asc::rounding_mode::nearest_even, asc::saturation_mode::finite>);\n',
                   standard, flags=("-ffast-math",))
        if self.mode != "host":
            self.check('#include <asc/numeric_types>\n'
                       'static_assert(!asc::numeric_format_traits<asc::float16>::has_native_type);\n'
                       'static_assert(!asc::is_numeric_conversion_supported_v<asc::float16, float>);\n',
                       standard, flags=("--npu-arch=dav-2201",) if self.mode == "simd" else ("-U__BISHENG_CCEC__",))

    def runtime_failures(self, standard):
        if self.mode != "host":
            return
        for ndebug in (False, True):
            output = self.temporary / "invalid-runtime"
            command = [self.compiler, f"-std=c++{standard}", "-O2", "-I", str(ROOT / "include"),
                       str(CASE / "invalid_runtime.cpp"), "-o", str(output)]
            if ndebug:
                command.append("-DNDEBUG")
            subprocess.run(command, capture_output=True, check=True, timeout=90)
            for choice in range(4):
                result = subprocess.run([str(output), str(choice)], capture_output=True, timeout=10, check=False)
                self.results.append({"invalid_runtime": choice, "standard": standard,
                                     "ndebug": ndebug, "returncode": result.returncode})
                if result.returncode != -6:
                    raise RuntimeError(f"Invalid input did not terminate with SIGABRT: {choice} {result.returncode}")


def main():
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler", default=os.environ.get("CXX", "c++"))
    parser.add_argument("--mode", choices=("host", "simd", "simt"), default="host")
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    compiler = shutil.which(args.compiler)
    if not compiler:
        raise RuntimeError(f"Compiler unavailable: {args.compiler}")
    resource.setrlimit(resource.RLIMIT_CORE, (0, 0))
    with tempfile.TemporaryDirectory(prefix="numeric-types-") as temporary:
        contract = Contract(compiler, args.mode, Path(temporary))
        for standard in (17, 20):
            contract.headers(standard)
            contract.negatives(standard)
            contract.configuration(standard)
            contract.runtime_failures(standard)
        if args.report:
            args.report.parent.mkdir(parents=True, exist_ok=True)
            args.report.write_text(json.dumps(contract.results, indent=2) + "\n", encoding="utf-8")
        LOGGER.info("numeric_types %s contract checks=%d PASS", args.mode, len(contract.results))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
