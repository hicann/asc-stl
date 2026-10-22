# asc::std::chrono::hh_mm_ss::fractional_width

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

Header: `<asc/std/chrono>`.

`asc::std::chrono::hh_mm_ss::fractional_width` gives the number of decimal digits of the sub-second part of the time representation.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Declaration

fractional_width is a static constexpr member of hh_mm_ss. The following is an expression that queries this public member and does not add a new member.

```cpp
template<class Duration>
inline constexpr unsigned fractional_width_of =
    asc::std::chrono::hh_mm_ss<Duration>::fractional_width;
```

## Constraints

- Let D be common_type_t<Duration, seconds>::period::den. If 1/D can be exactly represented with no more than 18 decimal places, the value is the minimum number of digits required; otherwise it is 6. Whole-second precision corresponds to 0.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/chrono>

static_assert(asc::std::chrono::hh_mm_ss<asc::std::chrono::milliseconds>::fractional_width == 3);
static_assert(asc::std::chrono::hh_mm_ss<asc::std::chrono::seconds>::fractional_width == 0);
```

## Related APIs

- [`asc::std::chrono::hh_mm_ss`](chrono_hh_mm_ss.md)
- [API list for this header](asc_std_chrono.md)
