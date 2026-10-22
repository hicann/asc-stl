# asc::std::chrono::year_month_day::year_month_day

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

`asc::std::chrono::year_month_day::year_month_day` initializes a `year_month_day` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

### Prototype 1

```cpp
constexpr year_month_day();
```

### Prototype 2

```cpp
constexpr year_month_day(const chrono::year& year_value, const chrono::month& month_value, const chrono::day& day_value) noexcept;
```

### Prototype 3

```cpp
explicit constexpr year_month_day(const local_days& value) noexcept;
```

### Prototype 4

```cpp
constexpr year_month_day(const sys_days& value) noexcept;
```

### Prototype 5

```cpp
constexpr year_month_day(const year_month_day& other);
```

### Prototype 6

```cpp
constexpr year_month_day(const year_month_day_last& value) noexcept;
```

### Prototype 7

```cpp
constexpr year_month_day(year_month_day&& other) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `year_value` | Input | The year value; -32767 to 32767 is the valid range, and positive values denote AD years. |
| `month_value` | Input | The month value, where 1 to 12 denote January through December. |
| `day_value` | Input | The day value, where 1 to 31 denote a valid day; 0 and 32 to 255 can also be stored, but ok() evaluates to false. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | A day-precision local time point tagged with local_t; converted to year, month, and day purely from the epoch count, without querying or applying time zones (local_days). |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | A date expressed as system time point days (sys_days), converted to year, month, and day. |

### Parameters of Prototype 5

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The year_month_day object used for copy construction. |

### Parameters of Prototype 6

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | A date expressed as a year plus a month-end tag (year_month_day_last), taking the last day of that month. |

### Parameters of Prototype 7

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The year_month_day object used for move construction; the implicit move of these scalar fields preserves the source field values. |

## Return Value

No return value.

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.
- Before calling the month-end day query or a conversion that depends on it, the month field must be between 1 and 12; full validity can be checked with the ok() of the source object. An invalid month must not be used to query the month-length table.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::year_month_day value{asc::std::chrono::year{2024}, asc::std::chrono::month{2}, asc::std::chrono::day{29}};
    return static_cast<unsigned int>(value.day()) == 29;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
