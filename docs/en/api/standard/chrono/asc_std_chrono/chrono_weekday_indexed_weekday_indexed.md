# asc::std::chrono::weekday_indexed::weekday_indexed

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

`asc::std::chrono::weekday_indexed::weekday_indexed` initializes a `weekday_indexed` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

### Prototype 1

```cpp
constexpr weekday_indexed();
```

### Prototype 2

```cpp
constexpr weekday_indexed(const chrono::weekday& weekday_value, unsigned int index) noexcept;
```

### Prototype 3

```cpp
constexpr weekday_indexed(const weekday_indexed& weekday_value);
```

### Prototype 4

```cpp
constexpr weekday_indexed(weekday_indexed&& weekday_value);
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `weekday_value` | Input | The weekday value; 0 to 6 are valid and 0 denotes Sunday; 7 to 255 can also be stored, but ok() returns false for them. |
| `index` | Input | The nth weekday of the month; 1 to 5 are valid; 0 can also be stored, but ok() returns false for it. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `weekday_value` | Input | The weekday_indexed object used for copy construction. |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `weekday_value` | Input | The weekday_indexed object used for move construction; the implicit moves of these scalar fields keep the source field values. |

## Return Value

No return value.

## Constraints

- Arithmetic on calendar fields and timekeeping values can be used on the Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::weekday_indexed value{asc::std::chrono::weekday{4}, 4};
    return value.index() == 4 && value.weekday().c_encoding() == 4;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
