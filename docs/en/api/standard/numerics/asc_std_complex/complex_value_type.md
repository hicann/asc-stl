# asc::std::complex::value_type

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

`asc::std::complex::value_type` identifies the value type of elements or results.

Standard semantics reference: [cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex).

## Declaration

Member of: [`asc::std::complex`](complex.md).

```cpp
// Excerpt of the declaration inside the asc::std::complex class; template parameters and other members are provided by the enclosing class.
using value_type = T;
```

## Constraints

- Only the float or `complex<float>` operations declared on this page are provided.
- Interface availability depends on the corresponding float math capability.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/complex>

void use_type()
{
    using alias_type = typename asc::std::complex<float>::value_type;
}
```

## Related APIs

- [`asc::std::complex`](complex.md)
- [API list for this header](asc_std_complex.md)
