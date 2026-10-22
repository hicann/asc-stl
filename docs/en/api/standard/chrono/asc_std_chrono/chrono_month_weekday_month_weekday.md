# asc::std::chrono::month_weekday::month_weekday

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

`asc::std::chrono::month_weekday::month_weekday` initializes a `month_weekday` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

### Prototype 1

```cpp
constexpr month_weekday();
```

### Prototype 2

```cpp
constexpr month_weekday(const chrono::month& month_value, const chrono::weekday_indexed& weekday_value) noexcept;
```

### Prototype 3

```cpp
constexpr month_weekday(const month_weekday& month_value);
```

### Prototype 4

```cpp
constexpr month_weekday(month_weekday&& month_value);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `month_value` | Input | The month value, with 1 to 12 denoting January to December. |
| `weekday_value` | Input | The indexed weekday description (weekday_indexed), specifying the nth given weekday of that month. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `month_value` | Input | The month_weekday object used for copy construction. |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `month_value` | Input | The month_weekday object used for move construction; the implicit move of these scalar fields preserves the source field values. |

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
    asc::std::chrono::month_weekday value{asc::std::chrono::month{2}, asc::std::chrono::weekday_indexed{asc::std::chrono::weekday{4}, 4}};
    return value.weekday_indexed().index() == 4;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
