# asc::std::chrono::year_month_weekday::ok

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

`asc::std::chrono::year_month_weekday::ok` determines whether the current calendar field combination represents a valid date.

`year_month_weekday` combines year, month, and "the n-th occurrence of a weekday": it returns `true` when all of the following hold — the year is in `[-32767, 32767]`, the month is in `[1, 12]`, the weekday is in `[0, 6]` (0 denotes Sunday and 6 denotes Saturday), and the index is in `[1, 5]` — otherwise it returns `false`; when the index is 5, it additionally requires that a 5th occurrence of that weekday actually exists in that month (i.e. the corresponding date does not exceed the last day of that month).

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::year_month_weekday`](chrono_year_month_weekday.md).

```cpp
// Excerpt of the declaration inside class asc::std::chrono::year_month_weekday; template parameters and other members are provided by the owning class.
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
    const asc::std::chrono::year_month_weekday valid{
        asc::std::chrono::year{2024}, asc::std::chrono::month{2}, asc::std::chrono::Thursday[5]};
    const asc::std::chrono::year_month_weekday invalid{
        asc::std::chrono::year{2023}, asc::std::chrono::month{2}, asc::std::chrono::Thursday[5]};
    return valid.ok() && !invalid.ok();
}
```

## Related APIs

- [`asc::std::chrono::year_month_weekday`](chrono_year_month_weekday.md)
- [API list for this header](asc_std_chrono.md)
