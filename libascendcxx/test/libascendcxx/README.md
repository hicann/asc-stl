# libascendcxx test gates

This directory is the CMake and CTest entry point for ASC-STL's G0-G7 gates.
The current reference slices cover the compile-time-only
`asc/std/__type_traits/is_literal_type.h` and the Device runtime headers
`asc/std/__algorithm/clamp.h`, `asc/std/__algorithm/comp.h`, and
`asc/std/__bit/blsr.h`. Host, real AscendC Device compilation, and cannsim
Runtime results remain separate evidence.

## Canonical layout

```text
cases/<module>/<case-id>/
  host.pass.cpp
  device.compile.cpp
  support/...
  cannsim/
    kernel.cpp
    launcher.cpp
    launcher.h
    main.cpp
    kernel_spec.json
infrastructure/
  header/header_host.cpp.in
  header/header_device.cpp.in
  cannsim/smoke/...
metadata/
scripts/
  validate_metadata.py
  run_cannsim_test.sh
  test_cannsim_runner_failures.sh
```

The target header determines the case path. For example,
`asc/std/__algorithm/clamp.h` maps to `cases/__algorithm/clamp/`. Host semantics,
Device semantic compilation, support files, and an applicable cannsim bundle for
that header stay in the same case. Cases must not contain `CMakeLists.txt`, CANN
modules, runners, or environment scripts.

`metadata/headers.json` is authoritative for applicability and CTest mappings.
The validator derives the case path and full CTest suffix from each metadata
`target`, requires every applicable fixed-name source, rejects evidence for an
inapplicable gate, and rejects canonical case files that have no metadata
mapping. CMake registers only metadata-applicable cases; a file's accidental
presence is never a pass.

All build products, generated self-containment TUs, CTest state, cannsim logs,
and reports stay below an out-of-source build directory. No output belongs in
`cases/`, `infrastructure/`, `metadata/`, or `scripts/`.

## Gate layout

| Gate | Implementation | CTest label | `is_literal_type` | `clamp` |
| --- | --- | --- | --- | --- |
| G0 mapping | `metadata/headers.json` and validator | `metadata` | Required | Required |
| G1 repository rules | metadata/static scan and style scripts | `static-rules` | Required | Required |
| G2 self-contained headers | generated Host and AscendC TUs | `header-host`, `header-device` | Required | Required |
| G3 Host semantics | `cases/<module>/<case-id>/host.pass.cpp` | `semantic-host` | Required | Required |
| G4 Device compile | `cases/<module>/<case-id>/device.compile.cpp` | `device-compile` | Required | Required |
| G5 cannsim semantics | shared smoke plus applicable case runtime UTs | `cannsim-smoke`, `cannsim-runtime` | Not applicable | Required |
| G6 aggregation/consumer | approved public APIs only | `public-header`, `external-consumer` | Not applicable | Not applicable |
| G7 regression | stable affected and nightly labels | `affected-regression`, `nightly` | Required | Required |

CTest names include the full case-relative path:

```text
header.host.__algorithm.clamp
semantic.host.__algorithm.clamp
header.device.__algorithm.clamp
semantic.device.__algorithm.clamp
semantic.cannsim.__algorithm.clamp
```

The status vocabulary is `passed`, `failed`, `blocked_environment`,
`not_applicable`, `not_implemented`, and `not_run`. A missing applicable test is
never a pass.

## Runner environment

The Host gate requires:

- Bash and Git;
- Python 3.9 or newer;
- CMake 3.20 or newer with CTest;
- a Host compiler with C++17 support;
- clang-format 14 or newer;
- cpplint.

The Host entry point does not require a project-specific conda environment.
CI images should pin tool versions to keep local and online results consistent.

Device and cannsim scripts share `scripts/cann-env.sh`. For CI, the Runner
should explicitly set `ASC_STL_CANN_ENV_SCRIPT` to the installed CANN
`set_env.sh`. Local fallback discovery may use `/usr/local/Ascend/cann/set_env.sh`
or an already initialized `ASCEND_HOME_PATH`.

The validated baseline is CANN Toolkit 9.0.0 x86_64, compile SoC
`Ascend950PR_9599`, and simulator SoC `Ascend950`. The Device Runner must provide
the official `ascendc.cmake` and AscendC compiler. The cannsim Runner must
additionally provide an executable cannsim. Missing environment requirements
must be reported as an environment block rather than silently skipped.

This project has no real-device runtime gate. Device compile and cannsim remain
distinct formal evidence and cannot replace one another.

## Gate commands

Host gate:

```bash
bash scripts/ci-quick-check.sh
```

Device compile gate:

```bash
ASC_STL_CANN_ENV_SCRIPT=<CANN-install-root>/set_env.sh \
ASC_STL_TARGET_SOC=Ascend950PR_9599 \
bash scripts/ci-device-compile-check.sh
```

Cannsim Runtime gate:

```bash
ASC_STL_CANN_ENV_SCRIPT=<CANN-install-root>/set_env.sh \
ASC_STL_TARGET_SOC=Ascend950PR_9599 \
ASC_STL_CANNSIM_SOC=Ascend950 \
ASC_STL_CANNSIM_EXECUTABLE=<cannsim-executable> \
bash scripts/ci-cannsim-check.sh
```

`<CANN-install-root>` and `<cannsim-executable>` are Runner-provided values and
must not be replaced by developer-specific absolute paths in repository files.

The Device build fixes `RUN_MODE=npu` and uses the official
`ascendc_library(... OBJECT ...)` flow. The cannsim build also remains
`RUN_MODE=npu`; CTest then runs `cannsim record`. Host macros and CMake
`RUN_MODE=sim` are not substitutes for formal Device compilation.

`cannsim.smoke` is shared infrastructure and sets up the
`asc_stl_cannsim_ready` fixture. It exercises the simulator chain but is not
semantic completion evidence for a header. Each applicable runtime case has a
separate `semantic.cannsim.<full-case-path>` test, an independent all-element
golden, mismatch rejection, and a unique PASS marker. In particular,
`device.compile.cpp` and `cannsim/kernel.cpp` prove different properties.

## Add the next header

1. Add the header and complete dependency closure under
   `libascendcxx/include/asc/std`.
2. Register provenance, dependencies, APIs, applicability, and complete
   path-based CTest names in `metadata/headers.json`.
3. Put Host, Device compile, support, and applicable cannsim assets in the one
   header-derived `cases/<module>/<case-id>/` bundle, using the fixed filenames.
4. Keep expected Host and cannsim golden values independent of the tested API.
5. Add public aggregation and installed-consumer coverage only after API
   approval.
6. Run all applicable Host, Device compile, cannsim, regression, and style
   gates. CI results are retained by the PR checks and logs; successful checks
   do not rewrite repository metadata.

When ASC_AGENT delivers a validated case, copy the deterministic canonical case
bundle and re-run ASC-STL's own formal gates. Do not regenerate equivalent test
semantics during delivery.
