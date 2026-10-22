# asc::std::atan2f

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

`asc::std::atan2f` computes the quadrant-aware arc tangent from two coordinates; on the device side, the applicable scope is subject to the float and execution-location constraints on this page.

This interface is available on Host and in AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float atan2f(
    float y, float x) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `y` | Input | Ordinate value (dimensionless) used to compute the quadrant-aware arc tangent atan2(y, x). |
| `x` | Input | Abscissa value (dimensionless) used to compute the quadrant-aware arc tangent atan2(y, x); the quadrant of the returned angle is determined jointly by the signs of x and y. |

## Return Value

The return type is determined per prototype (`float`). Returns the arc tangent whose quadrant is determined from the signs of the two inputs, in radians.

## Constraints

- Provides the float overload and the standard *f aliases.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::atan2f(0.0F, 1.0F);
    return result == 0.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
