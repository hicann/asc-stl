# ASC-STL test gates

Tests are organized by stable product Header paths, never by implementation
wave, batch, delivery-unit, or progress identifiers. A target such as
`asc/std/source_location` maps directly to
`cases/asc/std/source_location/`; a target ending in `.h` drops only that
extension.

Each case may provide these metadata-controlled assets:

```text
host.pass.cpp
device.compile.asc
*.fail.cpp
*.fail.asc
runtime/cannsim/...
runtime/hardware/...
```

`metadata/headers.json` registers the product Header tree, direct product
dependencies, test applicability, and exceptional case-local assets. It must
not contain implementation scheduling or migration provenance. Generated
self-containment translation units, build products, CTest state, simulator
logs, and hardware reports belong only in out-of-source build directories.

The stable formal gate mirror entry points are:

```text
scripts/ci-quick-check.sh
scripts/ci-device-compile-check.sh
scripts/ci-cannsim-check.sh
```

`scripts/quick_check_code.sh` is the explicit local CodeCheck preflight, while
its pre-commit hooks also reject direct Python `print()` calls to mirror the
formal `G.LOG.02` logging rule. Style discovery is limited to ASC-STL-owned
source roots so unrelated infrastructure injected by formal CI is not audited.
`scripts/ci-hardware-check.sh` is the local Ascend950 enhancement. All product
and test compilation covers the mandatory C++17 baseline and supported C++20
mode.

## Working on a standard header

Use `test/cases/asc/std/<header>/` for each public header. Keep domain-specific
fixtures in its `support/` subdirectory. The shared support directory holds
fixtures used by several headers and the CANN launch and result-checking code.

| Asset below the header directory | Purpose |
| --- | --- |
| `*.pass.cpp` | Host runtime assertions and compile-time contracts. CMake discovers positive cases and labels them by header. |
| `*.fail.cpp`, `*.fail.asc` | Unsupported or ill-formed uses. Register the expected negative case in the header metadata. |
| `device.compile.asc` | Device overload and type instantiation. Shared semantic cases can also be selected by header metadata. |
| `device_checks.h`, `simd_checks.h` | Executable device contracts. The common runner reports a result for each header and fails if any selected contract fails. |
| `examples.json` | Language modes and expected outcomes for that header's executable API pages. Headers that only forward or declare no API can have no registry. |

For a new positive file, register its basename in the header's
`additional_cases` in `test/metadata/headers.json` unless it is already the
primary `host.pass.cpp`. Use a named CMake registration if the case needs a
special language restriction, compile definition or link dependency. Host
compile-fail cases belong next to the header's positive cases. Record the
expected diagnostic in `test/scripts/validate_negative_boundaries.py` so the
`boundary.host` gate can verify the reason for rejection.

From the checkout root, these commands run the standard-header Host cases,
select just the `optional` cases, and execute that header's C++20 API examples.

```bash
cmake -S . -B build/std-host -DCMAKE_CXX_COMPILER=g++-13 -DCMAKE_BUILD_TYPE=Release
cmake --build build/std-host --parallel
ctest --test-dir build/std-host -L '^std-api$' --output-on-failure
ctest --test-dir build/std-host -L '^std-header-optional$' --output-on-failure
python3 scripts/check_api_docs.py --examples --std-header optional --standard 20 --compiler g++-13 --require-all
```

The `std-api` label also runs the existing standard-library implementation
tests. Use `std-header-local` for just the public header folders. A
`std-header-<name>` label runs that header's own tests and the tests in
its matching implementation family (for example, `__algorithm`).

Use `--std-only` in place of `--std-header optional` for the complete
standard-side example registry. Set `--standard 17` to check the baseline.
The JSON report's `stage` field distinguishes executed examples, static
assertions, expected termination and lower-language header parsing.

With the CANN environment loaded, the following runs the `array` and `span`
header checks on a device. Select a fresh build directory when changing the
language mode or simulator setting. The formal simulator and hardware gates
use the same header checks alongside their existing cross-header workloads.

```bash
cmake -S test/support/std_runtime -B build/std-950-cxx17 \
  -DASC_STL_CXX_STANDARD=17 '-DASC_STL_STD_HEADERS=array;span' -DCMAKE_BUILD_TYPE=Release
cmake --build build/std-950-cxx17 --parallel
python3 scripts/run_hardware_case.py --timeout 120 --log build/std-950-cxx17/hardware.log -- \
  "$PWD/build/std-950-cxx17/asc_stl_std_runtime"
```

