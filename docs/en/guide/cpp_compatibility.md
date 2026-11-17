# Language modes and compatibility

[简体中文](../../zh/guide/cpp_compatibility.md)

ASC-STL requires C++17 and maintains C++17 and C++20 modes. The ISO revision that
introduced an interface, the compiler version, Host standard-library version and
CANN package version are independent conditions. Selected newer library features
are backported where ordinary C++17 templates can express them; API pages define
the delivered overloads and execution locations.

## Type and expression predicates

Public predicate names in `<asc/std/concepts>`, `<asc/std/iterator>` and
`<asc/std/ranges>` are `inline constexpr bool` variable templates in C++17 and
native concepts in configurations that support concepts in C++20 or later.
Query `CANN_ASC_STL_HAS_NATIVE_CONCEPTS` for the actual form.
`static_assert(asc::std::integral<int>)` works in both modes; the C++17 Boolean
result can also control `enable_if`.

Constrained template parameters, `requires`, concept subsumption, `char8_t`,
three-way comparison syntax and multidimensional subscripting require their own
language and compiler support. The C++17 Boolean vocabulary does not provide
those language mechanisms.

## Interface availability, execution and constant evaluation

Check these properties separately:

- **Language mode:** selected `to_array`, contiguous-range span constructors,
  expected, inplace_vector and Philox facilities have C++17 implementations.
  Originating in a newer ISO standard does not automatically require its mode.
- **Execution location:** Host, AI Core SIMD and AI Core SIMT have different
  system-library, Runtime and address-space requirements. Host `<cuchar>` must
  actually provide the relevant character-conversion functions.
- **Constant evaluation:** the whole expression, object lifetimes and element
  operations must satisfy the selected language's rules. A runtime operation or
  a `constexpr` declaration alone does not guarantee a valid `static_assert`.

`format_to_n_result` is available as an aggregate in C++17. Reusing private
rendering code in C++17 does not expose a new runtime-formatting API; public typed
formatting still requires C++20 and immediate `consteval` checking.
`destroying_delete_t` and its object are vocabulary tags in C++17 and do not enable
the compiler's destroying-delete mechanism. The two C compatibility macros from
`cstdalign` and `cstdbool` are supplied by ASC-STL only in C++17.

Some type rules deliberately differ by language mode, including parts of
`common_type` fallback and insert-iterator `difference_type`. Some C++20 objects
use `no_unique_address`. Use consistent modes and configuration across translation
units that exchange such objects. View cache/storage corrections can also change
concrete object layouts; recompile dependent components after updating. These
types do not have a byte-level stable ABI guarantee.

Interfaces originating in C++23 or C++26 are maintained as documented subsets;
their presence does not promise complete support for either language or library
revision.

## Query ASC-STL capabilities

After including `<asc/std/version>`, query the `CANN_ASC_STL_HAS_*` macros. Every
query is defined as 0 or 1. A value of 1 still requires each API's overload, type
and execution constraints. These macros describe ASC-STL, not Host `std`.

| Macro suffix after `CANN_ASC_STL_HAS_` | Capability |
| --- | --- |
| `SOURCE_LOCATION`, `UNREACHABLE`, `TYPE_IDENTITY`, `ENDIAN` | Corresponding vocabulary facilities |
| `IS_CONSTANT_EVALUATED` | Reliable compiler distinction between constant and runtime evaluation |
| `CONCEPT_PREDICATES`, `NATIVE_CONCEPTS` | Boolean predicate vocabulary and native concept form, respectively |
| `SPAN`, `TO_ARRAY`, `MDSPAN`, `SUBMDSPAN` | Listed view, array conversion and slicing interfaces |
| `EXPECTED`, `OPTIONAL_REFERENCE`, `INPLACE_VECTOR` | Listed interfaces and nonthrowing domains |
| `PHILOX`, `ALLOCATE_AT_LEAST` | Counter-based engine and allocator detection/fallback |
| `FORMAT_TO_N_RESULT`, `FORMAT` | Result aggregate and typed formatting with immediate validation |

A Host example can branch on the ASC-STL capability:

```cpp
#include <asc/std/version>
#include <asc/std/array>

#if CANN_ASC_STL_HAS_TO_ARRAY
constexpr int input[2] = {2, 4};
constexpr auto values = asc::std::to_array(input);
static_assert(values[1] == 4);
#endif
```

## Migrate old feature checks

Use CANN_ASC_STL_LIB_x >= YYYYMML for complete standard features. Partial features
have no revision macro. See the [feature inventory](std_feature_test.md) for the
mapping, requirements and conditions; HAS queries retain their subset meaning.

```cpp
#include <asc/std/version>
#include <asc/std/array>

#if defined(CANN_ASC_STL_LIB_to_array) && CANN_ASC_STL_LIB_to_array >= 201907L
constexpr auto values = asc::std::to_array({2, 4});
static_assert(values[1] == 4);
#endif
```

CANN_ASC_STL_ENABLE_LEGACY_STD_FEATURE_MACROS is now inert. Migrate old ASC checks
to CANN_ASC_STL_LIB_source_location / CANN_ASC_STL_LIB_unreachable, or retain HAS
queries for the original subsets. Host __cpp_lib_* describes Host std only.

Host C++20 source_location::current is consteval when immediate functions are
supported, so explicit arguments must satisfy constant-expression requirements.
Its C++17/Device constexpr subset remains. unreachable is explicitly noexcept.

## Host system libraries

The duplicate-key lookup, complex frequency-response and padded tensor-view
usage paths have been checked in C++17 with GCC 9.5 as well as GCC 13. This does
not establish support for every header on every GCC release. Type identity checks
in these dependencies use ASC-STL traits rather than requiring the newer
`__is_same` builtin. The trivial-destructor trait uses GCC's legacy
`__has_trivial_destructor` when builtin feature detection is unavailable.
On a compiler without `__builtin_bit_cast`, floating-point codecs remain usable
at runtime, but conversions requiring that operation are not constant expressions.
Check whether `CANN_ASC_STL_LIB_bit_cast` is defined before requiring constexpr
bit casts. Pair-like constructor constraints reject non-tuple-like sources before
attempting element access; this also permits reference tuples used by slicing.

Custom lookup for `ranges::iter_swap` also supports GCC 9/11 Host builds.
An iterator may provide a two-argument `iter_swap` as a hidden friend or in its
associated namespace. A valid customization remains usable when dereferencing
the iterator returns a read-only reference. Without such a customization,
availability still follows element swapping or the move-exchange fallback.

The C++20 `<asc/std/cuchar>` functions `c8rtomb` and `mbrtoc8` must be exported by
the actual system `<cuchar>`. On GNU/Linux this normally needs glibc 2.36 or later
and a libstdc++ built with that capability. Ubuntu 24.04 with GCC 13/glibc 2.39
provides the tested combination. Updating only the compiler is insufficient;
compile, link and run in the same environment. Do not inject another glibc globally
into a CANN installation. See also [known device limitations](known_limitations.md).

## C++17/C++20 simulator regressions

`bash scripts/ci-cannsim-check.sh` builds and runs the C++17 and C++20 suites in
Release mode. The range-algorithm case assigns eight input lengths to disjoint
data slices in eight blocks of one launch; every length still checks all results
in both GM and UB. The W13/W14 SIMT case assigns six independent single-thread check groups
to six blocks in one launch, then aggregates their results in a separate
four-thread synchronization launch to reduce repeated simulator dispatch.

The default per-case limit remains 600 seconds, and a timeout is a failure.
Compare regression timings with the same simulator, toolchain and resources;
a passing server run does not establish success in another CI environment.
