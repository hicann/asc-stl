# asc::std::chrono::`operator-`

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

`asc::std::chrono::operator-` computes the difference of durations, time points, or calendar fields, or offsets forward by the given duration/days/months/years.

Duration semantics are described in [`duration`](chrono_duration.md). Calendar validity is determined by the corresponding type's `ok()`.

## Function Prototype

Called as `left - right`; hidden friends participate through argument-dependent lookup and must not be relied on via qualified namespace lookup.

### Prototype 1

Member of: [`duration<Rep, Period>`](chrono_duration.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr common_type_t<duration, duration<Rep2, Period2>> operator-(const duration& left, const duration<Rep2, Period2>& right);
```

### Prototype 2

Member of: [`time_point<Clock, Duration>`](chrono_time_point.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>> operator-(const time_point& left, const chrono::duration<Rep2, Period2>& right);
```

### Prototype 3

Member of: [`time_point<Clock, Duration>`](chrono_time_point.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
template <class Duration2>
[[nodiscard]] friend constexpr common_type_t<Duration, Duration2> operator-(const time_point& left, const time_point<Clock, Duration2>& right);
```

### Prototype 4

Member of: [`day`](chrono_day.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr day operator-(const day& left, const days& right) noexcept;
```

### Prototype 5

Member of: [`day`](chrono_day.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr days operator-(const day& left, const day& right) noexcept;
```

### Prototype 6

Member of: [`month`](chrono_month.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr month operator-(const month& left, const months& right) noexcept;
```

### Prototype 7

Member of: [`month`](chrono_month.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr months operator-(const month& left, const month& right) noexcept;
```

### Prototype 8

Member of: [`weekday`](chrono_weekday.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr days operator-(const weekday& left, const weekday& right) noexcept;
```

### Prototype 9

Member of: [`weekday`](chrono_weekday.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr weekday operator-(const weekday& left, const days& right) noexcept;
```

### Prototype 10

Member of: [`year`](chrono_year.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr year operator-(const year& left, const years& right) noexcept;
```

### Prototype 11

Member of: [`year`](chrono_year.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr years operator-(const year& left, const year& right) noexcept;
```

### Prototype 12

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr months operator-(const year_month& left, const year_month& right) noexcept;
```

### Prototype 13

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month operator-(const year_month& left, const months& right) noexcept;
```

### Prototype 14

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month operator-(const year_month& left, const years& right) noexcept;
```

### Prototype 15

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day operator-(const year_month_day& left, const months& right) noexcept;
```

### Prototype 16

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day operator-(const year_month_day& left, const years& right) noexcept;
```

### Prototype 17

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day_last operator-(const year_month_day_last& left, const months& right) noexcept;
```

### Prototype 18

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day_last operator-(const year_month_day_last& left, const years& right) noexcept;
```

### Prototype 19

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday operator-(const year_month_weekday& left, const months& right) noexcept;
```

### Prototype 20

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday operator-(const year_month_weekday& left, const years& right) noexcept;
```

### Prototype 21

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator-(const year_month_weekday_last& left, const months& right) noexcept;
```

### Prototype 22

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator-(const year_month_weekday_last& left, const years& right) noexcept;
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
| `left` | Input | The duration value; the unit of its count is determined by its period, and arithmetic with another duration first forms a common timekeeping period. |
| `right` | Input | The duration value; the unit of its count is determined by its period, and arithmetic with another duration first forms a common timekeeping period. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep2` | The count or scalar representation type of the other operand; forms a common count type with Rep. |
| `Period2` | The tick period of the other duration, a ratio type based on seconds. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The time point; it takes part in comparison or offset under the same Clock, and the result precision is determined by the common duration. |
| `right` | Input | The duration value; the unit of its count is determined by its period, and arithmetic with another duration first forms a common timekeeping period. |

### Parameters of Prototype 3

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Duration2` | The duration type stored by the other time point; the two time points have the same Clock. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The time point; it takes part in comparison or offset under the same Clock, and the result precision is determined by the common duration. |
| `right` | Input | The time point; it takes part in comparison or offset under the same Clock, and the result precision is determined by the common duration. |

### Parameters of Prototype 4

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The day field, usually 1 to 31; it carries no month or year. |
| `right` | Input | A signed number of days with a unit of 24 hours; when used for a field offset, it denotes the amount the day field moves. |

### Parameters of Prototype 5

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The day field, usually 1 to 31; it carries no month or year. |
| `right` | Input | The day field, usually 1 to 31; it carries no month or year. |

### Parameters of Prototype 6

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The month field, with 1 to 12 denoting January to December. |
| `right` | Input | A signed number of months; the result for a standalone month wraps around modulo 12 months and records no year carry. |

### Parameters of Prototype 7

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The month field, with 1 to 12 denoting January to December. |
| `right` | Input | The month field, with 1 to 12 denoting January to December. |

### Parameters of Prototype 8

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The weekday field, where the C encoding has 0 as Sunday and 1 to 6 as Monday to Saturday. |
| `right` | Input | The weekday field, where the C encoding has 0 as Sunday and 1 to 6 as Monday to Saturday. |

### Parameters of Prototype 9

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The weekday field, where the C encoding has 0 as Sunday and 1 to 6 as Monday to Saturday. |
| `right` | Input | A signed number of days with a unit of 24 hours; when used for a field offset, it denotes the amount the day field moves. |

### Parameters of Prototype 10

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The year field, with a valid range of -32767 to 32767. |
| `right` | Input | A signed number of years; when used in calendar arithmetic it keeps the other fields. |

### Parameters of Prototype 11

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The year field, with a valid range of -32767 to 32767. |
| `right` | Input | The year field, with a valid range of -32767 to 32767. |

### Parameters of Prototype 12

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a year and a month. |
| `right` | Input | The combination of a year and a month. |

### Parameters of Prototype 13

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a year and a month. |
| `right` | Input | A signed number of months; when used in calendar arithmetic it carries into the year in units of 12 months. |

### Parameters of Prototype 14

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a year and a month. |
| `right` | Input | A signed number of years; when used in calendar arithmetic it keeps the other fields. |

### Parameters of Prototype 15

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The year, month, and day fields; operated on field by field, without automatically correcting invalid dates. |
| `right` | Input | A signed number of months; when used in calendar arithmetic it carries into the year in units of 12 months. |

### Parameters of Prototype 16

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The year, month, and day fields; operated on field by field, without automatically correcting invalid dates. |
| `right` | Input | A signed number of years; when used in calendar arithmetic it keeps the other fields. |

### Parameters of Prototype 17

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The last day of a given month of a given year. |
| `right` | Input | A signed number of months; when used in calendar arithmetic it carries into the year in units of 12 months. |

### Parameters of Prototype 18

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The last day of a given month of a given year. |
| `right` | Input | A signed number of years; when used in calendar arithmetic it keeps the other fields. |

### Parameters of Prototype 19

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The nth specified weekday of a given month of a given year. |
| `right` | Input | A signed number of months; when used in calendar arithmetic it carries into the year in units of 12 months. |

### Parameters of Prototype 20

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The nth specified weekday of a given month of a given year. |
| `right` | Input | A signed number of years; when used in calendar arithmetic it keeps the other fields. |

### Parameters of Prototype 21

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The last specified weekday of a given month of a given year. |
| `right` | Input | A signed number of months; when used in calendar arithmetic it carries into the year in units of 12 months. |

### Parameters of Prototype 22

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The last specified weekday of a given month of a given year. |
| `right` | Input | A signed number of years; when used in calendar arithmetic it keeps the other fields. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `common_type_t<duration, duration<Rep2, Period2>>` | The durations use the common period and count type; the difference of time points returns the common duration. |
| Prototype 2 | `time_point<Clock, common_type_t<Duration, chrono::duration<Rep2, Period2>>>` | Offsets the time point by the duration, keeping the Clock, with the result duration at the common precision. |
| Prototype 3 | `common_type_t<Duration, Duration2>` | The durations use the common period and count type; the difference of time points returns the common duration. |
| Prototype 4 | `day` | Offsets the field by the corresponding number of years or days without supplementing other calendar fields; the result must satisfy the representability requirements. |
| Prototype 5 | `days` | Returns the signed difference between the two fields; the differences of month and weekday fall into 0 to 11 months and 0 to 6 days, respectively. |
| Prototype 6 | `month` | Wraps around modulo 12 months, with the result being a month field from 1 to 12 and no year carry recorded. |
| Prototype 7 | `months` | Returns the signed difference between the two fields; the differences of month and weekday fall into 0 to 11 months and 0 to 6 days, respectively. |
| Prototype 8 | `days` | Returns the signed difference between the two fields; the differences of month and weekday fall into 0 to 11 months and 0 to 6 days, respectively. |
| Prototype 9 | `weekday` | Wraps around modulo 7 days, with the result being a weekday field from 0 to 6. |
| Prototype 10 | `year` | Offsets the field by the corresponding number of years or days without supplementing other calendar fields; the result must satisfy the representability requirements. |
| Prototype 11 | `years` | Returns the signed difference between the two fields; the differences of month and weekday fall into 0 to 11 months and 0 to 6 days, respectively. |
| Prototype 12 | `months` | Returns the signed difference between the two fields; the differences of month and weekday fall into 0 to 11 months and 0 to 6 days, respectively. |
| Prototype 13 | `year_month` | Offsets the combined fields by months or years; the other fields or the end-of-month tag are unchanged, the resulting date may be invalid, and ok() must be used to check it. |
| Prototype 14 | `year_month` | Offsets the combined fields by months or years; the other fields or the end-of-month tag are unchanged, the resulting date may be invalid, and ok() must be used to check it. |
| Prototype 15 | `year_month_day` | Offsets the combined fields by months or years; the other fields or the end-of-month tag are unchanged, the resulting date may be invalid, and ok() must be used to check it. |
| Prototype 16 | `year_month_day` | Offsets the combined fields by months or years; the other fields or the end-of-month tag are unchanged, the resulting date may be invalid, and ok() must be used to check it. |
| Prototype 17 | `year_month_day_last` | Offsets the combined fields by months or years; the other fields or the end-of-month tag are unchanged, the resulting date may be invalid, and ok() must be used to check it. |
| Prototype 18 | `year_month_day_last` | Offsets the combined fields by months or years; the other fields or the end-of-month tag are unchanged, the resulting date may be invalid, and ok() must be used to check it. |
| Prototype 19 | `year_month_weekday` | Offsets the combined fields by months or years; the other fields or the end-of-month tag are unchanged, the resulting date may be invalid, and ok() must be used to check it. |
| Prototype 20 | `year_month_weekday` | Offsets the combined fields by months or years; the other fields or the end-of-month tag are unchanged, the resulting date may be invalid, and ok() must be used to check it. |
| Prototype 21 | `year_month_weekday_last` | Offsets the combined fields by months or years; the other fields or the end-of-month tag are unchanged, the resulting date may be invalid, and ok() must be used to check it. |
| Prototype 22 | `year_month_weekday_last` | Offsets the combined fields by months or years; the other fields or the end-of-month tag are unchanged, the resulting date may be invalid, and ok() must be used to check it. |

## Constraints

- The count and intermediate operations must be representable.
- Calendar arithmetic does not implicitly correct invalid dates; whether the result is valid is determined by the corresponding type's `ok()`.
- Two time points can be operated on or compared only under the same Clock.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/chrono>

bool example()
{
    const asc::std::chrono::sys_seconds end{asc::std::chrono::seconds{7}};
    const asc::std::chrono::sys_seconds begin{asc::std::chrono::seconds{2}};
    const auto difference = end - begin;
    const auto previous = asc::std::chrono::month{1} - asc::std::chrono::months{1};
    return difference.count() == 5 && static_cast<unsigned>(previous) == 12;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
