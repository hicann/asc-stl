# asc::std::fmax

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

`asc::std::fmax` selects the larger argument according to the floating-point maximum rules; on the device side, the applicable scope is subject to the float and execution-location constraints on this page.

For availability of the different types, see the individual prototypes and the constraints.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__is_extended_arithmetic_v<Tp>, int> = 0>
[[nodiscard]] constexpr conditional_t<is_integral_v<Tp>, double, Tp> fmax(Tp x, Tp y) noexcept;
}
```

Available locations: Host, AI Core SIMD programming, AI Core SIMT programming.

### Prototype 2

```cpp
namespace asc::std {
template <class Tp, class Up,
    ::asc::std::enable_if_t<::asc::std::is_floating_point_v<Tp>&& ::asc::std::is_floating_point_v<Up>, int> = 0>
[[nodiscard]] constexpr auto fmax(Tp x, Up y) noexcept;
}
```

Available locations: Host, AI Core SIMD programming, AI Core SIMT programming.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Tp` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. The branch where a standard integer type is promoted to double is for Host only; the device side does not provide that integer promotion. |
| `Up` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. The branch where a standard integer type is promoted to double is for Host only; the device side does not provide that integer promotion. |

The unnamed default int template parameter is used for overload selection; the caller does not need to provide it.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | First operand (dimensionless) participating in the maximum computation; when either operand is NaN, the other operand is returned. |
| `y` | Input | Second operand (dimensionless) participating in the maximum computation; when either operand is NaN, the other operand is returned. |

## Return Value

The return type is determined per prototype (`conditional_t<is_integral_v<Tp>, double, Tp>`, `auto`). Returns the larger of the two inputs; when only one input is NaN, the other non-NaN value is returned.

## Constraints

- Standard integer inputs on Host are promoted to double; the device-side integer promotion branch is rejected by a static assertion. Instantiations of float, double, long double, and extended types must also be supported by the target compilation mode.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::fmax(2.0F, 5.0F);
    return result == 5.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
