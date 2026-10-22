# asc::std::nextafterf

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

`asc::std::nextafterf` returns the next representable floating-point value in the direction of the target value; the applicable device-side scope is governed by the float and execution-location constraints on this page.

The available locations for this interface are Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float nextafterf(
    float x, float y) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | Starting floating-point value for finding the adjacent representable value (dimensionless). |
| `y` | Input | Target floating-point value indicating the direction of movement (dimensionless); returns x when x equals y. |

## Return Value

The return type is determined per prototype (`float`). Returns the adjacent value in the original result format toward the target direction; returns the target value when the inputs are equal, preserving the sign of the target zero.

## Constraints

- When the two values are equal, returns the target direction argument converted to the result type; +0 and -0 compare equal, in which case the sign of the target zero is preserved.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto value = asc::std::nextafterf(1.0F, 2.0F);
    return value > 1.0F && value < 2.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
