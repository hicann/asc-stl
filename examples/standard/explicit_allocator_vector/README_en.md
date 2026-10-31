# Vector with an explicit allocator

[简体中文](README.md) | [All examples](../../README_en.md)

## Overview

Construct a vector with a caller-owned 256-byte arena and exercise reserve, insertion, removal, clear and move assignment.

## Supported environment

Host compiler with C++17/20 and its system libraries; CMake 3.20 or newer. CANN and an NPU are not required.

## Files

- [main.cpp](main.cpp): example and checks.
- [CMakeLists.txt](CMakeLists.txt): standalone build and CTest registration.

## Build and run

Run from the repository root:

```bash
cmake -S examples/standard/explicit_allocator_vector -B build/explicit_allocator_vector17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/explicit_allocator_vector17 -j2
ctest --test-dir build/explicit_allocator_vector17 --output-on-failure
```

Select standard 20 and a separate build directory for C++20.

## Expected result and constraints

The program checks capacity, values, iterators, allocator identity and moved-from state. Exit code 0 with no output indicates success. The arena must outlive its containers; this bump allocator does not reclaim individual allocations and is not a general-purpose allocator.
