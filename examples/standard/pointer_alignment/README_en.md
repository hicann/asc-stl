# Pointer traits and alignment

[简体中文](README.md) | [All examples](../../README_en.md)

## Overview

Demonstrate addressof, pointer_traits, to_address, alignment queries and locating aligned storage in an existing buffer.

## Supported environment

Host compiler with C++17/20 and its system libraries; CMake 3.20 or newer. CANN and an NPU are not required.

## Files

- [main.cpp](main.cpp): example and checks.
- [CMakeLists.txt](CMakeLists.txt): standalone build and CTest registration.

## Build and run

Run from the repository root:

```bash
cmake -S examples/standard/pointer_alignment -B build/pointer_alignment17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/pointer_alignment17 -j2
ctest --test-dir build/pointer_alignment17 --output-on-failure
```

Select standard 20 and a separate build directory for C++20.

## Expected result and constraints

Compile-time checks verify pointer types; runtime checks verify addresses, alignment and adjusted space. Exit code 0 with no output indicates success. assume_aligned requires an already aligned pointer; it does not repair a misaligned address.
