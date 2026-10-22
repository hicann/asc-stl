# asc::std::ldexpl

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

`asc::std::ldexpl` is provided by `<asc/std/cmath>`; Host long double value*2^e, the suffix-l alias.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double ldexpl(long double value, int exponent) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Floating-point value to be scaled by an integral power of 2 (dimensionless). |
| `exponent` | Input | Integral exponent with base 2 (int, dimensionless); the result is value * 2^exponent. |

## Return Value

The return type is determined per prototype (`long double`). Returns the input multiplied by 2 raised to the exponent.

## Constraints

- Host long double value*2^e, suffix-l alias.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    return asc::std::ldexpl(0.5L, 4) == 8.0L;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
