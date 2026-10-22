# asc::std::ratio

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

`asc::std::ratio` represents a ratio as a compile-time rational number, or determines the magnitude relationship between two ratios.

Standard semantics reference: [cppreference `ratio`](https://en.cppreference.com/w/cpp/header/ratio).

## Declaration

```cpp
namespace asc::std {
template<intmax_t Numerator, intmax_t Denominator = 1> class ratio;
} // namespace asc::std
```

## Constraints

- The denominator must not be zero; the normalized numerator and denominator must be representable by `intmax_t`.
- The numerator and denominator of the original template arguments must not be `INTMAX_MIN`; the denominator must be nonzero, and the intermediate and final results of the reduction and sign normalization must be representable by `intmax_t`.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/ratio>

void use_trait()
{
    // 4/2 reduces to 2/1; the denominator is always positive
    static_assert(asc::std::ratio<4, 2>::num == 2);
    static_assert(asc::std::ratio<4, 2>::den == 1);
    // The negative sign is normalized into the numerator; den remains positive
    static_assert(asc::std::ratio<-4, 2>::num == -2);
    static_assert(asc::std::ratio<-4, 2>::den == 1);
    // The type member is the equivalent reduced ratio type
    static_assert(asc::std::ratio<4, 2>::type::num == 2);
    static_assert(asc::std::ratio<4, 2>::type::den == 1);
}
```

## Related APIs

- [API list for this header](asc_std_ratio.md)
