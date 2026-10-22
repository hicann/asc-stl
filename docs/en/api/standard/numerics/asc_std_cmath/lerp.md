# asc::std::lerp

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

`asc::std::lerp` computes the linear interpolation between two values; the applicable device-side scope is governed by the float and execution-location constraints on this page.

The available locations for this interface are Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] float lerp(float a, float b, float t) noexcept;
}
```

Available locations: Host, AI Core SIMT programming.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `a` | Input | Starting value of the linear interpolation (dimensionless). |
| `b` | Input | End value of the linear interpolation (dimensionless). |
| `t` | Input | Interpolation weight (dimensionless); mathematically a + t * (b - a), and the implementation avoids overflow of the difference of large values with opposite signs within a finite interval; returns b when t = 1, and values outside [0, 1] are allowed for extrapolation. |

## Return Value

The return type is determined per prototype (`float`). Returns the linear interpolation; finite endpoints with a [0, 1] weight produce a finite result and preserve the endpoints and monotonicity.

## Constraints

- When a and b are finite and t is within [0, 1], returns a finite result that preserves the endpoints and monotonicity; extrapolated results may still overflow.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    return asc::std::lerp(-3.0e38F, 3.0e38F, 0.5F) == 0.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
