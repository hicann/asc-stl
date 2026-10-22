# asc::std::ratio::num

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

`asc::std::ratio::num` holds the numerator of the compile-time rational number.

Standard semantics reference: [cppreference `ratio`](https://en.cppreference.com/w/cpp/header/ratio).

## Declaration

`asc::std::ratio<Numerator, Denominator>::num` is a static `constexpr` member of type `const intmax_t`. Its value is the numerator divided by the greatest common divisor, with the sign of the denominator folded into the numerator.

```cpp
using R = asc::std::ratio<6, -8>;
static_assert(R::num == -3);
static_assert(R::den == 4);
```

## Constraints

- The denominator must not be zero; the normalized numerator and denominator must be representable by `intmax_t`.
- The numerator and denominator of the original template arguments must not be `INTMAX_MIN`; the denominator must be nonzero, and the intermediate and final results of the reduction and sign normalization must be representable by `intmax_t`.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/ratio>

bool example()
{
    using Ratio = asc::std::ratio<6, -8>;
    static_assert(Ratio::num == -3);
    static_assert(Ratio::den == 4);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_ratio.md)
