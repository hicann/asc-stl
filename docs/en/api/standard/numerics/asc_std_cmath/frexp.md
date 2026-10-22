# asc::std::frexp

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

`asc::std::frexp` decomposes a floating-point value into a significand and a binary exponent; on the device side, the applicable scope is subject to the float and execution-location constraints on this page.

This interface is available on Host and in AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float frexp(
    float value, int* exponent) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

### Prototype 2

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
[[nodiscard]] constexpr Tp frexp(
    Tp value, int* exponent) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

### Prototype 3

```cpp
namespace asc::std {
[[nodiscard]] constexpr double frexp(double value, int* exponent) noexcept;
}
```

Available locations: Host.

### Prototype 4

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double frexp(long double value, int* exponent) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

### Prototype 5

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
[[nodiscard]] constexpr double frexp(Tp value, int* exponent) noexcept;
}
```

Available locations: Host.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Tp` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. The extended floating-point selection of the exponential and scaling family accepts only the available half and bfloat16, not FP8. |

The unnamed default int template parameter is used for overload selection; the caller does not need to provide it.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Input value (dimensionless) to be decomposed into a normalized significand and exponent. |
| `exponent` | Output | Valid int storage that receives the binary exponent. |

## Return Value

The return type is determined per prototype (`float`, `Tp`, `double`, `long double`). Returns the significand and writes the binary exponent; the absolute value of the significand of a non-zero finite value lies in [0.5, 1).

## Constraints

- The extended floating-point templates of the exponential and scaling family accept only half and bfloat16; no extended overloads of this family are provided for FP8.

- Provides the float overload and the standard *f aliases; the underlying capability is provided by the Ascend C development kit.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    int exponent = 0;
    const auto fraction = asc::std::frexp(8.0F, &exponent);
    return fraction == 0.5F && exponent == 4;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
