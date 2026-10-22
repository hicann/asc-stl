# asc::std::chrono::months

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

`asc::std::chrono::months` is an integer-count duration of 2629746 seconds (one twelfth of the average year length) per tick, convertible with other `duration`s. When used as an offset in calendar arithmetic, its `count` denotes a number of years or months and does not correct the date by a fixed number of seconds.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Declaration

```cpp
namespace asc::std::chrono {
using months = duration<int, ratio_divide<years::period, ratio<12>>>;
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
    asc::std::chrono::months first{2}, second{3};
    return (first + second).count() == 5;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
