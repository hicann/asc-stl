# Stream and event lifetime

[简体中文](README.md) | [All examples](../../README_en.md)

## Overview

Demonstrate device references, stream/event creation, non-owning references, recording,
waiting, timing, handle release/adoption, moves and explicit close. The program
initializes the Runtime on logical device 0, checks results, resets the device and finalizes.

## Supported environment

A Host C++17/20 compiler with its system libraries, CMake 3.20 or newer, and CANN providing
`acl/acl.h` and `libascendcl`. Execution requires a supported Ascend 950PR/950DT device
and matching driver and Runtime. This project manages device resources from the Host;
it does not compile a custom Kernel. The Host standard-library examples need neither dependency.

## Files

- [main.cpp](main.cpp): resource lifetime and result checks.
- [CMakeLists.txt](CMakeLists.txt): locate ACL and build the executable.

## Build and run

Source the installed CANN `set_env.sh`, then run from the repository root:

```bash
cmake -S examples/runtime/stream_event -B build/stream_event17 -DASC_STL_EXAMPLE_STANDARD=17
cmake --build build/stream_event17 -j2
timeout --signal=TERM --kill-after=10s 60s build/stream_event17/asc_stl_stream_event
```

Use standard 20 and a separate build directory for C++20. CTest never starts this program automatically.

## Expected result and constraints

Exit code 0 with no output indicates that checks, device reset and Runtime finalization
all succeeded. Failure returns a nonzero code. Non-owning references require their owners
to remain valid. After release, the adopting object is responsible for closing the handle.
Timing is checked only for a nonnegative result, not as a performance claim. Check device
health after a timeout or device error before running another program.
