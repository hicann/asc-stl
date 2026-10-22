# asc::std::ratio_less

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

`asc::std::ratio_less` represents a ratio as a compile-time rational number, or determines the magnitude relationship between two ratios.

Standard semantics reference: [cppreference `ratio`](https://en.cppreference.com/w/cpp/header/ratio).

## Declaration

```cpp
namespace asc::std {
template<class R1, class R2> struct ratio_less;
} // namespace asc::std
```

## Constraints

- The denominator must not be zero; the normalized numerator and denominator must be representable by `intmax_t`.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/ratio>

void use_trait()
{
    // 1/3 is less than 1/2
    static_assert(asc::std::ratio_less<asc::std::ratio<1, 3>, asc::std::ratio<1, 2>>::value);
    // Negative comparison: -1/2 is less than -1/3
    static_assert(asc::std::ratio_less_v<asc::std::ratio<-1, 2>, asc::std::ratio<-1, 3>>);
    // Counterexample: 1/2 is not less than 1/3
    static_assert(!asc::std::ratio_less_v<asc::std::ratio<1, 2>, asc::std::ratio<1, 3>>);
}
```

## Related APIs

- [API list for this header](asc_std_ratio.md)
