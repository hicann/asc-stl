# GM/UB pipeline copy

[简体中文](README.md) | [All examples](../../README_en.md)

## Overview

Launch one AI Core kernel on logical device 0, copy 256 integers from GM to UB, add one, and copy them back for element-wise checks.

## Supported environment

- Host + AI Core SIMD; C++17/20; CMake 3.20+.
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
cmake -S examples/extension/pipeline_copy -B build/pipeline_copy17 \
  -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_ASC_ARCHITECTURES=dav-3510 -DCMAKE_BUILD_TYPE=Release
cmake --build build/pipeline_copy17 -j2
timeout --signal=TERM --kill-after=10s 60s build/pipeline_copy17/asc_stl_pipeline_copy
```

Use standard 20 and a separate build directory for C++20.

## Expected result and constraints

Success requires exit code 0 and `PASS: pipeline_copy`. The Host synchronizes the stream before inspecting results and releasing memory. Storage must remain valid throughout asynchronous access. This is a usage example, not a performance measurement. After a timeout or device error, check device health before running another example.
