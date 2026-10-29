# asc::std::norm

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

`asc::std::norm` returns the squared magnitude of a complex number.

Standard semantics reference: [cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
template<class T> constexpr T norm(const complex<T>& value) noexcept;
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr T norm(T value) noexcept;
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Component type of the complex operand; currently must be `float`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Complex operand whose squared magnitude (real part squared plus imaginary part squared) is requested. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Value type of the real-number input; the return value is the square of that value. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Real-number input whose squared magnitude is requested (returns value * value). |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T` | Returns the squared magnitude of the complex number. |
| Prototype 2 | `T` | Returns the squared magnitude of the complex number. |

## Constraints

- The complex overload currently accepts only `complex<float>`; the scalar overload directly computes `value * value` and returns it as `T` without constructing a complex number.
- The scalar type must support that multiplication expression and the conversion of the result to `T`, and must satisfy the type capabilities of the target compilation mode.
- Both overloads are declared `noexcept`.

## Example

The following Host snippet demonstrates the interface call with concrete objects.

```cpp
#include <asc/std/complex>

decltype(auto) example()
{
    asc::std::complex<float> value{1.0f, 2.0f};
    return asc::std::norm(value);
}

bool verify_example()
{
    return example() == 5.0f;
}
```

## Related APIs

- [API list for this header](asc_std_complex.md)
