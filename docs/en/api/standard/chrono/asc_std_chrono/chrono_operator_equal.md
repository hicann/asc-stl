# asc::std::chrono::`operator==`

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

`asc::std::chrono::operator==` compares durations, time points of the same Clock, or the listed calendar fields for the `==` relation.

Duration semantics are described in [`duration`](chrono_duration.md). Calendar validity is determined by the corresponding type's `ok()`.

## Function Prototype

Called as `left == right`; hidden friends participate through argument-dependent lookup and must not be relied on via qualified namespace lookup.

### Prototype 1

Member of: [`duration<Rep, Period>`](chrono_duration.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr bool operator==(const duration& left, const duration<Rep2, Period2>& right);
```

### Prototype 2

Member of: [`time_point<Clock, Duration>`](chrono_time_point.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
template <class Duration2>
[[nodiscard]] friend constexpr bool operator==(const time_point& left, const time_point<Clock, Duration2>& right);
```

### Prototype 3

Member of: [`day`](chrono_day.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const day& left, const day& right) noexcept;
```

### Prototype 4

Member of: [`month`](chrono_month.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const month& left, const month& right) noexcept;
```

### Prototype 5

Member of: [`weekday`](chrono_weekday.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const weekday& left, const weekday& right) noexcept;
```

### Prototype 6

Member of: [`weekday_indexed`](chrono_weekday_indexed.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const weekday_indexed& left, const weekday_indexed& right) noexcept;
```

### Prototype 7

Member of: [`weekday_last`](chrono_weekday_last.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const weekday_last& left, const weekday_last& right) noexcept;
```

### Prototype 8

Member of: [`year`](chrono_year.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const year& left, const year& right) noexcept;
```

### Prototype 9

Member of: [`month_day`](chrono_month_day.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const month_day& left, const month_day& right) noexcept;
```

### Prototype 10

Member of: [`month_day_last`](chrono_month_day_last.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const month_day_last& left, const month_day_last& right) noexcept;
```

### Prototype 11

Member of: [`month_weekday`](chrono_month_weekday.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const month_weekday& left, const month_weekday& right) noexcept;
```

### Prototype 12

Member of: [`month_weekday_last`](chrono_month_weekday_last.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const month_weekday_last& left, const month_weekday_last& right) noexcept;
```

### Prototype 13

Member of: [`year_month`](chrono_year_month.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const year_month& left, const year_month& right) noexcept;
```

### Prototype 14

Member of: [`year_month_day`](chrono_year_month_day.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const year_month_day& left, const year_month_day& right) noexcept;
```

### Prototype 15

Member of: [`year_month_day_last`](chrono_year_month_day_last.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const year_month_day_last& left, const year_month_day_last& right) noexcept;
```

### Prototype 16

Member of: [`year_month_weekday`](chrono_year_month_weekday.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const year_month_weekday& left, const year_month_weekday& right) noexcept;
```

### Prototype 17

Member of: [`year_month_weekday_last`](chrono_year_month_weekday_last.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
[[nodiscard]] friend constexpr bool operator==(const year_month_weekday_last& left, const year_month_weekday_last& right) noexcept;
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
| `Duration2` | The duration type stored by the other time point; the two time points have the same Clock. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The time point; it takes part in comparison or offset under the same Clock, and the result precision is determined by the common duration. |
| `right` | Input | The time point; it takes part in comparison or offset under the same Clock, and the result precision is determined by the common duration. |

### Parameters of Prototype 3

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The day field, usually 1 to 31; it carries no month or year. |
| `right` | Input | The day field, usually 1 to 31; it carries no month or year. |

### Parameters of Prototype 4

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The month field, with 1 to 12 denoting January to December. |
| `right` | Input | The month field, with 1 to 12 denoting January to December. |

### Parameters of Prototype 5

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The weekday field, where the C encoding has 0 as Sunday and 1 to 6 as Monday to Saturday. |
| `right` | Input | The weekday field, where the C encoding has 0 as Sunday and 1 to 6 as Monday to Saturday. |

### Parameters of Prototype 6

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a weekday and an index within the month; the index 1 to 5 denotes the nth occurrence of that weekday. |
| `right` | Input | The combination of a weekday and an index within the month; the index 1 to 5 denotes the nth occurrence of that weekday. |

### Parameters of Prototype 7

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The specified weekday occurring last in the month. |
| `right` | Input | The specified weekday occurring last in the month. |

### Parameters of Prototype 8

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The year field, with a valid range of -32767 to 32767. |
| `right` | Input | The year field, with a valid range of -32767 to 32767. |

### Parameters of Prototype 9

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of the month and day fields, without a year. |
| `right` | Input | The combination of the month and day fields, without a year. |

### Parameters of Prototype 10

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The tag combination for the last day of a month. |
| `right` | Input | The tag combination for the last day of a month. |

### Parameters of Prototype 11

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a month and the nth weekday. |
| `right` | Input | The combination of a month and the nth weekday. |

### Parameters of Prototype 12

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a month and the last specified weekday. |
| `right` | Input | The combination of a month and the last specified weekday. |

### Parameters of Prototype 13

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a year and a month. |
| `right` | Input | The combination of a year and a month. |

### Parameters of Prototype 14

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The year, month, and day fields; operated on field by field, without automatically correcting invalid dates. |
| `right` | Input | The year, month, and day fields; operated on field by field, without automatically correcting invalid dates. |

### Parameters of Prototype 15

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The last day of a given month of a given year. |
| `right` | Input | The last day of a given month of a given year. |

### Parameters of Prototype 16

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The nth specified weekday of a given month of a given year. |
| `right` | Input | The nth specified weekday of a given month of a given year. |

### Parameters of Prototype 17

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The last specified weekday of a given month of a given year. |
| `right` | Input | The last specified weekday of a given month of a given year. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `bool` | Compares the two counts at the common timekeeping period, determining the shown relation. |
| Prototype 2 | `bool` | Compares the time_since_epoch() durations under the same Clock, determining the shown relation. |
| Prototype 3 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 4 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 5 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 6 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 7 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 8 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 9 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 10 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 11 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 12 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 13 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 14 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 15 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 16 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |
| Prototype 17 | `bool` | Compares the stored corresponding calendar fields; combined fields determine the relation in year, month, day, or weekday member order, without converting to a timestamp. |

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
    const asc::std::chrono::seconds left{1};
    const asc::std::chrono::milliseconds right{1000};
    const auto earlier = asc::std::chrono::year{2024} / asc::std::chrono::month{2};
    const auto later = asc::std::chrono::year{2024} / asc::std::chrono::month{3};
    return (left == right) == true && (earlier == later) == false;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
