# asc::std::chrono::years

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

`asc::std::chrono::years` is an integer-counted duration with 31556952 seconds per tick (the average year length over the 400-year Gregorian cycle), convertible with other `duration` types. When used as an offset in calendar arithmetic, its `count` denotes a number of years or months and does not correct dates by a fixed number of seconds.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Declaration

```cpp
namespace asc::std::chrono {
using years = duration<int, ratio_multiply<ratio<146097, 400>, days::period>>;
} // namespace asc::std::chrono
```

## Constraints

- Provides value operations and the six explicit relational operators.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::years first{2}, second{3};
    return (first + second).count() == 5;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
