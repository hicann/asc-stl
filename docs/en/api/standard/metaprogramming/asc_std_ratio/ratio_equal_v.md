# asc::std::ratio_equal_v

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

`asc::std::ratio_equal_v` determines at compile time whether two rational numbers satisfy the magnitude relation indicated by the name.

Standard semantics reference: [cppreference `ratio`](https://en.cppreference.com/w/cpp/header/ratio).

## Declaration

```cpp
namespace asc::std {
template<class R1, class R2> inline constexpr bool ratio_equal_v = ratio_equal<R1, R2>::value;
} // namespace asc::std
```

## Constraints

- The denominator must not be zero; the normalized numerator and denominator must be representable by `intmax_t`.

## Example

The following snippet checks the interface result with concrete template arguments and an independent expected value.

```cpp
#include <asc/std/ratio>

static_assert((asc::std::ratio_equal_v<asc::std::ratio<1, 2>, asc::std::ratio<1, 3>>) == false);
```

## Related APIs

- [API list for this header](asc_std_ratio.md)
