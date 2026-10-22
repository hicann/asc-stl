# asc::std::chrono::year_month_day::operator sys_days

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

`asc::std::chrono::year_month_day::operator sys_days` is provided by `<asc/std/chrono>`; it converts to a time point at system-epoch day precision. The interface follows the semantics of the corresponding C++ standard facility; the language modes and call locations of ASC-STL are subject to the declaration on this page.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`year_month_day`](chrono_year_month_day.md).

```cpp
[[nodiscard]] constexpr operator sys_days() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `asc::std::chrono::sys_days` | A day-precision time point of this date on the system time line. |

## Constraints

- The conversion between the civil calendar and the system epoch follows the civil-calendar algorithm.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::year_month_day value{asc::std::chrono::year{2024}, asc::std::chrono::month{2}, asc::std::chrono::day{29}};
    return static_cast<asc::std::chrono::sys_days>(value).time_since_epoch().count() == 19782;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
