# asc::std::operator/

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

`asc::std::operator/` computes the quotient according to the complex division rule.

Standard semantics reference: [cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class T> constexpr complex<T> operator/(const T& lhs, const complex<T>& rhs) noexcept;
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class T> constexpr complex<T> operator/(const complex<T>& lhs, const T& rhs) noexcept;
} // namespace asc::std
```

### Prototype 3

```cpp
namespace asc::std {
template<class T> constexpr complex<T> operator/(const complex<T>& lhs, const complex<T>& rhs) noexcept;
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Component value type of the scalar left operand, the complex right operand, and the result. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `lhs` | Input | Left operand of the complex division (a real scalar, serving as the dividend). |
| `rhs` | Input | Right operand of the complex division (a complex number, serving as the divisor; must be non-zero). |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Component value type of the complex left operand, the scalar right operand, and the result. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `lhs` | Input | Left operand of the complex division (a complex number, serving as the dividend). |
| `rhs` | Input | Right operand of the complex division (a real scalar, serving as the divisor; must be non-zero). |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Value type of the components (real part and imaginary part) of the complex operand; must be a floating-point type. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `lhs` | Input | Left operand of the complex division (a complex number, serving as the dividend). |
| `rhs` | Input | Right operand of the complex division (a complex number, serving as the divisor; must be non-zero). |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `complex<T>` | Returns the complex value computed according to the corresponding complex arithmetic rule. |
| Prototype 2 | `complex<T>` | Returns the complex value computed according to the corresponding complex arithmetic rule. |
| Prototype 3 | `complex<T>` | Returns the complex value computed according to the corresponding complex arithmetic rule. |

## Constraints

- Only the float or `complex<float>` operations declared on this page are provided.
- Interface availability depends on the corresponding float math capability.

## Example

The following Host snippet demonstrates the interface call with concrete objects.

```cpp
#include <asc/std/complex>

decltype(auto) example()
{
    asc::std::complex<float> left{1.0f, 2.0f};
    asc::std::complex<float> right{2.0f, 1.0f};
    return asc::std::operator/(left, right);
}
```

## Related APIs

- [API list for this header](asc_std_complex.md)
