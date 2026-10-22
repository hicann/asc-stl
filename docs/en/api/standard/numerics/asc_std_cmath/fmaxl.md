# asc::std::fmaxl

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

`asc::std::fmaxl` returns the larger of two long double arguments; when either argument is NaN, the other argument is returned.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double fmaxl(long double x, long double y) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | First operand (dimensionless) participating in the maximum computation; when either operand is NaN, the other operand is returned. |
| `y` | Input | First operand (dimensionless) participating in the maximum computation; when either operand is NaN, the other operand is returned. |

## Return Value

The return type is determined per prototype (`long double`). Returns the larger of the two inputs; when only one input is NaN, the other non-NaN value is returned.

## Constraints

- Standard integer inputs on Host are promoted to double; the device-side integer promotion branch is rejected by a static assertion. Instantiations of float, double, long double, and extended types must also be supported by the target compilation mode.

- NaN-aware: returns NaN only when both arguments are NaN; never throws.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::fmaxl(2.0L, 5.0L);
    return result == 5.0L;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
