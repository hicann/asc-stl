# asc::std::fabsf

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

`asc::std::fabsf` returns the absolute value of the floating-point argument; on the device side, the applicable scope is subject to the float and execution-location constraints on this page.

This interface is available on Host and in AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float fabsf(float x) noexcept;
}
```

Available locations: Host, AI Core SIMD programming, AI Core SIMT programming.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | Input value (dimensionless) whose floating-point absolute value is to be computed. |

## Return Value

The return type is determined per prototype (`float`). Returns the absolute value with the sign bit cleared; float, double, and long double keep their original type, and Host integer inputs return double.

## Constraints

- Standard integer inputs on Host are promoted to double; the device-side integer promotion branch is rejected by a static assertion. Instantiations of float, double, long double, and extended types must also be supported by the target compilation mode.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::fabsf(-2.0F);
    return result == 2.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
