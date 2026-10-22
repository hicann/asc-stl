# asc::std::chrono::month_weekday_last::ok

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

`asc::std::chrono::month_weekday_last::ok` determines whether the current calendar field combination represents a valid date.

`month_weekday_last` combines the month and the "last given weekday of the month" fields: it returns `true` when the month is in `[1, 12]` and the weekday is in `[0, 6]` (where 0 denotes Sunday and 6 denotes Saturday), and `false` otherwise.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::month_weekday_last`](chrono_month_weekday_last.md).

```cpp
// Declaration excerpt from inside the asc::std::chrono::month_weekday_last class; template parameters and other members are provided by the enclosing class.
[[nodiscard]] constexpr bool ok() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, and `false` otherwise. |

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::month_weekday_last value{asc::std::chrono::month{2}, asc::std::chrono::weekday_last{asc::std::chrono::weekday{4}}};
    return value.ok();
}
```

## Related APIs

- [`asc::std::chrono::month_weekday_last`](chrono_month_weekday_last.md)
- [API list for this header](asc_std_chrono.md)
