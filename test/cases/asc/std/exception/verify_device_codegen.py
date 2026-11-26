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

"""Check the single termination kernel's release machine code without launching it."""

import argparse
import hashlib
import logging
import subprocess
from pathlib import Path


LOGGER = logging.getLogger(__name__)


def text_symbols(objdump, elf):
    listing = subprocess.run([objdump, "--syms", elf], check=True, capture_output=True, text=True)
    symbols = {}
    for line in listing.stdout.splitlines():
        fields = line.split()
        if len(fields) >= 5 and fields[-3] == ".text":
            symbols[fields[-1]] = (int(fields[0], 16), int(fields[-2], 16))
    return symbols


def verify_simd_trap(objdump, output, machine_code):
    reference = text_symbols(objdump, output / "reference.o")
    start, _ = reference["asc_stl_test_trap_begin"]
    end, _ = reference["asc_stl_test_trap_end"]
    opcode = machine_code["reference"][start:end]
    if len(opcode) != 4:
        raise SystemExit("The SIMD assembler reference must enclose one 32-bit TRAP instruction")
    for kind, code in machine_code.items():
        symbols = reference if kind == "reference" else text_symbols(objdump, output / f"{kind}.o")
        entry, size = symbols["terminate_device_compile"]
        if not size or entry % 4 or size % 4 or entry + size > len(code):
            raise SystemExit(f"Invalid SIMD kernel extent in {kind}: offset {entry}, size {size}")
        offsets = [i for i in range(entry, entry + size, 4) if code[i:i + 4] == opcode]
        LOGGER.info("%s: SIMD TRAP %s at kernel offsets %s", kind, opcode.hex(), [i - entry for i in offsets])
        if bool(offsets) != (kind != "loop"):
            raise SystemExit(f"Unexpected SIMD TRAP presence in the {kind} kernel")


def main():
    logging.basicConfig(level=logging.INFO, format="%(message)s")
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--package", type=Path, required=True)
    parser.add_argument("--source", type=Path, required=True)
    parser.add_argument("--include", type=Path, required=True)
    parser.add_argument("--output", type=Path, required=True)
    parser.add_argument("--standard", choices=("17", "20"), required=True)
    parser.add_argument("--mode", choices=("simt", "simd"), required=True)
    parser.add_argument("--arch", required=True)
    args = parser.parse_args()
    compiler = args.package / "bin/bisheng"
    objcopy = args.package / "tools/bisheng_compiler/bin/llvm-objcopy"
    args.output.mkdir(parents=True, exist_ok=True)
    simt = args.mode == "simt"
    common = [
        compiler, "--asc-aicore-lang", "--cce-aicore-only", f"--npu-arch={args.arch}",
        f"-std=c++{args.standard}", "-O3", f"-I{args.include}",
        f"-DCANN_ASC_STL_USE_SIMT_LAUNCH={int(simt)}",
    ]
    if simt:
        common.append("--enable-simt")
    machine_code = {}
    for kind, reference in (("product", None), ("reference", 1), ("loop", 0)):
        defines = [] if reference is None else [f"-DASC_STL_TEST_TERMINATION_REFERENCE={reference}"]
        elf = args.output / f"{kind}.o"
        section = args.output / f"{kind}.bin"
        subprocess.run([*common, *defines, "-c", args.source, "-o", elf], check=True)
        subprocess.run([objcopy, "--dump-section", f".text={section}", elf], check=True)
        code = section.read_bytes()
        LOGGER.info("%s: %d bytes, SHA256 %s", kind, len(code), hashlib.sha256(code).hexdigest())
        machine_code[kind] = code

    # SIMD tests the fault opcode independently of scheduling and register allocation.
    if not simt:
        verify_simd_trap(objcopy.with_name("llvm-objdump"), args.output, machine_code)
        return

    # The SIMT fault is a volatile store to an invalid address. Compare its full
    # instruction sequence, including address materialization, with the reference.
    if machine_code["reference"] == machine_code["loop"]:
        raise SystemExit("The assembler reference lost its fault instruction")
    if machine_code["product"] != machine_code["reference"]:
        raise SystemExit("std::terminate machine code differs from the device fault reference")


if __name__ == "__main__":
    main()
