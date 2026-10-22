# asc::std::literals::complex_literals::operator""if

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

`operator""if` constructs a `complex<float>` from a purely imaginary numeric literal, equivalent to `complex<float>{0.0f, static_cast<float>(arg)}`.

Standard semantics reference: [cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex).

## Function Prototype

### Prototype 1

```cpp
// Located in the asc::std::literals::complex_literals inline namespace.
[[nodiscard]] constexpr asc::std::complex<float> operator""if(long double arg) noexcept;
```

This prototype applies to `C++17+` and is available in Host.

### Prototype 2

```cpp
// Located in the asc::std::literals::complex_literals inline namespace.
[[nodiscard]] constexpr asc::std::complex<float> operator""if(unsigned long long arg) noexcept;
```

This prototype applies to `C++17+` and is available in Host.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `arg` | Input | Scalar value controlling this operation; the valid values are determined jointly by the declaration and the constraints. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::std::complex<float>` | A float complex number whose real part is 0 and whose imaginary part is the literal value. |

## Constraints

- The imaginary part is the result of converting the literal value to float, and the real part is zero.
- An integer literal is first converted to float and then used as the imaginary part, with a real part of zero.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/complex>

decltype(auto) example(long double arg)
{
    return asc::std::literals::complex_literals::operator""if(arg);
}
```

## Related APIs

- [API list for this header](asc_std_complex.md)
