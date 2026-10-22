# asc::std::chrono::`operator/`

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

`asc::std::chrono::operator/` divides durations, or assembles month-day, year-month, full-date, and nth/last weekday descriptions from calendar fields.

Duration semantics are described in [`duration`](chrono_duration.md). Calendar validity is determined by the corresponding type's `ok()`.

## Function Prototype

Called as `left / right`; hidden friends participate through argument-dependent lookup and must not be relied on via qualified namespace lookup.

### Prototype 1

Member of: [`duration<Rep, Period>`](chrono_duration.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type. The declaration summary omits implementation parameters used only for overload selection: `Rep2` must not be a `duration`, and `const Rep2&` must be convertible to `common_type_t<Rep, Rep2>`.

```cpp
template <class Rep2>
[[nodiscard]] friend constexpr duration<common_type_t<Rep, Rep2>, Period> operator/(const duration& left, const Rep2& right);
```

### Prototype 2

Member of: [`duration<Rep, Period>`](chrono_duration.md). The following is a hidden friend declaration inside the class; class template parameters (if any) are provided by the enclosing type.

```cpp
template <class Rep2, class Period2>
[[nodiscard]] friend constexpr common_type_t<Rep, Rep2> operator/(const duration& left, const duration<Rep2, Period2>& right);
```

### Prototype 3

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_day operator/(const chrono::month& left, const chrono::day& right) noexcept;
```

### Prototype 4

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_day operator/(const chrono::day& left, const chrono::month& right) noexcept;
```

### Prototype 5

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_day operator/(const chrono::month& left, int right) noexcept;
```

### Prototype 6

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_day operator/(int left, const chrono::day& right) noexcept;
```

### Prototype 7

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_day operator/(const chrono::day& left, int right) noexcept;
```

### Prototype 8

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_day_last operator/(const chrono::month& left, last_spec right) noexcept;
```

### Prototype 9

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_day_last operator/(last_spec left, const chrono::month& right) noexcept;
```

### Prototype 10

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_day_last operator/(int left, last_spec right) noexcept;
```

### Prototype 11

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_day_last operator/(last_spec left, int right) noexcept;
```

### Prototype 12

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_weekday operator/(const chrono::month& left, const chrono::weekday_indexed& right) noexcept;
```

### Prototype 13

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_weekday operator/(int left, const chrono::weekday_indexed& right) noexcept;
```

### Prototype 14

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_weekday operator/(const chrono::weekday_indexed& left, const chrono::month& right) noexcept;
```

### Prototype 15

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_weekday operator/(const chrono::weekday_indexed& left, int right) noexcept;
```

### Prototype 16

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_weekday_last operator/(const chrono::month& left, const chrono::weekday_last& right) noexcept;
```

### Prototype 17

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_weekday_last operator/(int left, const chrono::weekday_last& right) noexcept;
```

### Prototype 18

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_weekday_last operator/(const chrono::weekday_last& left, const chrono::month& right) noexcept;
```

### Prototype 19

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr month_weekday_last operator/(const chrono::weekday_last& left, int right) noexcept;
```

### Prototype 20

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month operator/(const chrono::year& left, const chrono::month& right) noexcept;
```

### Prototype 21

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month operator/(const chrono::year& left, int right) noexcept;
```

### Prototype 22

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day operator/(const year_month& left, const day& right) noexcept;
```

### Prototype 23

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day operator/(const year_month& left, int right) noexcept;
```

### Prototype 24

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day operator/(const year& left, const month_day& right) noexcept;
```

### Prototype 25

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day operator/(int left, const month_day& right) noexcept;
```

### Prototype 26

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day operator/(const month_day& left, const year& right) noexcept;
```

### Prototype 27

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day operator/(const month_day& left, int right) noexcept;
```

### Prototype 28

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day_last operator/(const year_month& left, last_spec right) noexcept;
```

### Prototype 29

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day_last operator/(const year& left, const month_day_last& right) noexcept;
```

### Prototype 30

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day_last operator/(int left, const month_day_last& right) noexcept;
```

### Prototype 31

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day_last operator/(const month_day_last& left, const year& right) noexcept;
```

### Prototype 32

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_day_last operator/(const month_day_last& left, int right) noexcept;
```

### Prototype 33

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday operator/(const year_month& left, const weekday_indexed& right) noexcept;
```

### Prototype 34

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday operator/(const year& left, const month_weekday& right) noexcept;
```

### Prototype 35

Located in the `asc::std::chrono` namespace.

```cpp
constexpr year_month_weekday operator/(int left, const month_weekday& right) noexcept;
```

### Prototype 36

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday operator/(const month_weekday& left, const year& right) noexcept;
```

### Prototype 37

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday operator/(const month_weekday& left, int right) noexcept;
```

### Prototype 38

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator/(const year_month& left, const weekday_last& right) noexcept;
```

### Prototype 39

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator/(const year& left, const month_weekday_last& right) noexcept;
```

### Prototype 40

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator/(int left, const month_weekday_last& right) noexcept;
```

### Prototype 41

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator/(const month_weekday_last& left, const year& right) noexcept;
```

### Prototype 42

Located in the `asc::std::chrono` namespace.

```cpp
[[nodiscard]] constexpr year_month_weekday_last operator/(const month_weekday_last& left, int right) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep2` | The count or scalar representation type of the other operand; forms a common count type with Rep. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The duration value; the unit of its count is determined by its period, and arithmetic with another duration first forms a common timekeeping period. |
| `right` | Input | The divisor; it must be convertible to the common count type, and modulo additionally requires support for the remainder operation. |

### Parameters of Prototype 2

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

### Parameters of Prototype 3

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The month field, with 1 to 12 denoting January to December. |
| `right` | Input | The day field, usually 1 to 31; it carries no month or year. |

### Parameters of Prototype 4

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The day field, usually 1 to 31; it carries no month or year. |
| `right` | Input | The month field, with 1 to 12 denoting January to December. |

### Parameters of Prototype 5

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The month field, with 1 to 12 denoting January to December. |
| `right` | Input | An integer value constructed as the day field; its valid domain is the same as the corresponding calendar field. |

### Parameters of Prototype 6

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | An integer value constructed as the month field; its valid domain is the same as the corresponding calendar field. |
| `right` | Input | The day field, usually 1 to 31; it carries no month or year. |

### Parameters of Prototype 7

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The day field, usually 1 to 31; it carries no month or year. |
| `right` | Input | An integer value constructed as the month field; its valid domain is the same as the corresponding calendar field. |

### Parameters of Prototype 8

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The month field, with 1 to 12 denoting January to December. |
| `right` | Input | The end-of-month tag; it stores no concrete day count or weekday. |

### Parameters of Prototype 9

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The end-of-month tag; it stores no concrete day count or weekday. |
| `right` | Input | The month field, with 1 to 12 denoting January to December. |

### Parameters of Prototype 10

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | An integer value constructed as the month field; its valid domain is the same as the corresponding calendar field. |
| `right` | Input | The end-of-month tag; it stores no concrete day count or weekday. |

### Parameters of Prototype 11

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The end-of-month tag; it stores no concrete day count or weekday. |
| `right` | Input | An integer value constructed as the month field; its valid domain is the same as the corresponding calendar field. |

### Parameters of Prototype 12

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The month field, with 1 to 12 denoting January to December. |
| `right` | Input | The combination of a weekday and an index within the month; the index 1 to 5 denotes the nth occurrence of that weekday. |

### Parameters of Prototype 13

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | An integer value constructed as the month field; its valid domain is the same as the corresponding calendar field. |
| `right` | Input | The combination of a weekday and an index within the month; the index 1 to 5 denotes the nth occurrence of that weekday. |

### Parameters of Prototype 14

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a weekday and an index within the month; the index 1 to 5 denotes the nth occurrence of that weekday. |
| `right` | Input | The month field, with 1 to 12 denoting January to December. |

### Parameters of Prototype 15

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a weekday and an index within the month; the index 1 to 5 denotes the nth occurrence of that weekday. |
| `right` | Input | An integer value constructed as the month field; its valid domain is the same as the corresponding calendar field. |

### Parameters of Prototype 16

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The month field, with 1 to 12 denoting January to December. |
| `right` | Input | The specified weekday occurring last in the month. |

### Parameters of Prototype 17

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | An integer value constructed as the month field; its valid domain is the same as the corresponding calendar field. |
| `right` | Input | The specified weekday occurring last in the month. |

### Parameters of Prototype 18

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The specified weekday occurring last in the month. |
| `right` | Input | The month field, with 1 to 12 denoting January to December. |

### Parameters of Prototype 19

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The specified weekday occurring last in the month. |
| `right` | Input | An integer value constructed as the month field; its valid domain is the same as the corresponding calendar field. |

### Parameters of Prototype 20

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The year field, with a valid range of -32767 to 32767. |
| `right` | Input | The month field, with 1 to 12 denoting January to December. |

### Parameters of Prototype 21

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The year field, with a valid range of -32767 to 32767. |
| `right` | Input | An integer value constructed as the month field; its valid domain is the same as the corresponding calendar field. |

### Parameters of Prototype 22

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a year and a month. |
| `right` | Input | The day field, usually 1 to 31; it carries no month or year. |

### Parameters of Prototype 23

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a year and a month. |
| `right` | Input | An integer value constructed as the day field; its valid domain is the same as the corresponding calendar field. |

### Parameters of Prototype 24

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The year field, with a valid range of -32767 to 32767. |
| `right` | Input | The combination of the month and day fields, without a year. |

### Parameters of Prototype 25

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | An integer value constructed as the year field; its valid domain is the same as the corresponding calendar field. |
| `right` | Input | The combination of the month and day fields, without a year. |

### Parameters of Prototype 26

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of the month and day fields, without a year. |
| `right` | Input | The year field, with a valid range of -32767 to 32767. |

### Parameters of Prototype 27

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of the month and day fields, without a year. |
| `right` | Input | An integer value constructed as the year field; its valid domain is the same as the corresponding calendar field. |

### Parameters of Prototype 28

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a year and a month. |
| `right` | Input | The end-of-month tag; it stores no concrete day count or weekday. |

### Parameters of Prototype 29

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The year field, with a valid range of -32767 to 32767. |
| `right` | Input | The tag combination for the last day of a month. |

### Parameters of Prototype 30

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | An integer value constructed as the year field; its valid domain is the same as the corresponding calendar field. |
| `right` | Input | The tag combination for the last day of a month. |

### Parameters of Prototype 31

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The tag combination for the last day of a month. |
| `right` | Input | The year field, with a valid range of -32767 to 32767. |

### Parameters of Prototype 32

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The tag combination for the last day of a month. |
| `right` | Input | An integer value constructed as the year field; its valid domain is the same as the corresponding calendar field. |

### Parameters of Prototype 33

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a year and a month. |
| `right` | Input | The combination of a weekday and an index within the month; the index 1 to 5 denotes the nth occurrence of that weekday. |

### Parameters of Prototype 34

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The year field, with a valid range of -32767 to 32767. |
| `right` | Input | The combination of a month and the nth weekday. |

### Parameters of Prototype 35

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | An integer value constructed as the year field; its valid domain is the same as the corresponding calendar field. |
| `right` | Input | The combination of a month and the nth weekday. |

### Parameters of Prototype 36

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a month and the nth weekday. |
| `right` | Input | The year field, with a valid range of -32767 to 32767. |

### Parameters of Prototype 37

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a month and the nth weekday. |
| `right` | Input | An integer value constructed as the year field; its valid domain is the same as the corresponding calendar field. |

### Parameters of Prototype 38

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a year and a month. |
| `right` | Input | The specified weekday occurring last in the month. |

### Parameters of Prototype 39

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The year field, with a valid range of -32767 to 32767. |
| `right` | Input | The combination of a month and the last specified weekday. |

### Parameters of Prototype 40

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | An integer value constructed as the year field; its valid domain is the same as the corresponding calendar field. |
| `right` | Input | The combination of a month and the last specified weekday. |

### Parameters of Prototype 41

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a month and the last specified weekday. |
| `right` | Input | The year field, with a valid range of -32767 to 32767. |

### Parameters of Prototype 42

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The combination of a month and the last specified weekday. |
| `right` | Input | An integer value constructed as the year field; its valid domain is the same as the corresponding calendar field. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `duration<common_type_t<Rep, Rep2>, Period>` | Divides the duration count by a scalar, returning a duration that keeps the original period. |
| Prototype 2 | `common_type_t<Rep, Rep2>` | Converts both durations to the common period and divides, returning the dimensionless quotient of the common count type. |
| Prototype 3 | `month_day` | Assembles the calendar fields or tags on both sides into a month_day; no numeric division is performed. |
| Prototype 4 | `month_day` | Assembles the calendar fields or tags on both sides into a month_day; no numeric division is performed. |
| Prototype 5 | `month_day` | Assembles the calendar fields or tags on both sides into a month_day; no numeric division is performed. |
| Prototype 6 | `month_day` | Assembles the calendar fields or tags on both sides into a month_day; no numeric division is performed. |
| Prototype 7 | `month_day` | Assembles the calendar fields or tags on both sides into a month_day; no numeric division is performed. |
| Prototype 8 | `month_day_last` | Assembles the calendar fields or tags on both sides into a month_day_last; no numeric division is performed. |
| Prototype 9 | `month_day_last` | Assembles the calendar fields or tags on both sides into a month_day_last; no numeric division is performed. |
| Prototype 10 | `month_day_last` | Assembles the calendar fields or tags on both sides into a month_day_last; no numeric division is performed. |
| Prototype 11 | `month_day_last` | Assembles the calendar fields or tags on both sides into a month_day_last; no numeric division is performed. |
| Prototype 12 | `month_weekday` | Assembles the calendar fields or tags on both sides into a month_weekday; no numeric division is performed. |
| Prototype 13 | `month_weekday` | Assembles the calendar fields or tags on both sides into a month_weekday; no numeric division is performed. |
| Prototype 14 | `month_weekday` | Assembles the calendar fields or tags on both sides into a month_weekday; no numeric division is performed. |
| Prototype 15 | `month_weekday` | Assembles the calendar fields or tags on both sides into a month_weekday; no numeric division is performed. |
| Prototype 16 | `month_weekday_last` | Assembles the calendar fields or tags on both sides into a month_weekday_last; no numeric division is performed. |
| Prototype 17 | `month_weekday_last` | Assembles the calendar fields or tags on both sides into a month_weekday_last; no numeric division is performed. |
| Prototype 18 | `month_weekday_last` | Assembles the calendar fields or tags on both sides into a month_weekday_last; no numeric division is performed. |
| Prototype 19 | `month_weekday_last` | Assembles the calendar fields or tags on both sides into a month_weekday_last; no numeric division is performed. |
| Prototype 20 | `year_month` | Assembles the calendar fields or tags on both sides into a year_month; no numeric division is performed. |
| Prototype 21 | `year_month` | Assembles the calendar fields or tags on both sides into a year_month; no numeric division is performed. |
| Prototype 22 | `year_month_day` | Assembles the calendar fields or tags on both sides into a year_month_day; no numeric division is performed. |
| Prototype 23 | `year_month_day` | Assembles the calendar fields or tags on both sides into a year_month_day; no numeric division is performed. |
| Prototype 24 | `year_month_day` | Assembles the calendar fields or tags on both sides into a year_month_day; no numeric division is performed. |
| Prototype 25 | `year_month_day` | Assembles the calendar fields or tags on both sides into a year_month_day; no numeric division is performed. |
| Prototype 26 | `year_month_day` | Assembles the calendar fields or tags on both sides into a year_month_day; no numeric division is performed. |
| Prototype 27 | `year_month_day` | Assembles the calendar fields or tags on both sides into a year_month_day; no numeric division is performed. |
| Prototype 28 | `year_month_day_last` | Assembles the calendar fields or tags on both sides into a year_month_day_last; no numeric division is performed. |
| Prototype 29 | `year_month_day_last` | Assembles the calendar fields or tags on both sides into a year_month_day_last; no numeric division is performed. |
| Prototype 30 | `year_month_day_last` | Assembles the calendar fields or tags on both sides into a year_month_day_last; no numeric division is performed. |
| Prototype 31 | `year_month_day_last` | Assembles the calendar fields or tags on both sides into a year_month_day_last; no numeric division is performed. |
| Prototype 32 | `year_month_day_last` | Assembles the calendar fields or tags on both sides into a year_month_day_last; no numeric division is performed. |
| Prototype 33 | `year_month_weekday` | Assembles the calendar fields or tags on both sides into a year_month_weekday; no numeric division is performed. |
| Prototype 34 | `year_month_weekday` | Assembles the calendar fields or tags on both sides into a year_month_weekday; no numeric division is performed. |
| Prototype 35 | `year_month_weekday` | Assembles the calendar fields or tags on both sides into a year_month_weekday; no numeric division is performed. |
| Prototype 36 | `year_month_weekday` | Assembles the calendar fields or tags on both sides into a year_month_weekday; no numeric division is performed. |
| Prototype 37 | `year_month_weekday` | Assembles the calendar fields or tags on both sides into a year_month_weekday; no numeric division is performed. |
| Prototype 38 | `year_month_weekday_last` | Assembles the calendar fields or tags on both sides into a year_month_weekday_last; no numeric division is performed. |
| Prototype 39 | `year_month_weekday_last` | Assembles the calendar fields or tags on both sides into a year_month_weekday_last; no numeric division is performed. |
| Prototype 40 | `year_month_weekday_last` | Assembles the calendar fields or tags on both sides into a year_month_weekday_last; no numeric division is performed. |
| Prototype 41 | `year_month_weekday_last` | Assembles the calendar fields or tags on both sides into a year_month_weekday_last; no numeric division is performed. |
| Prototype 42 | `year_month_weekday_last` | Assembles the calendar fields or tags on both sides into a year_month_weekday_last; no numeric division is performed. |

## Constraints

- The count and intermediate operations must be representable.
- Calendar arithmetic does not implicitly correct invalid dates; whether the result is valid is determined by the corresponding type's `ok()`.
- For integer counts, the current implementation treats a divisor that converts to 0 as 1; this is not the standard chrono guarantee for zero divisors. Use a non-zero divisor when standard portable semantics are required; must not be called when the signed minimum value divided by -1 is not representable.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/chrono>

bool example()
{
    const auto last_day = asc::std::chrono::year{2024} / asc::std::chrono::month{2}
        / asc::std::chrono::last;
    const auto ratio = asc::std::chrono::seconds{7} / asc::std::chrono::seconds{2};
    return ratio == 3 && static_cast<unsigned>(last_day.day()) == 29;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
