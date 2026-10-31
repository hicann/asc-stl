# Parallel algorithms: inputs, synchronized results and bounded execution

[简体中文](README.md) | [All examples](../../README_en.md)

## Overview

This project exercises 57 separate cases through the public `<asc/algorithm>` API.
[cases.json](cases.json) specifies inputs and independently determined expected results.
Each case initializes the Runtime, allocates GM inputs, outputs, result slots and 8192
bytes of GM scratch space, submits work, waits with a deadline, reads results and records
cleanup. Successful submission alone does not establish correctness.

## Supported environment

Ascend 950PR/950DT, CANN with the ASC CMake module and BiSheng, and CMake 3.20 or newer.
Execution requires a matching Runtime, driver and available logical device 0.
The project uses SIMT and defines `CANN_ASC_STL_USE_SIMT_LAUNCH=1`. The parallel APIs
require Clang-compatible ASC translation units and are unavailable in ordinary GCC units.
C++17 and C++20 use separate builds and results.

## Build and run

Run from the repository root after sourcing the installed CANN environment:

```bash
source /usr/local/Ascend/ascend-toolkit/set_env.sh
cmake -S examples/extension/parallel_algorithms -B build/parallel_algorithms17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/parallel_algorithms17 -j2
python3 examples/extension/parallel_algorithms/run.py --binary build/parallel_algorithms17/asc_stl_parallel_algorithms \
  --standard 17 --report-dir build/parallel_algorithms17/results
```

The headers default to this repository's include tree; override `ASC_STL_INCLUDE_DIR`
when needed. Use standard 20 and a separate build and report directory for C++20.
The report directory must not already exist. The runner first checks the binary's
language mode and declared count of 57 cases.

## Expected result and execution limits

Success requires exit code 0, `passed: true` in `results.json`, and successful result
and cleanup checks for every selected case. Reports retain input contracts, submission,
synchronization, returned values, independent expectations and cleanup status.

- The Device task deadline is 10 seconds, set with `aclrtSetOpExecuteTimeOut`.
- Stream synchronization uses `aclrtSynchronizeStreamWithTimeout` with 10000 milliseconds.
- Each case uses a separate process with a default 40-second deadline. On timeout, the
  runner sends SIGTERM, allows 15 seconds for cleanup, then sends SIGKILL. Reaping after
  SIGKILL is bounded to 5 seconds; an unreaped process is recorded as `SIGKILL_UNREAPED`
  and execution stops. Signal handlers only set a flag; ACL calls remain in Host control flow.
- The first unexpected failure, timeout or interruption stops subsequent cases. Failed
  cleanup retains the relevant handle records. Synchronization failure stops further
  device operations and leaves the result failed.
- Process exit does not establish device recovery. Check device health before submitting
  more work after an error or timeout.

Use `--case adjacent_difference`, for example, to select one case; its result covers
only that case. Reports include binary, case-list and runner SHA-256 hashes. Record the
source revision and build command separately with validation evidence.

## Files

- [main.cpp](main.cpp): Host entry and resource lifetime.
- [parallel_cases.asc](parallel_cases.asc): the sole ASC compilation unit, which textually
  includes [cases.asc](cases.asc) and [cases_0.asc](cases_0.asc), [cases_1.asc](cases_1.asc),
  [cases_2.asc](cases_2.asc), [cases_3.asc](cases_3.asc), [cases_4.asc](cases_4.asc),
  [cases_5.asc](cases_5.asc). This avoids duplicate Runtime registration definitions
  produced by the current CANN pure-SIMT toolchain with multiple translation units.
- [parallel_example.h](parallel_example.h): shared Host context used by API snippets.
- [CMakeLists.txt](CMakeLists.txt): build configuration.
- [run.py](run.py): bounded execution and reporting.

Compiling an API snippet additionally requires this directory in the include path,
SIMT mode and the macro above. Compilation does not establish successful device execution.
