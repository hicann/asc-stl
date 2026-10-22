# asc::std::scalblnl

## Product Support

<!-- npu="950" id1 -->
- Ascend 950PR&950DT series products: Supported
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3 series products: Not supported
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2 series products: Not supported
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2 inference products: Not supported
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas inference series products AI Core: Not supported
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas inference series products Vector Core: Not supported
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas training series products: Not supported
<!-- end id7 -->

## Description

Header: `<asc/std/cmath>`.

`asc::std::scalblnl` is provided by `<asc/std/cmath>`; the Host long double overload is the same as scalbn but with a long exponent, with the suffix l as an alias.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double scalblnl(long double value, long exponent) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Floating-point value (dimensionless) to be scaled by an integer power of FLT_RADIX (which is 2). |
| `exponent` | Input | Integer exponent (long, dimensionless) with base 2 (FLT_RADIX); the result is value * 2^exponent. |

## Return Value

The return type is determined per prototype (`long double`). Returns the input multiplied by the floating-point radix raised to the power exponent, with the exponent passed as long.

## Constraints

- The Host long double overload is the same as scalbn but with a long exponent, with the suffix l as an alias.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    return asc::std::scalblnl(0.5L, 4) == 8.0L;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
