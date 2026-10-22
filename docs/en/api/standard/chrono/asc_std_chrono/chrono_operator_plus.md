# asc::std::chrono::`operator+`

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

`asc::std::chrono::operator+` performs addition on durations, time points, or calendar fields. Durations first unify their periods, and date forms are offset by day, month, or year.

For duration semantics see [`duration`](chrono_duration.md). Calendar validity is determined by the `ok()` of the corresponding type.

## Function Prototype

Called as `left + right`; hidden friends participate through argument-dependent lookup and must not be relied on through qualified namespace lookup.

### Prototype 1

Member of: [`duration<Rep, Period>`](chrono_duration.md). The following is a hidden-friend declaration within the class; the class template parameters (if any) are provided by the owning type.

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr common_type_t<duration, duration<Rep2, Period2>> operator+(const duration& left, const duration<Rep2, Period2>& right);
```

### Prototype 2

Member of: [`time_point<Clock, Duration>`](chrono_time_point.md). The following is a hidden-friend declaration within the class; the class template parameters (if any) are provided by the owning type.

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>> operator+(const time_point& left, const chrono::duration<Rep2, Period2>& right);
```

### Prototype 3

Member of: [`time_point<Clock, Duration>`](chrono_time_point.md). The following is a hidden-friend declaration within the class; the class template parameters (if any) are provided by the owning type.

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>> operator+(const chrono::duration<Rep2, Period2>& left, const time_point& right);
```

### Prototype 4

Member of: [`day`](chrono_day.md). The following is a hidden-friend declaration within the class; the class template parameters (if any) are provided by the owning type.

```cpp
[[nodiscard]] friend constexpr day operator+(const day& left, const days& right) noexcept;
```

### Prototype 5

Member of: [`day`](chrono_day.md). The following is a hidden-friend declaration within the class; the class template parameters (if any) are provided by the owning type.

```cpp
[[nodiscard]] friend constexpr day operator+(const days& left, const day& right) noexcept;
```

### Prototype 6

Member of: [`month`](chrono_month.md). The following is a hidden-friend declaration within the class; the class template parameters (if any) are provided by the owning type.

```cpp
[[nodiscard]] friend constexpr month operator+(const month& left, const months& right) noexcept;
```

### Prototype 7

Member of: [`month`](chrono_month.md). The following is a hidden-friend declaration within the class; the class template parameters (if any) are provided by the owning type.

```cpp
[[nodiscard]] friend constexpr month operator+(const months& left, const month& right) noexcept;
```

### Prototype 8

Member of: [`weekday`](chrono_weekday.md). The following is a hidden-friend declaration within the class; the class template parameters (if any) are provided by the owning type.

```cpp
[[nodiscard]] friend constexpr weekday operator+(const weekday& left, const days& right) noexcept;
```

### Prototype 9

Member of: [`weekday`](chrono_weekday.md). The following is a hidden-friend declaration within the class; the class template parameters (if any) are provided by the owning type.

```cpp
[[nodiscard]] friend constexpr weekday operator+(const days& left, const weekday& right) noexcept;
```

### Prototype 10

Member of: [`year`](chrono_year.md). The following is a hidden-friend declaration within the class; the class template parameters (if any) are provided by the owning type.

```cpp
[[nodiscard]] friend constexpr year operator+(const year& left, const years& right) noexcept;
```

### Prototype 11

Member of: [`year`](chrono_year.md). The following is a hidden-friend declaration within the class; the class template parameters (if any) are provided by the owning type.

```cpp
[[nodiscard]] friend constexpr year operator+(const years& left, const year& right) noexcept;
```

### Prototype 12

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month operator+(const year_month& left, const months& right) noexcept;
```

### Prototype 13

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month operator+(const months& left, const year_month& right) noexcept;
```

### Prototype 14

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month operator+(const year_month& left, const years& right) noexcept;
```

### Prototype 15

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month operator+(const years& left, const year_month& right) noexcept;
```

### Prototype 16

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day operator+(const year_month_day& left, const months& right) noexcept;
```

### Prototype 17

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day operator+(const months& left, const year_month_day& right) noexcept;
```

### Prototype 18

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day operator+(const year_month_day& left, const years& right) noexcept;
```

### Prototype 19

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day operator+(const years& left, const year_month_day& right) noexcept;
```

### Prototype 20

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day_last operator+(const year_month_day_last& left, const months& right) noexcept;
```

### Prototype 21

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day_last operator+(const months& left, const year_month_day_last& right) noexcept;
```

### Prototype 22

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day_last operator+(const year_month_day_last& left, const years& right) noexcept;
```

### Prototype 23

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day_last operator+(const years& left, const year_month_day_last& right) noexcept;
```

### Prototype 24

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday operator+(const year_month_weekday& left, const months& right) noexcept;
```

