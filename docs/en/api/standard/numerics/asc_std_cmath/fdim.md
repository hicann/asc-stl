# asc::std::fdim

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

`asc::std::fdim` returns the positive difference of the two arguments; on the device side, the applicable scope is subject to the float and execution-location constraints on this page.

This interface is available on Host and in AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float fdim(
    float x, float y) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

### Prototype 2

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
[[nodiscard]] constexpr Tp fdim(
    Tp x, Tp y) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time. Extended floating-point templates participate only when the corresponding type is available; numeric calls with half, bfloat16, and the supported FP8 types are for AI Core SIMT programming.

### Prototype 3

```cpp
namespace asc::std {
[[nodiscard]] constexpr double fdim(double x, double y) noexcept;
}
```

Available locations: Host.

### Prototype 4

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double fdim(long double x, long double y) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

### Prototype 5

```cpp
namespace asc::std {
template <class Tp, class Up, ::asc::std::enable_if_t<is_arithmetic_v<Tp> && is_arithmetic_v<Up>, int> = 0>
[[nodiscard]] constexpr __promote_t<Tp, Up> fdim(Tp x, Up y) noexcept;
}
```

Available locations: Host.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Tp` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. |
| `Up` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. |

The unnamed default int template parameter is used for overload selection; the caller does not need to provide it.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | Minuend of the positive difference operation (dimensionless). |
| `y` | Input | Subtrahend of the positive difference operation (dimensionless); the result is +0 when x is not greater than y, and NaN when either operand is NaN. |

## Return Value

The return type is determined per prototype (`float`, `Tp`, `double`, `long double`, `__promote_t<Tp, Up>`). Returns x-y when x is greater than y, otherwise positive zero.

## Constraints

- Whether an extended type can be instantiated depends on target type support; ordinary transcendental functions are computed in float and converted back to the original format, and the rules for integer rounding and adjacent values are given in the dedicated notes on this page.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::fdim(5.0F, 2.0F);
    return result == 3.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