Select `-DASC_STL_STD_MODE=simd` to run the D-SIMD contracts for `bit`, `cmath`,
`compare` and `ctime`. Omitting the mode selects D-SIMT. For either mode,
omitting `ASC_STL_STD_HEADERS` runs every registered check for that mode. The
hardware and Cannsim gates compile D-SIMT in batches of up to eight headers.
Each batch has its own executable and log, with a separate result for each header.
The D-SIMT `bitset` check distributes shift counts across 32 lanes and
compares every output bit for every shift from zero through the width plus one.

To simulate one header with the same launcher and result checks, select it
when configuring the build and pass the executable to the simulator runner.

```bash
sim_build="$PWD/build/std-sim-cxx20"
cmake -S test/support/std_runtime -B "$sim_build" -DCMAKE_BUILD_TYPE=Release \
  -DASC_STL_CXX_STANDARD=20 -DASC_STL_STD_HEADERS=span -DASC_STL_TEST_CANNSIM=ON
cmake --build "$sim_build" --parallel
test/scripts/run_cannsim_test.sh "$(command -v cannsim)" "$sim_build/asc_stl_std_runtime" \
  Ascend950 "$sim_build/results" "$sim_build" ASC_STL_STD_RUNTIME_PASS
```

A header comprised of aliases, concepts or macro constants can be verified
with type, value and availability checks at compile time. A device kernel
that only includes the header establishes self-containment. Use result checks
for device operations whose observable behavior depends on runtime inputs.

## Executable documentation and supplemental release checks

The Host gate executes registered API examples in C++17 and C++20. CTest reports
core examples and optional-dependency examples separately. An unavailable optional
dependency produces a skipped test (exit 77), never a successful example. The
Device compile gate also compiles all registered D-SIMD and D-SIMT examples in
both language modes; these results are compilation evidence, not device execution.
Per-example JSON reports are written below the CMake build's `test/` directory.

The documentation structure gate verifies the example registry and compares C++
code in Chinese and English API pages, ignoring comments and whitespace outside
literals. Its coverage inventory lists every unregistered example page. Registration
coverage is not API semantic coverage; unregistered examples are not claimed as tested.

Supplemental release checks require a clean, committed product checkout and write
new logs, source identities and a summary to a fresh report directory. They supplement
the complete Host/Device/cannsim product gate; a selected stage is not a full release
verdict. Load the intended CANN environment before software Device checks or hardware
checks. Supply real optional dependencies, for example DLPack:

```bash
export ASC_STL_DOC_EXTRA_INCLUDE_DIRS=/path/to/dlpack/include
bash scripts/ci-release-check.sh --scope software --report-dir /path/to/new/software-report
```

The software scope runs all registered Host/Device documentation examples, the
C++17/C++20 memory-safety regression and user-workload correctness/performance checks.
It requires every selected example to complete: a missing dependency, failure, zero
applicable cases, or unexecuted case cannot produce a passing release summary.
`--jobs` controls concurrent example compilers; the Runtime scope remains serial.

This release wrapper intentionally differs from CTest's optional-test skip policy.
Exit 77 remains `NOT_APPLICABLE`; a nonzero exit with a `BLOCKED_ENVIRONMENT:`
diagnostic remains `BLOCKED_ENVIRONMENT`. Neither establishes completion of a selected
release stage. The wrapper stops at the first non-`PASS` result, records later stages
as `NOT_RUN`, sets `passed=false`, and exits 1. These preserved stage statuses distinguish
missing applicability or prerequisites from a product/test failure; the wrapper exit
code means the selected release evidence is incomplete, not necessarily a product defect.
An all-skipped run never passes. Hardware preflight must pass before Runtime execution.
To check an independent Host workload without the Device prerequisites, use
`--scope software --stage acceptance` in a separate report directory. This checks only
that selected stage and does not turn the incomplete run into a full release pass.

To avoid repeating an unchanged successful matrix, select the remaining supplements
and retain the independent product gate's detailed documentation reports:

```bash
bash scripts/ci-release-check.sh --scope software --stage memory --stage acceptance \
  --report-dir /path/to/new/supplement-report
```

Real CANN Runtime examples are deliberately excluded from cloud/software CI. On the
validated hardware host, run the separate scope under the hardware recorder and its
source/device checks:

```bash
bash scripts/ci-release-check.sh --scope hardware --report-dir /path/to/new/runtime-report
```

The hardware scope checks the compute-device mapping, then processes C++17 and C++20
Runtime examples in order. It stops on the first failure and records later stages as
`NOT_RUN`. Compile-only examples retain that classification. Hardware Runtime results,
full product gates and software supplements must refer to the same product revision;
one cannot replace another.
