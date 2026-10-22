# asc::std::remainderf

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

`asc::std::remainderf` computes the floating-point remainder corresponding to the nearest integer quotient; the applicable device-side scope is governed by the float and execution-location constraints on this page.

The available locations for this interface are Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float remainderf(
    float x, float y) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | Dividend of the IEEE remainder operation (dimensionless). |
| `y` | Input | Divisor of the IEEE remainder operation (dimensionless, must be non-zero; returns NaN when it is 0). |

## Return Value

The return type is determined per prototype (`float`). Returns x-n*y, where n is the integer nearest to x/y with halfway values rounded to even; the absolute value of the real result does not exceed |y|/2.

## Constraints

- Keeps the mathematical domains and pointer validity requirements in the parameter descriptions; available locations and language conditions are determined per prototype.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::remainderf(5.0F, 2.0F);
    return result == 1.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
