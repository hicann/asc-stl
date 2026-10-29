# ASC-STL

A C++ standard library for Ascend device programming — header-only, with a single public header organization shared by Host and Device code

English | [简体中文](README.md)

[📖 API Reference](docs/en/api/README.md) | [📚 Roadmap](docs/zh/roadmap/roadmap_v1_0_0.md) | [🧪 Quick Start](docs/en/quick_start.md) | [📄 LICENSE](LICENSE) | [🤝 Contributing](CONTRIBUTING.md)

## 🔥 Current Availability

**The implemented standard-layer facilities in the `master` development branch are available for use: `asc::std` covers the existing 16 categories and 74 public headers.** See [Current Standard-Layer Scope](#current-standard-layer-scope) below. Ascend extensions and Runtime facilities remain under active development.

The current development branch is `master`, with source version identifier `1.0.0`. Currently, no formal [tag](https://gitcode.com/cann/asc-stl/tags) or [Release](https://gitcode.com/cann/asc-stl/releases) has been published; the formal release date is to be announced.

### 🚀 Release and Refinement Plan

| Target | Current status | Next steps |
| --- | --- | --- |
| `master` | Implemented standard-layer facilities available as documented; extensions and Runtime in progress | Continue implementation, API constraints, examples and regression coverage |
| First formal `v1.0.0` | Not released | Publish the tag, Release and feature notes together |
| Later iterations | Planned | Refine extension/Runtime capabilities, quality and documentation in batches |

### 📖 Documentation

- [Current standard-layer scope](#current-standard-layer-scope) · [Complete standard-layer API support list](docs/zh/api/standard/standard.md)
- [ASC-STL v1.0.0 supported scope](docs/zh/roadmap/roadmap_v1_0_0.md)
- [API reference](docs/en/api/README.md): language modes, execution locations, constraints and examples

## 🚀 Overview

### Design Goals

Developing compute kernels for Ascend devices requires general-purpose C++ facilities such as the type system, containers and views, algorithms, numerics, atomics, synchronization, memory, and parallel operations. ASC-STL delivers these capabilities as a **header-only library** and produces no separate dynamic or static library:

- **Standard idioms straight into kernels**: types, algorithms, numerics, and other general-purpose facilities are provided in standard C++ style, with Host and Device code sharing a single public header organization;
- **Platform capabilities made explicit**: Ascend platform features — the GM/UB address spaces, the device execution hierarchy, device atomics and thread synchronization, and device parallel algorithms — all have well-defined, explicit public interfaces;
- **Runtime capabilities encapsulated**: runtime facilities such as devices, streams/events, kernel invocation, and memory resources are exposed through public C++ interfaces, without leaking low-level Runtime API types.

### Interface Composition

| Interface | Namespace / include path | Scope | Current status |
| --- | --- | --- | --- |
| C++ standard library interface | `asc::std` · `<asc/std/...>` | 16 categories: language support, concepts, diagnostics, memory management, metaprogramming, general utilities, containers, iterators, ranges, algorithms, strings, text processing, numerics, date and time, input/output, and concurrency support | Implemented facilities available as documented |
| Ascend extension interface | `asc` · `<asc/...>` | 9 categories: device atomics and thread synchronization, asynchronous data movement, address spaces and memory views, multidimensional data views and movement, device execution hierarchy and collective operations, device parallel algorithms, and device-side numerics and type utilities | Partial implementation; ongoing refinement |
| Runtime interface | `asc` · `<asc/...>` | 4 categories: device/stream/event management, kernel invocation, device execution policies and execution requirements, and memory resources/memory pools/buffers | Partial implementation; ongoing refinement |

### Overall Architecture

![Figure 1 ASC-STL design architecture](docs/en/figures/asc_stl_architecture_en.png)

- ASC-STL is a header-only C++ library whose interfaces fall into three parts: the C++ standard library interfaces, the Ascend extension interfaces, and the Runtime interfaces;
- Device-side programming capability builds on CANN Ascend C; code is compiled by the BiSheng compiler (based on Clang 15.0.5) and runs on the Ascend 950PR / 950DT processor;
- Runtime dependencies are the CANN Runtime (AscendCL Runtime API) and the NPU driver, which provide device management, kernel invocation, memory management, and device access.

### Choosing the Right Facilities

- For general-purpose types, algorithms, numerics, and synchronization logic → use the **C++ standard library interfaces** (use the documented standard-layer subset);
- For GM/UB memory operations, device atomics and thread cooperation, and device parallel algorithms → use the **Ascend extension interfaces** (partial implementation; ongoing refinement);
- For managing devices, streams/events, and kernel invocation → use the **Runtime interfaces** (partial implementation; ongoing refinement).

## 🔍 Directory Layout

ASC-STL is organized as a header-only library. Public headers live under `include/asc/`; tests, CMake configuration, and check scripts live in separate directories.

```text
asc-stl/
├── include/
│   └── asc/                         # Root of the ASC-STL public headers
│       ├── __config                 # Unified configuration entry
│       ├── std/                     # C++ standard library interfaces: <asc/std/...>
│       │   └── ...                  # Other internal implementation directories (__ prefix)
│       ├── algorithm                # Device parallel algorithms
│       ├── atomic                   # Device atomic operations
│       ├── collectives              # Thread-group cooperative operations
│       ├── execution                # Aggregate entry for device execution policies
│       ├── memory                   # GM, UB, and memory views
│       ├── stream                   # Stream and event management
│       └── ...                      # Other device-capability public headers
├── docs/                            # Project documentation and product roadmap
├── test/                            # Host, device, and simulation tests
├── cmake/                           # CMake install and export configuration
├── scripts/                         # Build and check scripts
├── CMakeLists.txt                   # Top-level CMake configuration
├── version.cmake                    # Version definitions
├── build.sh                         # Build and test entry script
├── README.md                        # Project README (Chinese)
├── README_en.md                     # Project README (English)
└── LICENSE                          # Product license
```

The public headers under `include/asc/std/` provide the standard-library entry points included as `<asc/std/...>`; the remaining public headers under `include/asc/` provide the Ascend extension and Runtime entry points included as `<asc/...>`.

## ⚡️ Quick Start

For a quick tour of using ASC-STL, see [Quick Start](docs/en/quick_start.md): environment setup, usage on the Host and in kernels, compiling and running, and local verification — with a Host program and a complete device project covering input, launch, result verification and cleanup.

ASC-STL itself is header-only and has no separate library to build. Ordinary Host algorithms and type facilities can be used by including their public headers. Runtime APIs backed by AscendCL additionally require the corresponding CANN runtime, linking against `ascendcl`, and the required device/resource initialization. Host use needs a C++17 compiler and the required system libraries; kernel compilation and execution require CANN (see [Software/Hardware Compatibility](#-softwarehardware-compatibility)).

### Requirements

| Dependency | Version / notes |
| --- | --- |
| CANN | 9.2.0 |
| BiSheng CCE / clang | 15.0.5 |
| g++ | C++17 as the product minimum; the full Host test suite additionally requires C++20 support |
| CMake | ≥ 3.20 |
| Processor | Ascend 950PR / 950DT processor |

Different builds of the same CANN version may use different SDK directory layouts. The device-layer queries first include `c_api/utils/sys_var.h` and fall back to `c_api/sys_var/sys_var.h`; a compilation error is raised when neither is present. The 64-bit multiply-overflow check for Tensor descriptors uses 32-bit segmented arithmetic to keep older BiSheng versions from emitting a device-side `__multi3` symbol that cannot be linked on the dynamic-descriptor path; the public interfaces and status codes are unchanged.

The Host standard-library interfaces also depend on the accompanying C library and the C++ standard library. The C++20 `<asc/std/cuchar>` interfaces `c8rtomb` and `mbrtoc8` require the system `<cuchar>` to actually export them; on GNU/Linux this usually means glibc 2.36 or newer together with a libstdc++ built with the corresponding capabilities. Upgrading the compiler alone is therefore not sufficient — compilation, linking, and execution should be verified in the same environment. Ubuntu 24.04 with GCC 13 / glibc 2.39 provides this set of interfaces; do not inject a newer glibc globally into an older CANN environment. The full Host gate exercises both C++17 and C++20 modes and must not skip tests because system libraries are missing.

### C++ Language Compatibility

C++17 is the minimum and C++20 remains supported. Newer facilities that can be expressed with ordinary templates are backported as documented subsets. Predicate names are Boolean variable templates in C++17 and native concepts when the C++20 configuration supports them. Language syntax, Host/Device execution and constant evaluation are separate requirements.

`<asc/std/version>` supplies `CANN_ASC_STL_HAS_*` macros with values 0 or 1. Standard-named feature macros remain under Host-library control by default; old ASC checks can use an explicit migration option. See [language modes and compatibility](docs/en/guide/cpp_compatibility.md) for the interfaces and configuration rules.

### Include Directly (Host Example)

```cpp
// sample.cpp — headers only, no library to link against
#include <asc/std/optional>
#include <asc/std/type_traits>

int main() {
    static_assert(asc::std::is_integral_v<int>);
    asc::std::optional<int> value = 42;
    return *value == 42 ? 0 : 1;
}
```

```bash
g++ -std=c++17 -Wall -Wextra -I asc-stl/include sample.cpp -o sample && ./sample
```

### CMake Integration

```cmake
add_subdirectory(asc-stl)

target_link_libraries(your_target PRIVATE asc_stl::asc_stl)   # INTERFACE target; propagates include paths only
```

### Building and Running Tests

```bash
# Option 1: build entry script (installs headers and CMake configuration to build/install by default)
bash build.sh

# Option 2: Host gate (style checks, self-containedness of public headers, C++17/C++20 Host semantic
#           unit tests; requires Python 3)
bash scripts/ci-quick-check.sh

# Option 3: CMake + CTest (test targets must be enabled explicitly; the device-compile and simulation
#           gates require a CANN environment and are enabled via build.sh --device-compile / --cannsim)
cmake -B build -DBUILD_TESTING=ON && cmake --build build -j && cd build && ctest
```

Run `bash scripts/ci-hardware-check.sh` for real-hardware regression; it runs three rounds each in C++17 and C++20 by default.

### Known Device Limits

The current BiSheng/CCE 15 fingerprint has a confirmed pure-SIMT miscompile for continuing reverse traversals of constant-initialized local arrays. Separate combined constant-array (B022) and long-string/local-arena (B027) original code shapes remain unresolved. Their adapted runtime/staged tests preserve behavior checks, but passing them does not prove the original shapes or SDK have recovered. See [known compatibility and execution limits](docs/en/guide/known_limitations.md) and the [detailed regression record](test/support/README.md). These limits do not mean that all arrays or strings are unavailable.

## 💻 Software/Hardware Compatibility

ASC-STL requires the following software and hardware environment:

- Ascend products: [Ascend 950PR / 950DT processors](https://www.hiascend.com/hardware/processor)
- CPU architecture: `aarch64` / `x86_64`
- OS: a supported Linux (check [compatibility](https://www.hiascend.com/hardware/compatibility))
- Software dependencies:
  - CANN 9.2.0 or later (BiSheng CCE/clang 15.0.5 and the AscendCL Runtime ship with CANN)
  - CMake ≥ 3.20

The table retains the planned compatibility targets for each version. Actual compatibility depends on the specific SDK build and validation result; the listed [CANN](https://www.hiascend.com/developer/download/community/result?module=cann) versions are not proof of support for every later package:

<table style="width: 75%; margin: 0 auto;">
  <colgroup>
    <col style="width: 30%">
    <col style="width: 30%">
    <col style="width: 40%">
  </colgroup>
  <thead>
      <tr>
          <th>ASC-STL Version</th>
          <th>Supported CANN Package</th>
          <th>Supported Ascend Products</th>
      </tr>
  </thead>
  <tbody style="text-align: center">
      <tr>
          <td>master development branch (version identifier 1.0.0)</td>
          <td>Community 9.2.0 and later</td>
          <td><a href="https://www.hiascend.com/hardware/processor">Ascend 950PR / 950DT processors</a></td>
      </tr>
  </tbody>
</table>

## 🧰 IDE Support

The project sets `CMAKE_EXPORT_COMPILE_COMMANDS`; after configuration, `compile_commands.json` is generated in the build directory for clangd, VS Code, and other IDEs. As a header-only library has no compilation units of its own, this database is produced by the test build targets:

```bash
cmake -B build            # generates build/compile_commands.json
ln -sf build/compile_commands.json .
```

Conditional-compilation macros for device-side code are injected by the CCE toolchain; guidance for previewing device paths in online IDEs is TBD.

## 📊 Version Status and Feature Inventory

### Current Standard-Layer Scope

The table lists all **74 current public standard-layer headers** in the existing **16 categories**. Include them as `<asc/std/...>` and use the `asc::std` namespace.

| Category | Public headers | Currently available scope |
| --- | --- | --- |
| [Language support](docs/zh/api/standard/language_support/language_support.md) | `cfloat` `climits` `cstddef` `cstdint` `exception` `compare` `new` `limits` `source_location` `version` `ciso646` `cstdalign` `cstdbool` | Fundamental types and numeric macros, comparison categories, source locations, capability macros, termination and placement-new facilities. |
| [Concepts](docs/zh/api/standard/concepts/concepts.md) | `concepts` | Type and expression predicates: Boolean variable templates in C++17 and native concepts where supported in C++20. |
| [Diagnostics](docs/zh/api/standard/diagnostics/diagnostics.md) | `cassert` `cerrno` `system_error` | Assertions, error-number macros, error codes, error conditions and error categories. |
| [Memory management](docs/zh/api/standard/memory_management/memory_management.md) | `memory` `scoped_allocator` | Pointer and allocator traits, allocator protocols, object lifetime and uninitialized-memory algorithms. |
| [Metaprogramming](docs/zh/api/standard/metaprogramming/metaprogramming.md) | `type_traits` `ratio` | Type queries and transformations, compile-time constants and rational arithmetic. |
| [General utilities](docs/zh/api/standard/utilities/utilities.md) | `utility` `functional` `tuple` `optional` `variant` `expected` `bit` `bitset` `cstdlib` | Move/forward/swap utilities, function objects, tuples, optional values, variants, expected results, bit operations and bit sets. |
| [Containers](docs/zh/api/standard/containers/containers.md) | `array` `vector` `deque` `list` `forward_list` `inplace_vector` `map` `set` `unordered_map` `unordered_set` `queue` `stack` `span` `mdspan` | Fixed-capacity and dynamic containers, associative containers, adapters and contiguous/multidimensional views; dynamic containers use explicit allocators. |
| [Iterators](docs/zh/api/standard/iterators/iterators.md) | `iterator` | Iterator traits, traversal helpers and insertion, reverse and move adapters. |
| [Ranges](docs/zh/api/standard/ranges/ranges.md) | `ranges` | Range access and predicates, range views and composition such as filtering, transformation and slicing. |
| [Algorithms](docs/zh/api/standard/algorithms/algorithms.md) | `algorithm` `execution` | Traversal, search, comparison, copying, transformation, partitioning, sorting, binary search, set, heap and permutation algorithms, plus execution-policy vocabulary. |
| [Strings](docs/zh/api/standard/strings/strings.md) | `cstring` `string` `string_view` | C-string and byte operations, explicitly allocated basic_string, character traits and string views. |
| [Text processing](docs/zh/api/standard/text_processing/text_processing.md) | `cctype` `charconv` `cuchar` `cwchar` `cwctype` `format` | Character classification, numeric text conversion, wide/multibyte character facilities and format_to output facilities. |
| [Numerics](docs/zh/api/standard/numerics/numerics.md) | `cmath` `complex` `ccomplex` `ctgmath` `numbers` `linalg` `random` `numeric` | Scalar mathematics, complex numbers, constants, random engines/distributions and numeric algorithms; linalg currently supplies scaled, conjugated and transposed views. |
| [Date and time](docs/zh/api/standard/chrono/chrono.md) | `chrono` `ctime` | Durations, time points, calendars and conversions, clock facilities and time conversion. |
| [Input/output](docs/zh/api/standard/input_output/input_output.md) | `cinttypes` | Integer-format macros and intmax_t utilities. |
| [Concurrency support](docs/zh/api/standard/concurrency/concurrency.md) | `atomic` `barrier` `latch` `semaphore` `mutex` `shared_mutex` | Atomics, barriers, latches and semaphores, plus RAII lock management. |

## 📖 Resources

### Documentation

| Document | Description |
| --- | --- |
| [Quick Start](docs/en/quick_start.md) | Environment setup, Host/Kernel usage, and local verification, with tested examples (in Chinese) |
| [v1.0.0 supported scope](docs/zh/roadmap/roadmap_v1_0_0.md) | Current standard-layer functionality and extension/Runtime refinement directions |
| [Contributing guide](CONTRIBUTING.md) | Contribution workflow, contribution scenarios, and code/test requirements |
| [API reference](docs/en/api/README.md) | Entry point to the ASC-STL public-interface reference: standard library, Ascend extensions, and Runtime |

## 👥 Collaborators

- Prof. Xiong Shengwu's team, Wuhan University of Technology
- Lu Xiongbo, Jiang Zhenyu, Wang Yike

## 📝 Additional Information

- **Security statement**: [SECURITY.md](SECURITY.md);
- **License**: [Apache License 2.0](LICENSE).
