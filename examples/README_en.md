# ASC-STL examples

[简体中文](README.md) | [Quick Start](../docs/en/quick_start.md)

Each example has one source project shared by the Chinese and English guides.
API pages link here for complete programs, build instructions and result checks.
The standard examples use existing Host facilities; the other projects require CANN
and a supported Ascend device to execute.

## Example index

| Example | Main facilities | Execution |
| --- | --- | --- |
| [Allocator traits and nested access](standard/allocator_traits/README_en.md) | `allocator_traits / scoped_allocator_adaptor` | Host |
| [Vector with an explicit allocator](standard/explicit_allocator_vector/README_en.md) | `vector / type_traits` | Host |
| [Pointer traits and alignment](standard/pointer_alignment/README_en.md) | `memory / pointer_traits` | Host |
| [Complete Add + ReLU quick start](quick_start/README_en.md) | `std::max / pipeline` | Host + AI Core SIMD |
| [Warp collectives](extension/warp_collectives/README_en.md) | `warp` | Host + AI Core SIMT |
| [GM atomics and barriers](extension/atomic_operations/README_en.md) | `atomic / barrier` | Host + AI Core SIMT |
| [GM/UB pipeline copy](extension/pipeline_copy/README_en.md) | `pipeline / memory` | Host + AI Core SIMD |
| [57 parallel algorithm cases](extension/parallel_algorithms/README_en.md) | `algorithm / execution` | Host + AI Core SIMT |
| [Stream and event lifetime](runtime/stream_event/README_en.md) | `devices / stream` | Host + CANN Runtime |

## Build and run Host examples

Run these commands from the repository root. CMake 3.20 or newer and a C++17/20
compiler with its system libraries are required; CANN is not needed.

```bash
cmake -S examples -B build/examples17 -DASC_STL_EXAMPLE_STANDARD=17 -DCMAKE_BUILD_TYPE=Release
cmake --build build/examples17 -j2
ctest --test-dir build/examples17 --output-on-failure
```

Use `-DASC_STL_EXAMPLE_STANDARD=20` with a separate build directory for C++20.
All three Host examples must pass. Each subdirectory also supports a standalone
CMake build; see its README. `allocator_traits` includes compile-time type checks;
all three examples check observable results at runtime.

The product's top-level CMake also accepts `-DASC_STL_BUILD_EXAMPLES=ON` (default OFF).
`BUILD_TESTING=OFF` disables test registration when embedding the header library;
examples still build when explicitly enabled. To run only these tests in a product
build, use `ctest --test-dir <build> -R '^examples[.]' --output-on-failure`.

## Optional Runtime and Device builds

Source the installed CANN `set_env.sh` before configuring. The Kernel examples
use the CANN ASC or AscendC CMake modules and target Ascend 950PR/950DT;
requirements are listed in each project. Toolkit installation allows compilation;
execution additionally needs the matching Runtime, driver and available device.

```bash
cmake -S examples -B build/examples-device17 -DASC_STL_EXAMPLE_STANDARD=17 \
  -DASC_STL_BUILD_RUNTIME_EXAMPLES=ON -DASC_STL_BUILD_DEVICE_EXAMPLES=ON \
  -DCMAKE_ASC_ARCHITECTURES=dav-3510 -DSOC_VERSION=Ascend950PR_9599 -DCMAKE_BUILD_TYPE=Release
cmake --build build/examples-device17 -j2
```

Both options default to OFF. Runtime and Kernel programs are never automatically
executed by the build or CTest. The Runtime executable is under
`runtime/stream_event/`; Kernel projects have separate build directories under
`device/<name>/`. Each project's run instructions also apply there. Kernel build
targets are named `asc_stl_example_<name>`, for example `asc_stl_example_quick_start`.
The parallel algorithm project has a dedicated runner that records all 57 cases.

## Project conventions

- Use public headers and keep inputs, expected results and failure exit codes explicit.
- Explain the purpose, supported environment, files, build/run steps and expected result
  in both READMEs. Keep language and execution-mode requirements specific to the case.
- Use `ASC_STL_EXAMPLE_STANDARD` for 17/20 and `ASC_STL_INCLUDE_DIR` to select another
  include tree. The default resolves the headers in this repository.
- Document compilation, simulation and hardware execution separately. A successful
  build does not establish device correctness or a performance improvement.
- Keep API explanations and short snippets in `docs/`; link to the example source.
  Regression and error-path tests remain in `test/`.
