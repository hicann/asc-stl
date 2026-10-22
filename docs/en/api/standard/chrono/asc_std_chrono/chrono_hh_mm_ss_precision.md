# asc::std::chrono::hh_mm_ss::precision

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

`hh_mm_ss<Duration>::precision` is the sub-second precision type used for the hours-minutes-seconds decomposition. It is a duration whose count type is `common_type_t<Duration, seconds>::rep` and whose period is 1 / 10^fractional_width seconds.

The computation rule of fractional_width is described in [`fractional_width`](chrono_hh_mm_ss_fractional_width.md).

## Declaration

precision is a public member type of hh_mm_ss; the alias above only demonstrates how to query it.

```cpp
template<class Duration>
using hh_mm_ss_precision_t =
    typename asc::std::chrono::hh_mm_ss<Duration>::precision;
```

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/chrono>
#include <asc/std/type_traits>

using split_type = asc::std::chrono::hh_mm_ss<asc::std::chrono::milliseconds>;
static_assert(asc::std::is_same_v<typename split_type::precision, asc::std::chrono::milliseconds>);
```

## Related APIs

- [`asc::std::chrono::hh_mm_ss`](chrono_hh_mm_ss.md)
- [API list for this header](asc_std_chrono.md)
