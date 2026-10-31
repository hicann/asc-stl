# Two-dimensional access with mdspan

[简体中文](README.md) | [All examples](../../README_en.md)

## Overview

Create row-major and column-major 2-by-3 views over the same storage containing 1 through 6. Sum the two rows in each view, then write 20 through the row-major view and observe the same location through the other view.

Public facilities: mdspan, extents, layout_right and layout_left.

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
cmake -S examples/standard/mdspan_matrix -B build/mdspan_matrix17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/mdspan_matrix17 -j2
build/mdspan_matrix17/asc_stl_mdspan_matrix
ctest --test-dir build/mdspan_matrix17 --output-on-failure
```

## Device build and run

Source the installed CANN set_env.sh, then run from the repository root:

```bash
cmake -S examples/standard/mdspan_matrix -B build/mdspan_matrix-device17 \
  -DASC_STL_EXAMPLE_DEVICE=ON -DASC_STL_EXAMPLE_STANDARD=17 \
  -DCMAKE_ASC_ARCHITECTURES=dav-3510 -DCMAKE_BUILD_TYPE=Release
cmake --build build/mdspan_matrix-device17 --target asc_stl_mdspan_matrix_device -j2
timeout --signal=TERM --kill-after=10s 60s build/mdspan_matrix-device17/asc_stl_mdspan_matrix_device
```

Use standard 20 and separate build directories for C++20. CTest runs the Host executable only; NPU execution is explicit.

## Expected result

The computed values are identical on Host and Device:

```text
row_major_sums=6,15 column_major_sums=9,12
shared_storage=20 column_view=20
```

The Host exits 0 on success. Device success additionally requires exit code 0, cleanup_passed=1 and ASC_STL_STANDARD_DEVICE_PASS. device_cplusplus must be 201703 for C++17 or 202002 for C++20. The Host supplies actual GM inputs; the Kernel evaluates them and writes results back for comparison with constants defined separately from the computation.

## Constraints

Changing the layout changes indexing, not the stored data. Both sets of sums are computed before writing 20. C++17/20 access uses operator(). Storage must cover the mapping; the Device example uses thread-private ordinary pointers, not a GM/UB accessor.

Device tasks have a checked 10-second execution limit and a 10000-millisecond stream wait. The outer timeout bounds the process. After synchronization failure, buffers that may still be used are retained until reset/finalize; the result remains failed. Stop after a device error or timeout and check device health before further work. These scalar examples demonstrate semantics, not parallel speedups.

## Related APIs

- [mdspan](../../../docs/en/api/standard/containers/asc_std_mdspan/mdspan.md)
