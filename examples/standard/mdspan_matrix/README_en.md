# Two-dimensional access and padded tensor crop/transpose with mdspan

[简体中文](README.md) | [All examples](../../README_en.md)

## Overview

Create row-major and column-major 2-by-3 views over the same storage containing 1 through 6. Sum the two rows in each view, then write 20 through the row-major view and observe the same location through the other view.

The example also implements a tensor preprocessing operator. Its 2-by-3-by-4 input has batch/row/column strides of 24/7/1 elements and requires 42 storage elements. Select a batch, crop a row interval, sample columns, and transpose the crop into contiguous output. Eight configurations cover both batches, a full crop, a nonzero column offset, a non-divisible step, a step larger than the interval, and three empty-slice forms.

Public facilities: mdspan, extents, dextents, layout_right, layout_left, layout_stride, submdspan, strided_slice, pair and span::subspan.

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
padded_crop_transpose_cases=8 elements=26 guards=PASS
```

The Host exits 0 on success. Device success additionally requires exit code 0, cleanup_passed=1 and ASC_STL_STANDARD_DEVICE_PASS. device_cplusplus must be 201703 for C++17 or 202002 for C++20. The Host supplies actual GM inputs; the Kernel evaluates them and writes results back for comparison with constants defined separately from the computation.

## Operator logic and reason for using views

Manual indexing combines the batch stride, row stride, crop origin, sampling step and transposed output index at each access:

```cpp
output[column * rows + row] = input[batch * 24 + (row_first + row) * 7 +
    column_offset + column * column_stride];
```

This example defines the 24/7/1 strides once in the source mapping, combines crop rules with `submdspan`, and expresses the coordinate transform directly in the loop:

```cpp
transposed(column, row) = crop(row, column);
```

`span::subspan` partitions the output into separate windows. The Host oracle enumerates source coordinates and uses the original address formula independently to check 26 output elements, crop shapes, and sentinel values in every unused output position. It does not derive expected values from the library's mappings or slices. The views reduce repeated address composition in the computation loop; this does not establish fewer total lines or a speedup.

In `strided_slice{offset, extent, stride}`, `extent` is the covered source interval length; the result count is `extent == 0 ? 0 : 1 + (extent - 1) / stride`. For example, the column slice `{1, 3, 2}` selects source columns 1 and 3, giving two columns. Empty slices retain their empty dimensions without accessing elements.

## Constraints

Changing the layout changes indexing, not the stored data. Both sets of sums are computed before writing 20. C++17/20 access uses operator(). Storage must cover the mapping; the Device example uses pure-SIMT ordinary pointers without explicit GM/UB accessors, with tensor input in the device allocation uploaded by the Host. One active thread executes the eight small configurations to validate composed semantics.

Device tasks have a checked 10-second execution limit and a 10000-millisecond stream wait. The outer timeout bounds the process. After synchronization failure, buffers that may still be used are retained until reset/finalize; the result remains failed. Stop after a device error or timeout and check device health before further work. These scalar examples demonstrate semantics, not parallel speedups.

## Related APIs

- [mdspan](../../../docs/en/api/standard/containers/asc_std_mdspan/mdspan.md)
- [submdspan](../../../docs/en/api/standard/containers/asc_std_mdspan/submdspan.md)
- [strided_slice](../../../docs/en/api/standard/containers/asc_std_mdspan/strided_slice.md)
