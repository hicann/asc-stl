# asc::std::ratio::type

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

Header: `<asc/std/ratio>`.

`asc::std::ratio::type` provides the member type computed by the type trait, mapping, or adaptor.

Standard semantics reference: [cppreference `ratio`](https://en.cppreference.com/w/cpp/header/ratio).

## Declaration

Member of: [`asc::std::ratio`](ratio.md).

```cpp
// Declaration excerpt from inside the asc::std::ratio class; template parameters and other members are provided by the enclosing class.
using type = ratio<num, den>;
```

## Constraints

- The denominator must not be zero; the normalized numerator and denominator must be representable by `intmax_t`.
- The numerator and denominator of the original template arguments must not be `INTMAX_MIN`; the denominator must be nonzero, and the intermediate and final results of the reduction and sign normalization must be representable by `intmax_t`.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/ratio>

void use_type()
{
    using alias_type = typename asc::std::ratio<2, 4>::type;
    static_assert(alias_type::num == 1 && alias_type::den == 2);
}
```

## Related APIs

- [`asc::std::ratio`](ratio.md)
- [API list for this header](asc_std_ratio.md)
