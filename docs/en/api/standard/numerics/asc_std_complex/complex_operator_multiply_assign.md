# asc::std::complex::operator*=

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

`asc::std::complex::operator*=` processes the current object and the operand according to the available operator rules of `complex`.

Standard semantics reference: [cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex).

## Function Prototype

Member of: [`asc::std::complex`](complex.md).

### Prototype 1: Complex Right Operand

```cpp
// Excerpt of the declaration inside the asc::std::complex class; template parameters and other members are provided by the enclosing class.
constexpr complex<T>& operator*=(complex<T> rhs) noexcept;
```

### Prototype 2: Scalar Right Operand

```cpp
// Excerpt of the declaration inside the asc::std::complex class; template parameters and other members are provided by the enclosing class.
constexpr complex<T>& operator*=(const T& rhs) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `rhs` | Input | Right operand of the multiplicative assignment: Prototype 1 takes `complex<T>` by value; Prototype 2 takes a real scalar, and both the real part and the imaginary part of the current object are multiplied by that value. |

## Return Value

| Return type | Description |
| --- | --- |
| `complex<T> &` | Returns a reference to the updated current object, which can continue to be used for assignment or compound operations. |

## Constraints

- Only the float or `complex<float>` operations declared on this page are provided.
- Interface availability depends on the corresponding float math capability.

## Example

The following Host snippet demonstrates the call with concrete numeric types; the state and arguments must satisfy the constraints on this page.

```cpp
#include <asc/std/complex>

void example(asc::std::complex<float>& value)
{
    value *= 2.0f;
}
```

## Related APIs

- [`asc::std::complex`](complex.md)
- [API list for this header](asc_std_complex.md)
