# Allocator traits and nested access

[简体中文](README.md) | [All examples](../../README_en.md)

## Overview

Query each allocator through `allocator_traits`, then access the outer and inner allocator objects stored by `scoped_allocator_adaptor`.

## Supported environment

Host compiler with C++17/20 and its system libraries; CMake 3.20 or newer. CANN and an NPU are not required.

## Files

- [main.cpp](main.cpp): example and checks.
- [CMakeLists.txt](CMakeLists.txt): standalone build and CTest registration.

## Build and run

Run from the repository root:

```bash
cmake -S examples/standard/allocator_traits -B build/allocator_traits17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/allocator_traits17 -j2
ctest --test-dir build/allocator_traits17 --output-on-failure
```

Select standard 20 and a separate build directory for C++20.

## Expected result and constraints

This example checks each allocator's traits and public types with static_assert, then verifies the separate state of its outer and inner allocator objects. Successful compilation and exit code 0 indicate success; the program prints nothing. It does not demonstrate storage allocation or deallocation.

The current adaptor has no outer_traits member and does not merge propagation traits; see the [documented subset](../../../docs/en/api/standard/memory_management/asc_std_scoped_allocator/scoped_allocator_adaptor.md). Query each allocator explicitly rather than treating an inherited outer member as a combined result.
