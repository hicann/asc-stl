# asc::std::proj

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

`asc::std::proj` projects a complex number onto the Riemann sphere.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class T> [[nodiscard]] complex<T> proj(T value) noexcept;
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class T> [[nodiscard]] complex<T> proj(const complex<T>& value) noexcept;
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Value type of the real-number input, which is also the component type of the returned complex number. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Real-number input to be projected onto the Riemann sphere (treated as a complex number with an imaginary part of 0; infinity maps to (+inf, 0)). |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Value type of the components (real part and imaginary part) of the complex operand; must be a floating-point type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Complex operand to be projected onto the Riemann sphere (when the real part or the imaginary part is inf, it maps to a +inf real part and a 0 imaginary part). |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `complex<T>` | Returns the projection of the input complex number onto the Riemann sphere. |
| Prototype 2 | `complex<T>` | Returns the projection of the input complex number onto the Riemann sphere. |

## Constraints

- Only the float or `complex<float>` operations declared on this page are provided.
- Interface availability depends on the corresponding float math capability.

## Example

The following Host snippet demonstrates the interface call with concrete objects.

```cpp
#include <asc/std/complex>

decltype(auto) example()
{
    asc::std::complex<float> value{1.0f, 2.0f};
    return asc::std::proj(value);
}
```

## Related APIs

- [API list for this header](asc_std_complex.md)
