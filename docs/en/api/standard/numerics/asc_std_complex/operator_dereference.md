# asc::std::operator*

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

`asc::std::operator*` performs complex multiplication: Prototype 1 multiplies two `complex<float>` values by the complex multiplication rule; Prototype 2 multiplies both the real part and the imaginary part of a `complex<float>` by a `float` scalar; Prototype 3 is a `float` scalar multiplied by a `complex<float>`, with the same result as the scalar multiplication of Prototype 2.

Standard semantics reference: [cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex).

## Function Prototype

The following function templates can be used in Host, AI Core SIMD programming, and AI Core SIMT programming; T can currently only be float.

```cpp
namespace asc::std {
template<class T> constexpr complex<T> operator*(const complex<T>& left, const complex<T>& right) noexcept;
}
```

```cpp
namespace asc::std {
template<class T> constexpr complex<T> operator*(const complex<T>& left, const T& right) noexcept;
}
```

```cpp
namespace asc::std {
template<class T> constexpr complex<T> operator*(const T& left, const complex<T>& right) noexcept;
}
```

Host additionally provides two non-template overloads taking float by value:

```cpp
namespace asc::std {
constexpr complex<float> operator*(const complex<float>& left, float right) noexcept;
}
```

```cpp
namespace asc::std {
constexpr complex<float> operator*(float left, const complex<float>& right) noexcept;
}
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Component type of the ASC complex number; currently float only. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Left operand of the multiplication, a complex number or a scalar float. |
| `right` | Input | Right operand of the multiplication, a complex number or a scalar float. |

Two complex numbers are computed by complex multiplication; the scalar overloads multiply both the real part and the imaginary part by the scalar and do not modify the inputs.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::std::complex<float>` | Returns the complex value computed according to the corresponding complex arithmetic rule. |
| Prototype 2 | `asc::std::complex<float>` | Returns the complex value computed according to the corresponding complex arithmetic rule. |
| Prototype 3 | `asc::std::complex<float>` | Returns the complex value computed according to the corresponding complex arithmetic rule. |

## Constraints

- Only the float or `complex<float>` operations declared on this page are provided.
- Interface availability depends on the corresponding float math capability.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/complex>

decltype(auto) example(const asc::std::complex<float>& lhs, const asc::std::complex<float>& rhs)
{
    return asc::std::operator*(lhs, rhs);
}
```

## Related APIs

- [API list for this header](asc_std_complex.md)
