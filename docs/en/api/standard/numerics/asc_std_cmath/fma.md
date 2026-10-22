# asc::std::fma

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

`asc::std::fma` computes the multiply-add result with a single rounding; on the device side, the applicable scope is subject to the float and execution-location constraints on this page.

This interface is available on Host and in AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float fma(
    float x, float y, float z) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

### Prototype 2

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
[[nodiscard]] constexpr Tp fma(
    Tp x, Tp y, Tp z) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time. Extended floating-point templates participate only when the corresponding type is available; numeric calls with half, bfloat16, and the supported FP8 types are for AI Core SIMT programming.

### Prototype 3

```cpp
namespace asc::std {
[[nodiscard]] constexpr double fma(double x, double y, double z) noexcept;
}
```

Available locations: Host.

### Prototype 4

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double fma(
    long double x, long double y, long double z) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

### Prototype 5

```cpp
namespace asc::std {
template <class Tp, class Up, class Vp,
    ::asc::std::enable_if_t<is_integral_v<Tp> && is_integral_v<Up> && is_integral_v<Vp>, int> = 0>
[[nodiscard]] constexpr float fma(Tp x, Up y, Vp z) noexcept;
}
```

Available locations: Host.

### Prototype 6

```cpp
namespace asc::std {
template <class Tp, class Up, class Vp,
    ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up> && is_arithmetic_v<Vp> &&
            (is_same_v<Tp, double> || is_same_v<Up, double> || is_same_v<Vp, double> || is_same_v<Tp, long double> ||
                is_same_v<Up, long double> || is_same_v<Vp, long double>),
        int> = 0>
[[nodiscard]] constexpr __promote_t<Tp, Up, Vp> fma(Tp x, Up y, Vp z) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Tp` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. |
| `Up` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. |
| `Vp` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. |

The unnamed default int template parameter is used for overload selection; the caller does not need to provide it.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | First factor of the product x * y in the fused multiply-add (dimensionless). |
| `y` | Input | Second factor of the product x * y in the fused multiply-add (dimensionless). |
| `z` | Input | Addend combined with the product in the fused multiply-add (dimensionless); the whole operation is rounded only once. |

## Return Value

The return type is determined per prototype (`float`, `Tp`, `double`, `long double`, `__promote_t<Tp, Up, Vp>`). Returns the product plus the third argument, with only a single rounding.

## Constraints

- On Host, all-integer templates return float per the existing interface; mixed templates containing double or long double return the promoted type of the prototype, and it must not be assumed that all integer math functions return double.

- Whether an extended type can be instantiated depends on target type support; ordinary transcendental functions are computed in float and converted back to the original format, and the rules for integer rounding and adjacent values are given in the dedicated notes on this page.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    return asc::std::fma(2.0F, 3.0F, 1.0F) == 7.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
