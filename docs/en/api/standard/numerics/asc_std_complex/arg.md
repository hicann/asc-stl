# asc::std::arg

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

Header: `<asc/std/complex>`.

`asc::std::arg` returns the phase angle of a complex number.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex).

## Function Prototype

The following two forms are used in Host and AI Core SIMT programming:

```cpp
namespace asc::std {
[[nodiscard]] float arg(float value) noexcept;
}
```

```cpp
namespace asc::std {
template<class T> [[nodiscard]] T arg(const complex<T>& value) noexcept;
}
```

The following scalar overloads are for Host only:

```cpp
namespace asc::std {
[[nodiscard]] double arg(double value) noexcept;
}
```

```cpp
namespace asc::std {
[[nodiscard]] long double arg(long double value) noexcept;
}
```

```cpp
namespace asc::std {
template<class T> [[nodiscard]] double arg(T value) noexcept;
}
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Real-number input whose phase angle is requested (treated as a complex number with an imaginary part of 0; the return value is 0 or π radians). |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Value type of the components (real part and imaginary part) of the complex operand; must be a floating-point type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Complex operand whose phase angle is requested (the phase angle is atan2(imaginary part, real part), in radians). |

## Return Value

Returns the phase angle atan2(imaginary part, real part) in radians. A complex input returns T; scalar float, double, and long double return their original types respectively, and integers return double. A scalar is treated as a complex number whose imaginary part is positive zero.

## Constraints

- ASC complex input supports only complex<float>; Host scalars additionally support double, long double, and integers. The integer template uses static_assert to require T to be an integer type.
- Interface availability depends on the corresponding float math capability.

## Example

The following Host example uses concrete inputs and checks the result.

```cpp
#include <asc/std/complex>

bool example()
{
    const asc::std::complex<float> value(1.0F, 0.0F);
    return asc::std::arg(value) == 0.0F && asc::std::arg(2.0) == 0.0;
}
```

## Related APIs

- [API list for this header](asc_std_complex.md)
