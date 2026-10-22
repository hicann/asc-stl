# asc::std::hypot

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

`asc::std::hypot` computes the square root of the sum of squares; on the device side, the applicable scope is subject to the float and execution-location constraints on this page.

This interface is available on Host and in AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float hypot(
    float x, float y) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

### Prototype 2

```cpp
namespace asc::std {
[[nodiscard]] constexpr float hypot(
    float x, float y, float z) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

### Prototype 3

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
[[nodiscard]] constexpr Tp hypot(
    Tp x, Tp y) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time. Extended floating-point templates participate only when the corresponding type is available; numeric calls with half, bfloat16, and the supported FP8 types are for AI Core SIMT programming.

### Prototype 4

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
[[nodiscard]] constexpr Tp hypot(
    Tp x, Tp y, Tp z) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time. Extended floating-point templates participate only when the corresponding type is available; numeric calls with half, bfloat16, and the supported FP8 types are for AI Core SIMT programming.

### Prototype 5

```cpp
namespace asc::std {
[[nodiscard]] constexpr double hypot(double x, double y) noexcept;
}
```

Available locations: Host.

### Prototype 6

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double hypot(long double x, long double y) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

### Prototype 7

```cpp
namespace asc::std {
template <class Tp, class Up, ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up>, int> = 0>
[[nodiscard]] constexpr __promote_t<Tp, Up> hypot(Tp x, Up y) noexcept;
}
```

Available locations: Host.

### Prototype 8

```cpp
namespace asc::std {
[[nodiscard]] constexpr double hypot(double x, double y, double z) noexcept;
}
```

Available locations: Host.

### Prototype 9

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double hypot(
    long double x, long double y, long double z) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

### Prototype 10

```cpp
namespace asc::std {
template <class Tp, class Up, class Vp,
    ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up> && is_arithmetic_v<Vp>, int> = 0>
[[nodiscard]] constexpr __promote_t<Tp, Up, Vp> hypot(Tp x, Up y, Vp z) noexcept;
}
```

Available locations: Host.

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
| `x` | Input | Edge length (dimensionless) in the x direction for computing the three-dimensional hypotenuse sqrt(x^2 + y^2 + z^2). |
| `y` | Input | Edge length (dimensionless) in the y direction for computing the three-dimensional hypotenuse sqrt(x^2 + y^2 + z^2). |
| `z` | Input | Edge length (dimensionless) in the z direction for computing the three-dimensional hypotenuse sqrt(x^2 + y^2 + z^2). |

## Return Value

The return type is determined per prototype (`float`, `Tp`, `double`, `long double`, `__promote_t<Tp, Up>`, `__promote_t<Tp, Up, Vp>`). Returns the square root of the sum of the squares of the inputs.

## Constraints

- Whether an extended type can be instantiated depends on target type support; ordinary transcendental functions are computed in float and converted back to the original format, and the rules for integer rounding and adjacent values are given in the dedicated notes on this page.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::hypot(3.0F, 4.0F);
    return result == 5.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
