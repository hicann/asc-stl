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
- Complex division uses ratio scaling. For finite inputs, an overflowing intermediate component is retried with a scaled numerator; for example, `(max + max*i) / (1 + i)` returns `(max, 0)`, where `max` is the largest finite float. This remains float arithmetic: rounding, underflow, and a mathematically unrepresentable result are still possible.
- In frequency-response estimation, exclude or separately handle excitation bins equal to zero before calling this interface.
- On the validated CANN 9.2.0-beta.2 / Ascend 950 SIMT configuration, `(1 + i) / (max + max*i)` returns zero instead of the subnormal real result approximately `2.93873588e-39`. A direct `1.0f / max` probe also returns zero, while `min_normal * 0.5f`, subnormal bit construction, and load/store preserve their subnormal values. This is an observed limitation of that division path, not a statement that all device arithmetic flushes subnormals. The complex division implementation does not currently recover this result; validate underflow boundaries on the actual toolchain and device.

## Example

The following Host example estimates a batch of frequency-response bins. The second bin exercises large, finite spectrum values without manually splitting complex arithmetic into real and imaginary expressions.

```cpp
#include <asc/std/complex>
#include <asc/std/limits>

using Complex = asc::std::complex<float>;

// Frequency response H[k] = Y[k] / X[k]; each excitation bin is nonzero.
void example(const Complex* measured, const Complex* excitation, Complex* response, int bins)
{
    for (int k = 0; k < bins; ++k) {
        response[k] = measured[k] / excitation[k];
    }
}

bool verify_example()
{
    const float large = asc::std::numeric_limits<float>::max();
    const Complex measured[] = {{1.0f, 2.0f}, {large, large}};
    const Complex excitation[] = {{2.0f, 1.0f}, {1.0f, 1.0f}};
    Complex response[2];
    example(measured, excitation, response, 2);
    return response[0].real() == 0.8f && response[0].imag() == 0.6f &&
        response[1].real() == large && response[1].imag() == 0.0f;
}
```

## Related APIs

- [API list for this header](asc_std_complex.md)
