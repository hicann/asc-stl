# Bit flags

[简体中文](README.md) | [All examples](../../README_en.md)

## Overview

The initial mask 5 has bits 0 and 2 set. Enable bit 5 to obtain 37, then clear bit 2 to obtain 33. Check population count, bit width, a single-bit flag and the zero mask.

Public facilities: cstdint, bit, popcount, bit_width and has_single_bit.

## Supported environment

- Host: a C++17/20 compiler and system libraries; CMake 3.20+. CANN is optional.
- Device: Ascend 950PR/950DT, CANN with the ASC CMake module and BiSheng, a matching driver and Runtime, and available logical device 0. The example uses SIMT with one active thread.

## Files

- [example.h](example.h): the same computation used by Host and Device.
- [example_types.h](example_types.h): plain input/output types.
- [check.h](check.h): Host inputs, independent expected values and output.
- [Shared Host entry](../../common/standard_host_main.cpp): construct input, evaluate and check results.
- [Shared Kernel](../../common/standard_kernel.asc) and [Host launch program](../../common/standard_device_main.cpp): upload, launch, bounded wait, download and cleanup.
- [CMakeLists.txt](CMakeLists.txt): standalone build.

## Host build and run

From the repository root:

```bash
cmake -S examples/standard/bit_flags -B build/bit_flags17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/bit_flags17 -j2
build/bit_flags17/asc_stl_bit_flags
ctest --test-dir build/bit_flags17 --output-on-failure
```

## Device build and run

Source the installed CANN set_env.sh, then run from the repository root:

```bash
cmake -S examples/standard/bit_flags -B build/bit_flags-device17 \
  -DASC_STL_EXAMPLE_DEVICE=ON -DASC_STL_EXAMPLE_STANDARD=17 \
  -DCMAKE_ASC_ARCHITECTURES=dav-3510 -DCMAKE_BUILD_TYPE=Release
cmake --build build/bit_flags-device17 --target asc_stl_bit_flags_device -j2
timeout --signal=TERM --kill-after=10s 60s build/bit_flags-device17/asc_stl_bit_flags_device
```

Use standard 20 and separate build directories for C++20. CTest runs the Host executable only; NPU execution is explicit.

## Expected result

The computed values are identical on Host and Device:

```text
enabled=37 final=33 active=2 width=6 single=1 zero_count=0
```

The Host exits 0 on success. Device success additionally requires exit code 0, cleanup_passed=1 and ASC_STL_STANDARD_DEVICE_PASS. device_cplusplus must be 201703 for C++17 or 202002 for C++20. The Host supplies actual GM inputs; the Kernel evaluates them and writes results back for comparison with constants defined separately from the computation.

## Constraints

Use unsigned integers for masks and respect each bit API's unsigned-type constraints. bit_width is the highest set-bit position plus one, not the population count.

Device tasks have a checked 10-second execution limit and a 10000-millisecond stream wait. The outer timeout bounds the process. After synchronization failure, buffers that may still be used are retained until reset/finalize; the result remains failed. Stop after a device error or timeout and check device health before further work. These scalar examples demonstrate semantics, not parallel speedups.

## Related APIs

- [popcount](../../../docs/en/api/standard/utilities/asc_std_bit/popcount.md)
- [bit_width](../../../docs/en/api/standard/utilities/asc_std_bit/bit_width.md)
- [has_single_bit](../../../docs/en/api/standard/utilities/asc_std_bit/has_single_bit.md)
