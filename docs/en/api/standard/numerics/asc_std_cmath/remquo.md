# asc::std::remquo

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

`asc::std::remquo` computes both the floating-point remainder and the low-order bits of the quotient; the applicable device-side scope is governed by the float and execution-location constraints on this page.

The available locations for this interface are Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float remquo(
    float x, float y, int* quotient) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

### Prototype 2

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
[[nodiscard]] constexpr Tp remquo(
    Tp x, Tp y, int* quotient) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time. Extended floating-point templates participate only when the corresponding type is available; numeric calls with half, bfloat16, and the supported FP8 types are for AI Core SIMT programming.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Tp` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. |

The unnamed default int template parameter is used for overload selection; the caller does not need to provide it.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | Dividend of the IEEE remainder operation (dimensionless). |
| `y` | Input | Divisor of the IEEE remainder operation (dimensionless, must be non-zero; returns NaN when it is 0). |
| `quotient` | Output | Output pointer: writes the signed low-order bits of the quotient; at least 3 low-order bits are preserved, the exact number is determined by the backend, and the sign follows the quotient; the storage is provided by the caller. |

## Return Value

The return type is determined per prototype (`float`, `Tp`). Returns the IEEE remainder and writes the sign of the quotient and at least 3 low-order bits through quotient.

## Constraints

- The caller relies only on the sign of the quotient and at least 3 low-order bits, and must not assume the returned quotient information has exactly 3 bits. quotient must point to a valid and writable int object.

- Whether an extended type can be instantiated depends on target type support; ordinary transcendental functions are computed in float and converted back to the original format, and the rules for integer rounding and adjacent values are given in the dedicated notes on this page.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    int quotient = 0;
    const auto remainder = asc::std::remquo(5.0F, 2.0F, &quotient);
    return remainder == 1.0F && quotient > 0 && (quotient & 7) == 2;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
