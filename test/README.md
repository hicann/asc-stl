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
