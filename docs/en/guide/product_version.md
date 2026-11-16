# Product version and extension API delivery

`<asc/version>` provides the release-date macro `CANN_ASC_STL`, three extension
delivery flags, and the contents of `<asc/std/version>`. Applications can check
a minimum release date and select code for delivered extension APIs. The header
is independently includable in Host, SIMD and SIMT compilation with C++17 or C++20.

| Information | Meaning |
| --- | --- |
| `CANN_ASC_STL` | Fixed Gregorian release date, encoded as decimal `YYYYMMDD`; currently `20261023`. Integer comparison preserves date order. |
| `CANN_ASC_STL_HAS_*` | Whether the package delivers the complete registered baseline API and its applicable acceptance; always `0` or `1`. |
| `CANN_ASC_STL_LIB_*` | A standard-layer feature revision, maintained according to its language and compiler conditions. |

`include/asc/__version/product.h` owns the four product macros. Their values are
identical across language and execution modes for the same package. The caller's
`__DATE__` and compilation time do not affect them. Dates must be valid Gregorian
dates with years from 1000 to 9999. Release commits distinguish same-day snapshots.

Standard features use the separate `CANN_ASC_STL_LIB_*` prefix. For example,
`CANN_ASC_STL_LIB_type_identity` has the standard feature revision `201806L`,
maintained separately from the product release date. Host applications can include
both `<version>` and `<asc/version>`; the host's `__cpp_lib_*` retain their meanings.

## Example

```cpp
#include <asc/version>

// 20260101 is an illustrative minimum release date.
#if CANN_ASC_STL < 20260101
#error "ASC-STL release 20260101 or newer is required"
#endif

#if CANN_ASC_STL_HAS_PIPELINE
constexpr bool select_pipeline_code = true;
#else
constexpr bool select_pipeline_code = false;
#endif
static_assert(select_pipeline_code == (CANN_ASC_STL_HAS_PIPELINE == 1));
```

Test flag values with `#if`. A zero selects an application fallback. A value of one
allows selecting the delivered API subject to its execution, chip, type,
address-space and operation support conditions. Host code can read the flags;
Device operations follow their supported Device compilation modes.

## Current delivery records

[extension_features.json](../../release/extension_features.json) records the macro
values and their delivery evidence. All three flags are currently zero because
their baseline APIs and applicable acceptance remain incomplete. Existing headers,
declarations and partial older implementations alone do not establish delivery.

| Macro | Baseline API and module Issue | Value |
| --- | --- | --- |
| `CANN_ASC_STL_HAS_PIPELINE` | [#105](https://gitcode.com/cann/asc-stl/issues/105): SIMT thread-group pipelines | `0` |
| `CANN_ASC_STL_HAS_NUMERIC_TYPES` | [#85](https://gitcode.com/cann/asc-stl/issues/85): extended numeric types and scalar conversions | `0` |
| `CANN_ASC_STL_HAS_CACHE` | [#99](https://gitcode.com/cann/asc-stl/issues/99): cache control | `0` |

This change replaces the component version macros and the device-policy and
collectives flags with the date macro and three delivery flags above. The pipeline
flag is registered against the SIMT baseline API in #105.

## Module delivery and release maintenance

The module Issue and API documentation define baseline signatures, behavior,
support conditions and applicable acceptance. On first delivery, freeze the API
description under `docs/release/` and register its path and SHA256. Record later
API additions and their first delivery dates in the module documentation.

Update the private macros, registry, API documentation, acceptance evidence and
release notes together. Setting a flag to one requires these registry fields:

| Field | Requirement |
| --- | --- |
| `issue` | The module Issue listed above. |
| `baseline` | Frozen API description with `path` and `sha256`, relative to `docs/release/`. |
| `implementation_commit` | Full implementation commit identifier. |
| `acceptance` | Acceptance JSON with `path` and `sha256`, relative to `docs/release/`. |
| `first_release_date` | First delivery date of this baseline, no later than the package date. |

The acceptance JSON identifies the same `implementation_commit` and lists
applicable `cases`, each with a unique `name`, `status: "PASS"` and `returncode: 0`.
Records should reference actual commands, environment and logs; module delivery
verifies that they cover the baseline API. Incomplete or skipped-only acceptance
keeps the flag at zero with an explanation in `reason`.

Run the release check on a fixed, committed source tree:

```bash
scripts/ci-release-check.sh --scope software --stage version --report-dir <new-report-directory>
```

This check also precedes every supplemental release stage and is registered in
Quick's static checks. It checks calendar dates, flag ranges, registry agreement,
module Issues, evidence and file digests. Invalid or incomplete records fail and
stop the release check. Functional acceptance follows the module API description.

The release process fixes the date and updates both `CANN_ASC_STL` and the registry
`release_date`. CMake installation copies the registry and frozen records to
`share/asc_stl/docs/release/`, preserving the `docs/zh/guide/` and `docs/en/guide/`
paths for this guide and its links.
