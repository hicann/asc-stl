# asc::std::complex::imag

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

`asc::std::complex::imag` returns the imaginary part of the complex number.

Standard semantics reference: [cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex).

## Function Prototype

Member of: [`asc::std::complex`](complex.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside the asc::std::complex class; template parameters and other members are provided by the enclosing class.
value_type imag() const volatile noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside the asc::std::complex class; template parameters and other members are provided by the enclosing class.
constexpr value_type imag() const noexcept;
```

### Prototype 3

```cpp
// Excerpt of the declaration inside the asc::std::complex class; template parameters and other members are provided by the enclosing class.
void imag(value_type value) volatile noexcept;
```

### Prototype 4

```cpp
// Excerpt of the declaration inside the asc::std::complex class; template parameters and other members are provided by the enclosing class.
constexpr void imag(value_type value) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

No parameters.

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | New value to write to the imaginary part (a value_type scalar, dimensionless). |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | New value to write to the imaginary part (a value_type scalar, dimensionless). |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `value_type` | Returns the imaginary part of the complex number. |
| Prototype 2 | `value_type` | Returns the imaginary part of the complex number. |
| Prototype 3 | `void` | No return value. |
| Prototype 4 | `void` | No return value. |

## Constraints

- Only the float or `complex<float>` operations declared on this page are provided.
- Interface availability depends on the corresponding float math capability.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/complex>

bool example()
{
    asc::std::complex<float> value(2.0f, 3.0f);
    return value.real() == 2.0f && value.imag() == 3.0f;
}
```

## Related APIs

- [`asc::std::complex`](complex.md)
- [API list for this header](asc_std_complex.md)
