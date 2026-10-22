# asc::std::exp

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

Headers: `<asc/std/cmath>`, `<asc/std/complex>`.

`asc::std::exp` computes the natural exponential; on the device side, the applicable scope is subject to the float and execution-location constraints on this page.

This interface is available on Host and in AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float exp(
    float value) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

### Prototype 2

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
[[nodiscard]] constexpr Tp exp(Tp value) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

### Prototype 3

```cpp
namespace asc::std {
[[nodiscard]] constexpr double exp(double value) noexcept;
}
```

Available locations: Host.

### Prototype 4

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double exp(long double value) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

### Prototype 5

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
[[nodiscard]] constexpr double exp(Tp value) noexcept;
}
```

Available locations: Host.

### Prototype 6

```cpp
namespace asc::std {
template <class T>
[[nodiscard]] complex<T> exp(const complex<T>& value) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. This complex overload requires including `<asc/std/complex>`; ASC complex components currently support only float.

### Prototype 7

```cpp
namespace asc::std {
template <>
[[nodiscard]] complex<float> exp(const complex<float>& value) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. This complex overload requires including `<asc/std/complex>`; ASC complex components currently support only float.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Tp` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. The extended floating-point selection of the exponential and scaling family accepts only the available half and bfloat16, not FP8. |
| `T` | Complex component type; ASC complex currently supports only float. The extended floating-point selection of the exponential and scaling family accepts only the available half and bfloat16, not FP8. |

The unnamed default int template parameter is used for overload selection; the caller does not need to provide it.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Complex operand of the base-e complex exponential operation. |

## Return Value

The return type is determined per prototype (`float`, `Tp`, `double`, `long double`, `complex<T>`, `complex<float>`). Returns the base-e exponential value.

## Constraints

- The extended floating-point templates of the exponential and scaling family accept only half and bfloat16; no extended overloads of this family are provided for FP8.

- Host follows the subnormal behavior of the system math library; the AI Core SIMT programming backend may flush subnormal results to zero, so Host underflow boundaries must not be applied directly to device results.

- Scalar precision and execution location are determined per prototype; complex inputs support only complex<float>.
- Interface availability depends on the corresponding float math capability.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::exp(0.0F);
    return result == 1.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
