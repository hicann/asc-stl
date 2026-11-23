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

"""Check extension trait preconditions, inclusion order and cross-TU identity."""
import argparse
import json
import logging
import os
from pathlib import Path
import shutil
import subprocess
import tempfile

LOGGER = logging.getLogger(__name__)
ROOT = Path(__file__).resolve().parents[2]


class Contract:
    def __init__(self, args, temporary):
        self.args = args
        self.temporary = temporary
        self.results = []

    def check(self, name, source, standard, diagnostic=None):
        suffix = ".cpp" if self.args.mode == "host" else ".asc"
        path = self.temporary / (name + suffix)
        path.write_text(source, encoding="utf-8")
        command = [self.args.compiler, f"-std=c++{standard}", "-Werror", "-I", str(ROOT / "include")]
        if self.args.mode != "host":
            command += ["--asc-aicore-lang", f"--npu-arch={self.args.npu_arch}", "--cce-aicore-only"]
        if self.args.mode == "simt":
            command += ["--enable-simt"]
        command += ["-fsyntax-only", str(path)]
        result = subprocess.run(command, capture_output=True, text=True, timeout=90, check=False)
        output = result.stdout + result.stderr
        expected_success = diagnostic is None
        self.results.append({"name": name, "standard": standard, "command": command,
                             "expected_success": expected_success, "returncode": result.returncode,
                             "diagnostic": output, "source": source})
        valid = result.returncode == 0 if expected_success else result.returncode > 0 and diagnostic in output
        if not valid:
            raise RuntimeError(f"Unexpected compilation result: {command}\n{output}")

    def preconditions(self, standard):
        for trait in ("is_bitwise_comparable", "is_trivially_relocatable"):
            for kind in ("struct", "union"):
                for index, cv in enumerate(("", "const ", "volatile ", "const volatile ")):
                    source = (f"#include <asc/type_traits>\n{kind} Forward;\n"
                              f"constexpr bool value = asc::{trait}_v<{cv}Forward>;\n")
                    self.check(f"{trait}_{kind}_{index}", source, standard, "requires a complete class or union")
            source = ("#include <asc/type_traits>\nstruct Value { unsigned value;\n"
                      "friend constexpr bool operator==(const Value& a, const Value& b) noexcept {\n"
                      "return a.value == b.value; } };\n"
                      f"static_assert(!asc::{trait}_v<Value>);\n"
                      f"template<> struct asc::{trait}<Value> : asc::std::true_type {{}};\n")
            self.check(f"{trait}_late_specialization", source, standard, "after instantiation")

    def include_order(self, standard):
        orders = (("asc/type_traits",), ("asc/numeric_types", "asc/type_traits"),
                  ("asc/type_traits", "asc/numeric_types"),
                  ("asc/std/type_traits", "asc/numeric_types", "asc/type_traits", "asc/type_traits"))
        for index, headers in enumerate(orders):
            source = "".join(f"#include <{name}>\n" for name in headers)
            source += ("static_assert(asc::is_low_precision_v<asc::float16>);\n"
                       "static_assert(!asc::is_bitwise_comparable_v<asc::float16>);\n"
                       "static_assert(asc::is_trivially_relocatable_v<asc::float16>);\n"
                       "static_assert(!asc::is_packed_numeric_v<int>);\n")
            self.check(f"include_order_{index}", source, standard)

    def cross_tu(self, standard):
        shared = self.temporary / "shared.h"
        shared.write_text("#pragma once\n#include <asc/type_traits>\n"
                          "struct Record { unsigned value; };\n"
                          "template<> struct asc::is_trivially_relocatable<Record> : asc::std::true_type {};\n",
                          encoding="utf-8")
        first = self.temporary / "first.cpp"
        first.write_text('#include "shared.h"\n#include <asc/numeric_types>\n'
                         'const bool* trait_address() { return &asc::is_low_precision_v<asc::float16>; }\n'
                         'bool record_property() { return asc::is_trivially_relocatable_v<Record>; }\n',
                         encoding="utf-8")
        second = self.temporary / "second.cpp"
        second.write_text('#include <asc/numeric_types>\n#include "shared.h"\n'
                          'extern const bool* trait_address();\nextern bool record_property();\n'
                          'int main() { return !(trait_address() == &asc::is_low_precision_v<asc::float16> '
                          '&& record_property() && asc::is_trivially_relocatable_v<Record>); }\n',
                          encoding="utf-8")
        executable = self.temporary / "cross-tu"
        command = [self.args.compiler, f"-std=c++{standard}", "-Wall", "-Wextra", "-Werror", "-pedantic",
                   "-I", str(ROOT / "include"), str(first), str(second), "-o", str(executable)]
        subprocess.run(command, capture_output=True, text=True, timeout=90, check=True)
        subprocess.run([str(executable)], capture_output=True, text=True, timeout=10, check=True)
        self.results.append({"name": "cross_tu", "standard": standard, "command": command,
                             "expected_success": True, "returncode": 0, "executed": True})


def main():
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--compiler", default=os.environ.get("CXX", "c++"))
    parser.add_argument("--mode", choices=("host", "simd", "simt"), default="host")
    parser.add_argument("--npu-arch", default="dav-3510")
    parser.add_argument("--report", type=Path)
    args = parser.parse_args()
    args.compiler = shutil.which(args.compiler)
    if not args.compiler:
        raise RuntimeError("Compiler unavailable")
    with tempfile.TemporaryDirectory(prefix="asc-type-traits-") as directory:
        contract = Contract(args, Path(directory))
        for standard in (17, 20):
            contract.include_order(standard)
            contract.preconditions(standard)
            if args.mode == "host":
                contract.cross_tu(standard)
        report = {"mode": args.mode, "results": contract.results, "passed": True}
        if args.report:
            args.report.parent.mkdir(parents=True, exist_ok=True)
            args.report.write_text(json.dumps(report, indent=2) + "\n", encoding="utf-8")
        LOGGER.info("type_traits %s contract: %d checks passed", args.mode, len(contract.results))


if __name__ == "__main__":
    main()
