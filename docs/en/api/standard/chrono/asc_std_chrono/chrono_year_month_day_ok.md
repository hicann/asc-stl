# asc::std::chrono::year_month_day::ok

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

`asc::std::chrono::year_month_day::ok` determines whether the current calendar field combination represents a valid date.

`year_month_day` combines the three fields year, month, and day: it returns `true` when the year is in `[-32767, 32767]`, the month is in `[1, 12]`, and the day is between 1 and the actual number of days in that month of that year (validated by the leap year rule; for example, February 29 is valid only when that year is a leap year), otherwise it returns `false`.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::year_month_day`](chrono_year_month_day.md).

```cpp
// Excerpt of the declaration inside class asc::std::chrono::year_month_day; template parameters and other members are provided by the owning class.
[[nodiscard]] constexpr bool ok() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` if the condition holds, otherwise `false`. |

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/chrono>

bool example()
{
    const asc::std::chrono::year_month_day leap{
        asc::std::chrono::year{2024}, asc::std::chrono::month{2}, asc::std::chrono::day{29}};
    const asc::std::chrono::year_month_day ordinary{
        asc::std::chrono::year{2023}, asc::std::chrono::month{2}, asc::std::chrono::day{29}};
    return leap.ok() && !ordinary.ok();
}
```

## Related APIs

- [`asc::std::chrono::year_month_day`](chrono_year_month_day.md)
- [API list for this header](asc_std_chrono.md)
