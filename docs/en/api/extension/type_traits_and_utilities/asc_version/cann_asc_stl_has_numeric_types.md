# CANN_ASC_STL_HAS_NUMERIC_TYPES

## Product Support

Requires C++17 and also supports C++20. The header is independently includable in Host, SIMD and SIMT compilation. Macro values are independent of the chip.

## Description

`<asc/version>`: Reports delivery of the baseline extended numeric types and scalar conversions described in [Issue #85](https://gitcode.com/cann/asc-stl/issues/85). The current value is `1`.

## Declaration

```cpp
#define CANN_ASC_STL_HAS_NUMERIC_TYPES 1
```

## Constraints

The macro is always defined as `0` or `1`. A value of `1` requires the complete baseline API and its applicable acceptance; otherwise it is `0`. Test its value with `#if`. Consult the module for operation-specific chip, type, address-space and execution-mode requirements.

## Example

```cpp
#include <asc/version>

#if CANN_ASC_STL_HAS_NUMERIC_TYPES
constexpr bool use_extension = true;
#else
constexpr bool use_extension = false;
#endif
static_assert(use_extension == (CANN_ASC_STL_HAS_NUMERIC_TYPES == 1));
```

## Related APIs

- [<asc/version>](asc_version.md)
- [Maintenance and delivery records](../../../../guide/product_version.md)
