# asc::std::polar

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

`asc::std::polar` constructs a complex number from its magnitude and phase angle.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex).

## Function Prototype

```cpp
namespace asc::std {
template<class T> [[nodiscard]] complex<T> polar(const T& radius, const T& angle = T()) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Component value type of the magnitude, the phase angle, and the returned complex number; must be a floating-point type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `radius` | Input | Magnitude of the complex number (a non-negative real number, dimensionless). |
| `angle` | Input | Phase angle of the complex number (an angle quantity, in radians); 0 when omitted. |

## Return Value

| Return type | Description |
| --- | --- |
| `complex<T>` | Returns the complex number constructed from the given magnitude and phase angle. |

## Constraints

- Only the float or `complex<float>` operations declared on this page are provided.
- Interface availability depends on the corresponding float math capability.

## Example

The following Host snippet demonstrates the interface call with concrete objects.

```cpp
#include <asc/std/complex>

decltype(auto) example()
{
    return asc::std::polar(1.0f, 0.5f);
}

bool verify_example()
{
    const auto result = example();
    return result.real() > 0.8775f && result.real() < 0.8777f && result.imag() > 0.4793f && result.imag() < 0.4796f;
}
```

## Related APIs

- [API list for this header](asc_std_complex.md)
