# asc::std::chrono::year_month_weekday_last::weekday

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

`asc::std::chrono::year_month_weekday_last::weekday` returns the weekday field in the current calendar combination.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::year_month_weekday_last`](chrono_year_month_weekday_last.md).

```cpp
// Excerpt of the declaration inside class asc::std::chrono::year_month_weekday_last; template parameters and other members are provided by the owning class.
[[nodiscard]] constexpr chrono::weekday weekday() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `chrono::weekday` | Returns the weekday field in the current calendar combination. |

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::year_month_weekday_last value{asc::std::chrono::year{2024}, asc::std::chrono::month{2}, asc::std::chrono::weekday_last{asc::std::chrono::weekday{4}}};
    return value.weekday().c_encoding() == 4;
}
```

## Related APIs

- [`asc::std::chrono::year_month_weekday_last`](chrono_year_month_weekday_last.md)
- [API list for this header](asc_std_chrono.md)