### Prototype 25

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday operator+(const months& left, const year_month_weekday& right) noexcept;
```

### Prototype 26

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday operator+(const year_month_weekday& left, const years& right) noexcept;
```

### Prototype 27

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday operator+(const years& left, const year_month_weekday& right) noexcept;
```

### Prototype 28

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator+(const year_month_weekday_last& left, const months& right) noexcept;
```

### Prototype 29

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator+(const months& left, const year_month_weekday_last& right) noexcept;
```

### Prototype 30

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator+(const year_month_weekday_last& left, const years& right) noexcept;
```

### Prototype 31

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator+(const years& left, const year_month_weekday_last& right) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep2` | The count or scalar representation type of the other operand; forms a common count type with Rep. |
| `Period2` | The tick period of the other duration, a ratio type based on seconds. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A duration value; its count unit is determined by its period, and operating with another duration first forms a common tick period. |
| `right` | Input | A duration value; its count unit is determined by its period, and operating with another duration first forms a common tick period. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep2` | The count or scalar representation type of the other operand; forms a common count type with Rep. |
| `Period2` | The tick period of the other duration, a ratio type based on seconds. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A time point; participates in comparison or offset on the same Clock, and the result precision is determined by the common duration. |
| `right` | Input | A duration value; its count unit is determined by its period, and operating with another duration first forms a common tick period. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep2` | The count or scalar representation type of the other operand; forms a common count type with Rep. |
| `Period2` | The tick period of the other duration, a ratio type based on seconds. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A duration value; its count unit is determined by its period, and operating with another duration first forms a common tick period. |
| `right` | Input | A time point; participates in comparison or offset on the same Clock, and the result precision is determined by the common duration. |

### Parameters of Prototype 4

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The day field, usually 1 to 31; carries no month or year. |
| `right` | Input | A signed number of days in units of 24 hours; when used for a field offset, it denotes the amount the day field moves. |

### Parameters of Prototype 5

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of days in units of 24 hours; when used for a field offset, it denotes the amount the day field moves. |
| `right` | Input | The day field, usually 1 to 31; carries no month or year. |

### Parameters of Prototype 6

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The month field, where 1 to 12 denote January through December. |
| `right` | Input | A signed number of months; for a standalone month the result wraps around every 12 months and does not keep the carry into years. |

### Parameters of Prototype 7

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of months; for a standalone month the result wraps around every 12 months and does not keep the carry into years. |
| `right` | Input | The month field, where 1 to 12 denote January through December. |

### Parameters of Prototype 8

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The weekday field, with C encoding where 0 is Sunday and 1 to 6 are Monday through Saturday. |
| `right` | Input | A signed number of days in units of 24 hours; when used for a field offset, it denotes the amount the day field moves. |

### Parameters of Prototype 9

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of days in units of 24 hours; when used for a field offset, it denotes the amount the day field moves. |
| `right` | Input | The weekday field, with C encoding where 0 is Sunday and 1 to 6 are Monday through Saturday. |

### Parameters of Prototype 10

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The year field, with a valid range of -32767 to 32767. |
| `right` | Input | A signed number of years; in calendar arithmetic the other fields are preserved. |

### Parameters of Prototype 11

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of years; in calendar arithmetic the other fields are preserved. |
| `right` | Input | The year field, with a valid range of -32767 to 32767. |

### Parameters of Prototype 12

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of year and month. |
| `right` | Input | A signed number of months; in calendar arithmetic it carries into the year every 12 months. |

### Parameters of Prototype 13

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of months; in calendar arithmetic it carries into the year every 12 months. |
| `right` | Input | The combination of year and month. |

### Parameters of Prototype 14

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of year and month. |
| `right` | Input | A signed number of years; in calendar arithmetic the other fields are preserved. |

### Parameters of Prototype 15

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of years; in calendar arithmetic the other fields are preserved. |
| `right` | Input | The combination of year and month. |

### Parameters of Prototype 16

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Year, month, and day fields; operates field by field and does not automatically correct invalid dates. |
| `right` | Input | A signed number of months; in calendar arithmetic it carries into the year every 12 months. |

### Parameters of Prototype 17

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of months; in calendar arithmetic it carries into the year every 12 months. |
| `right` | Input | Year, month, and day fields; operates field by field and does not automatically correct invalid dates. |

### Parameters of Prototype 18

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Year, month, and day fields; operates field by field and does not automatically correct invalid dates. |
| `right` | Input | A signed number of years; in calendar arithmetic the other fields are preserved. |

### Parameters of Prototype 19

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of years; in calendar arithmetic the other fields are preserved. |
| `right` | Input | Year, month, and day fields; operates field by field and does not automatically correct invalid dates. |

### Parameters of Prototype 20

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The last day of a month of a year. |
| `right` | Input | A signed number of months; in calendar arithmetic it carries into the year every 12 months. |

### Parameters of Prototype 21

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of months; in calendar arithmetic it carries into the year every 12 months. |
| `right` | Input | The last day of a month of a year. |

### Parameters of Prototype 22

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The last day of a month of a year. |
| `right` | Input | A signed number of years; in calendar arithmetic the other fields are preserved. |

### Parameters of Prototype 23

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of years; in calendar arithmetic the other fields are preserved. |
| `right` | Input | The last day of a month of a year. |

### Parameters of Prototype 24

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The n-th occurrence of a specified weekday in a month of a year. |
| `right` | Input | A signed number of months; in calendar arithmetic it carries into the year every 12 months. |

### Parameters of Prototype 25

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of months; in calendar arithmetic it carries into the year every 12 months. |
| `right` | Input | The n-th occurrence of a specified weekday in a month of a year. |

### Parameters of Prototype 26

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The n-th occurrence of a specified weekday in a month of a year. |
| `right` | Input | A signed number of years; in calendar arithmetic the other fields are preserved. |

### Parameters of Prototype 27

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of years; in calendar arithmetic the other fields are preserved. |
| `right` | Input | The n-th occurrence of a specified weekday in a month of a year. |

### Parameters of Prototype 28

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The last occurrence of a specified weekday in a month of a year. |
| `right` | Input | A signed number of months; in calendar arithmetic it carries into the year every 12 months. |

### Parameters of Prototype 29

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of months; in calendar arithmetic it carries into the year every 12 months. |
| `right` | Input | The last occurrence of a specified weekday in a month of a year. |

### Parameters of Prototype 30

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The last occurrence of a specified weekday in a month of a year. |
| `right` | Input | A signed number of years; in calendar arithmetic the other fields are preserved. |

### Parameters of Prototype 31

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | A signed number of years; in calendar arithmetic the other fields are preserved. |
| `right` | Input | The last occurrence of a specified weekday in a month of a year. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `common_type_t<duration, duration<Rep2, Period2>>` | The duration uses the common period and count type; a time point difference returns the common duration. |
| Prototype 2 | `time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>>` | Offsets the time point by the duration, preserving the Clock; the result duration uses the common precision. |
| Prototype 3 | `time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>>` | Offsets the time point by the duration, preserving the Clock; the result duration uses the common precision. |
| Prototype 4 | `day` | Offsets the field by the corresponding number of years or days without supplementing other calendar fields; the result must satisfy the representability requirement. |
| Prototype 5 | `day` | Offsets the field by the corresponding number of years or days without supplementing other calendar fields; the result must satisfy the representability requirement. |
| Prototype 6 | `month` | Wraps around every 12 months; the result is a month field of 1 to 12 and does not record the carry into years. |
| Prototype 7 | `month` | Wraps around every 12 months; the result is a month field of 1 to 12 and does not record the carry into years. |
| Prototype 8 | `weekday` | Wraps around every 7 days; the result is a weekday field of 0 to 6. |
| Prototype 9 | `weekday` | Wraps around every 7 days; the result is a weekday field of 0 to 6. |
| Prototype 10 | `year` | Offsets the field by the corresponding number of years or days without supplementing other calendar fields; the result must satisfy the representability requirement. |
| Prototype 11 | `year` | Offsets the field by the corresponding number of years or days without supplementing other calendar fields; the result must satisfy the representability requirement. |
| Prototype 12 | `year_month` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 13 | `year_month` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 14 | `year_month` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 15 | `year_month` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 16 | `year_month_day` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 17 | `year_month_day` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 18 | `year_month_day` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 19 | `year_month_day` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 20 | `year_month_day_last` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 21 | `year_month_day_last` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 22 | `year_month_day_last` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 23 | `year_month_day_last` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 24 | `year_month_weekday` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 25 | `year_month_weekday` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 26 | `year_month_weekday` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 27 | `year_month_weekday` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 28 | `year_month_weekday_last` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 29 | `year_month_weekday_last` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 30 | `year_month_weekday_last` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |
| Prototype 31 | `year_month_weekday_last` | Offsets the combined fields by months or years; the other fields or the month-end tag remain unchanged, and the resulting date may be invalid and must be checked with ok(). |

## Constraints

- Counts and intermediate operations must be representable.
- Calendar arithmetic does not implicitly correct invalid dates; whether the result is valid is determined by the `ok()` of the corresponding type.
- Two time points can be operated on or compared only under the same Clock.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/chrono>

bool example()
{
    const auto elapsed = asc::std::chrono::seconds{2} + asc::std::chrono::milliseconds{500};
    const auto date = (asc::std::chrono::year{2024} / asc::std::chrono::month{12}
        / asc::std::chrono::day{15}) + asc::std::chrono::months{1};
    return elapsed.count() == 2500 && static_cast<int>(date.year()) == 2025
        && static_cast<unsigned>(date.month()) == 1 && static_cast<unsigned>(date.day()) == 15;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
