# GM atomics and barriers

[简体中文](README.md) | [All examples](../../README_en.md)

## Overview

Allocate GM on logical device 0, launch a single-thread SIMT kernel, and check atomic read-modify-write and barrier completion results.

## Supported environment

- Host + AI Core SIMT; C++17/20; CMake 3.20+.
- Ascend 950PR/950DT, CANN with the ASC CMake module and BiSheng.
- Source the installed CANN set_env.sh before configuring. Running requires the matching Runtime, driver and logical device 0.

## Files

- [kernel.asc](kernel.asc): Kernel and launch interface.
- [main.cpp](main.cpp): Host resource management and result checks.
- [example.h](example.h): shared launch declarations.
- [CMakeLists.txt](CMakeLists.txt): standalone build.

## Build and run

Run from the repository root after activating CANN:

```bash
cmake -S examples/extension/atomic_operations -B build/atomic_operations17 \
  -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_ASC_ARCHITECTURES=dav-3510 -DCMAKE_BUILD_TYPE=Release
cmake --build build/atomic_operations17 -j2
timeout --signal=TERM --kill-after=10s 60s build/atomic_operations17/asc_stl_atomic_operations
```

Use standard 20 and a separate build directory for C++20.

## Expected result and constraints

Success requires exit code 0 and `PASS: atomic_operations`. The Host synchronizes the stream before inspecting results and releasing memory. Storage must remain valid throughout asynchronous access. This is a usage example, not a performance measurement. After a timeout or device error, check device health before running another example.

Tasks have a checked 10-second execution limit and bounded 10000-millisecond stream synchronization. Output is initialized to a sentinel. Success also requires cleanup_passed=1. If synchronization fails, buffers are retained until reset/finalize and the run remains failed.
