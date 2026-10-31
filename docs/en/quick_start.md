# ASC-STL Quick Start

[简体中文](../zh/quick_start.md) | [Language modes and compatibility](guide/cpp_compatibility.md)

Start with a Host program that needs no CANN. Then build the complete device
example to upload inputs, launch a kernel, verify results and release resources.
Building a binary and executing it on a supported NPU are separate checks.

## Choose an interface

ASC-STL is header-only. Add its `include` directory to the include path and include
the public header for the facility you need.

| Interface | Include path | Execution location |
| --- | --- | --- |
| Selected C++ standard-library facilities | `<asc/std/...>` | Host or Kernel, subject to each API's constraints |
| Ascend extensions | `<asc/...>` | Mainly Kernel: memory views, synchronization and parallel algorithms |
| Runtime facilities | `<asc/...>` | Host: devices, streams, launch and memory resources |

C++17 is the minimum, and C++20 is maintained. ASC-STL implements the documented
interface subset rather than replacing all of Host `std`. For example, `vector`
requires an explicit allocator and does not provide all copy operations. Check
language mode, execution location, element type and allocator requirements on the
[API page](api/README.md) before using a facility.

## Prepare the environment

Host algorithms and type facilities need a C++17 compiler and the required system
libraries. The currently exercised device toolchain is CANN 9.2.0-beta.2 with
BiSheng CCE 15;
actual execution also needs a supported Ascend 950PR/950DT, a matching driver and
CANN Runtime. Consult the [tested compatibility boundaries](guide/known_limitations.md)
when choosing an SDK build. Host Runtime calls backed by AscendCL must link
`ascendcl` and initialize the required resources.

```bash
git clone https://gitcode.com/cann/asc-stl.git
```

## Run a Host program

Save the following as `host_sample.cpp` beside the cloned `asc-stl` directory:

```cpp
#include <asc/std/algorithm>
#include <asc/std/optional>
#include <asc/std/type_traits>

int main() {
    static_assert(asc::std::is_integral_v<int>);
    int data[8] = {5, 3, 8, 1, 9, 2, 7, 4};
    asc::std::sort(data, data + 8);
    asc::std::optional<int> largest = data[7];
    return (asc::std::is_sorted(data, data + 8) && *largest == 9) ? 0 : 1;
}
```

```bash
g++ -std=c++17 -Wall -Wextra -I asc-stl/include host_sample.cpp -o host_sample
./host_sample
```

Exit status 0 means the result matches the expected ordering and largest value.
This program uses no Runtime facilities and needs no extra library. Use
`-std=c++20` to check the same program in the second supported mode.

For CMake integration, link the interface target:

```cmake
cmake_minimum_required(VERSION 3.20)
project(host_app LANGUAGES CXX)
add_subdirectory(asc-stl EXCLUDE_FROM_ALL)
add_executable(host_app host_sample.cpp)
target_link_libraries(host_app PRIVATE asc_stl::asc_stl)
```

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build
./build/host_app
```

## Run the complete device example

The [Add + ReLU project](../../examples/quick_start/README_en.md) has one shared
source tree for both languages. Its [kernel](../../examples/quick_start/add_relu_kernel.cpp)
uses `asc::std::max` to compute `z = max(x + y, 0)` for 64 floats. The
[Host program](../../examples/quick_start/main.cpp) allocates GM and a Stream,
uploads inputs, calls the launch function declared by the CANN-generated header,
synchronizes, downloads output and checks every value against an independent
Host golden. Cleanup failures also make the program fail.

Run from the cloned repository root. Adjust the environment script and SoC for
your supported installation:

```bash
cd asc-stl
source /usr/local/Ascend/ascend-toolkit/set_env.sh
cmake -S examples/quick_start -B build/quick-start-17 \
  -DASC_STL_EXAMPLE_STANDARD=17 -DSOC_VERSION=Ascend950PR_9599 \
  -DCMAKE_BUILD_TYPE=Release
cmake --build build/quick-start-17 -j2
timeout --signal=TERM --kill-after=10s 60s build/quick-start-17/asc_stl_quick_start
```

The source path contains `zh` because the source tree is shared; the linked project
instructions are in English. Use a separate `build/quick-start-20` directory and
`-DASC_STL_EXAMPLE_STANDARD=20` for C++20.

A successful run returns 0 and prints:

```text
cleanup_passed=1
elements=64 mismatches=0
ASC_STL_QUICK_START_PASS
```

The program uses ACL logical device 0. A container's `/dev/davinciN` suffix is not
an ACL logical device ID. A machine with only the Toolkit can build the program
but cannot provide a hardware execution result. Device task and Stream timeouts
are 10 seconds; retain the outer process timeout. After a device error or timeout,
check the environment before submitting more work.

This small scalar kernel demonstrates integration, not vectorized performance.
Continue with [GM/UB pipeline copying](../../examples/extension/pipeline_copy/README_en.md) or
[parallel algorithms](../../examples/extension/parallel_algorithms/README_en.md); these project
guides are currently in Chinese, with complete source files.

## Validate your checkout

From the repository root:

| Check | Command | Requirement |
| --- | --- | --- |
| Host gate | `bash scripts/ci-quick-check.sh` | Supported Host compiler and system libraries |
| Device compilation | `bash build.sh --device-compile -p <CANN path>` | CANN Toolkit |
| Simulation | `bash build.sh --cannsim -p <CANN path>` | CANN Toolkit and cannsim |
| Hardware regression | `bash scripts/ci-hardware-check.sh` | Supported, healthy real NPU |

The complete Host gate checks both C++17 and C++20, including system-library
requirements described in [language compatibility](guide/cpp_compatibility.md).
No hardware pass follows from compilation or simulation alone.
