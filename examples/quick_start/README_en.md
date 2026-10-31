# Complete device example: Add + ReLU

[简体中文](README.md) | [Quick Start](../../docs/en/quick_start.md)

## Overview

This project computes `z = max(x + y, 0)` for 64 float elements. It demonstrates a
public ASC-STL algorithm inside an Ascend C kernel and the complete Host resource
lifecycle. One block performs scalar work; this is not a performance benchmark.

## Supported environment

C++17/20, CMake 3.20 or newer, and CANN with its AscendC CMake module and BiSheng.
The Kernel uses AI Core SIMD mode on Ascend 950PR/950DT. Execution additionally
requires a matching Runtime, driver and available logical device 0.

## Files

| File | Responsibility |
| --- | --- |
| [add_relu_kernel.cpp](add_relu_kernel.cpp) | Move GM/UB data with ASC-STL pipeline and call `asc::std::max` |
| [main.cpp](main.cpp) | Initialize, allocate, upload, launch, synchronize, download, verify and release |
| [CMakeLists.txt](CMakeLists.txt) | Use the official CANN AscendC build module and its generated launch header |

## Build and run

From the repository root, adjust the environment script and SoC to your installation:

```bash
source /usr/local/Ascend/ascend-toolkit/set_env.sh
cmake -S examples/quick_start -B build/quick-start-17 \
  -DASC_STL_EXAMPLE_STANDARD=17 -DSOC_VERSION=Ascend950PR_9599 \
  -DCMAKE_BUILD_TYPE=Release
cmake --build build/quick-start-17 -j2
timeout --signal=TERM --kill-after=10s 60s build/quick-start-17/asc_stl_quick_start
```

For C++20 use `-DASC_STL_EXAMPLE_STANDARD=20` and a separate build directory.
The executable finds its generated kernel library through `$ORIGIN/lib`, without
an extra library-search environment setting. When moving build artifacts, keep
the executable and its adjacent `lib` directory together.
The ASC-STL include directory is resolved from the source location by default;
`-DASC_STL_INCLUDE_DIR=/path/to/include` can select an installed tree.
The program uses ACL logical device 0. Execution needs a real supported Ascend 950,
a driver and a compatible CANN Runtime. A Toolkit-only machine can build it but
cannot establish hardware validation.

## Expected result and constraints

A successful run returns 0 and prints all of `elements=64 mismatches=0`,
`cleanup_passed=1` and `ASC_STL_QUICK_START_PASS`. Each ACL call reports its operation
and status. Inputs exercise negative, zero and positive sums. Output memory is
initialized to a sentinel, and the Host golden uses an ordinary conditional
expression rather than the ASC-STL operation under test.

The device task timeout is 10 seconds and the Stream timeout is 10000 milliseconds;
the outer `timeout` bounds the whole process. If synchronization fails, the program
does not free buffers that may still be in use or destroy their Stream. It attempts
and reports reset/finalize and retains failure. Check device health after a device
error, cleanup failure or timeout before submitting another kernel.

## Verify the result checker

Maintainers can explicitly test a controlled mismatch on a healthy device:

```bash
timeout --signal=TERM --kill-after=10s 60s \
  build/quick-start-17/asc_stl_quick_start --inject-mismatch
```

This changes one Host expected value; it does not submit a device-fault kernel.
The required result is `elements=64 mismatches=1`, `cleanup_passed=1`,
`ASC_STL_QUICK_START_EXPECTED_MISMATCH` and exit status 42. An arbitrary nonzero exit
is not an expected-failure pass. Omit the option for normal use.
