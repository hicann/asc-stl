# Processing a span subrange

[简体中文](README.md) | [All examples](../../README_en.md)

## Overview

The input is 10, 20, 30, 40. Pass its two middle elements as a span to increment, then observe the original buffer through a read-only view. Also process an empty end subrange.

Public facilities: span and subspan.

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
cmake -S examples/standard/span_subrange -B build/span_subrange17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/span_subrange17 -j2
build/span_subrange17/asc_stl_span_subrange
ctest --test-dir build/span_subrange17 --output-on-failure
```

## Device build and run

Source the installed CANN set_env.sh, then run from the repository root:

```bash
cmake -S examples/standard/span_subrange -B build/span_subrange-device17 \
  -DASC_STL_EXAMPLE_DEVICE=ON -DASC_STL_EXAMPLE_STANDARD=17 \
  -DCMAKE_ASC_ARCHITECTURES=dav-3510 -DCMAKE_BUILD_TYPE=Release
cmake --build build/span_subrange-device17 --target asc_stl_span_subrange_device -j2
timeout --signal=TERM --kill-after=10s 60s build/span_subrange-device17/asc_stl_span_subrange_device
```

Use standard 20 and separate build directories for C++20. CTest runs the Host executable only; NPU execution is explicit.

## Expected result

The computed values are identical on Host and Device:

```text
buffer=10,21,31,40 slice_size=2 aliases=1 empty_size=0
```

The Host exits 0 on success. Device success additionally requires exit code 0, cleanup_passed=1 and ASC_STL_STANDARD_DEVICE_PASS. device_cplusplus must be 201703 for C++17 or 202002 for C++20. The Host supplies actual GM inputs; the Kernel evaluates them and writes results back for comparison with constants defined separately from the computation.

## Constraints

A span does not own storage, so the buffer must remain valid. A view with const elements does not copy data. The Device path first loads GM input into a thread-private array and creates a span over ordinary pointers; it performs no GM/UB pointer conversion.

Device tasks have a checked 10-second execution limit and a 10000-millisecond stream wait. The outer timeout bounds the process. After synchronization failure, buffers that may still be used are retained until reset/finalize; the result remains failed. Stop after a device error or timeout and check device health before further work. These scalar examples demonstrate semantics, not parallel speedups.

## Related APIs

- [span](../../../docs/en/api/standard/containers/asc_std_span/span.md)
