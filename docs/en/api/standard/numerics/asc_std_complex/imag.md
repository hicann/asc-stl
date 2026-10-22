# asc::std::imag

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

`asc::std::imag` returns the imaginary part of a complex number.

Standard semantics reference: [cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex).

## Function Prototype

### Prototype 1: Complex Input

```cpp
namespace asc::std {
template<class T> constexpr T imag(const complex<T>& value) noexcept;
} // namespace asc::std
```

### Prototype 2: Integer Input

```cpp
namespace asc::std {
template<class T, enable_if_t<is_integral_v<T>, int> = 0>
constexpr double imag(T value) noexcept;
} // namespace asc::std
```

### Prototype 3: Floating-Point Input

```cpp
namespace asc::std {
template<class T, enable_if_t<is_floating_point_v<T>, int> = 0>
constexpr T imag(T value) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Component type of the complex input; currently must be `float`; for scalar inputs, respectively a type satisfying `is_integral_v<T>` or `is_floating_point_v<T>`. |

The unnamed template parameter defaults to 0 and selects the corresponding scalar overload; the caller does not need to provide it explicitly.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Complex or scalar value whose imaginary part is to be read; a scalar is treated as having an imaginary part of 0. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `T` | Returns the imaginary part of the complex number, currently `float`. |
| Prototype 2 | `double` | Returns 0 of type `double`. |
| Prototype 3 | `T` | Returns 0 of the original floating-point type. |

## Constraints

- `asc::std::complex` currently supports only the `float` component type; this does not restrict the template parameter of the scalar overloads to `float` only.
- The scalar overloads are constrained by the integer and floating-point traits respectively; the concrete scalar type must still be supported by the target compilation mode.
- The listed overloads are all `constexpr` and declared `noexcept`, and do not modify the input object.

## Example

The following Host snippet demonstrates the interface call with concrete objects.

```cpp
#include <asc/std/complex>

decltype(auto) example()
{
    asc::std::complex<float> value{1.0f, 2.0f};
    return asc::std::imag(value);
}
```

## Related APIs

- [API list for this header](asc_std_complex.md)
