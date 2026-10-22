# asc::std::chrono::weekday::weekday

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

`asc::std::chrono::weekday::weekday` initializes a `weekday` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

### Prototype 1

```cpp
constexpr weekday();
```

### Prototype 2

```cpp
explicit constexpr weekday(const local_days& value) noexcept;
```

### Prototype 3

```cpp
constexpr weekday(const sys_days& value) noexcept;
```

### Prototype 4

```cpp
explicit constexpr weekday(const unsigned int value) noexcept;
```

### Prototype 5

```cpp
constexpr weekday(const weekday& value) noexcept;
```

### Prototype 6

```cpp
constexpr weekday(weekday&& value) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The number of days of a time point expressed in local-time-zone days; the corresponding weekday (0 to 6) is derived to construct the object. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | A date expressed as system time point days (sys_days); the corresponding weekday is derived to construct the object. |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The weekday value; 0 to 6 are valid and 0 denotes Sunday; the integer 7 is normalized to 0 (Sunday), so ok() is true; other stored values outside 0 to 6 are invalid. |

### Parameters of Prototype 5

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The weekday object used for copy construction. |

### Parameters of Prototype 6

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The weekday object used for move construction; the implicit move of these scalar fields preserves the source field values. |

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
    asc::std::chrono::weekday value{4};
    return value.c_encoding() == 4;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
