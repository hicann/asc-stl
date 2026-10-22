# asc::std::chrono::year_month_day_last::year_month_day_last

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

`asc::std::chrono::year_month_day_last::year_month_day_last` initializes a `year_month_day_last` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

### Prototype 1

```cpp
constexpr year_month_day_last(const chrono::year& year_value, const chrono::month_day_last& month_day_value) noexcept;
```

### Prototype 2

```cpp
constexpr year_month_day_last(const year_month_day_last& year_value);
```

### Prototype 3

```cpp
constexpr year_month_day_last(year_month_day_last&& year_value);
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `year_value` | Input | The year value; -32767 to 32767 is the valid range, and positive values denote AD years. |
| `month_day_value` | Input | The month-end tag (month_day_last), denoting a month and its last day. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `year_value` | Input | The year_month_day_last object used for copy construction. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `year_value` | Input | The year_month_day_last object used for move construction; the implicit move of these scalar fields preserves the source field values. |

## Return Value

No return value.

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::year_month_day_last value{asc::std::chrono::year{2024}, asc::std::chrono::month_day_last{asc::std::chrono::month{2}}};
    return static_cast<unsigned int>(value.day()) == 29;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
