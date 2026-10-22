# asc::std::chrono::day::day

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

`asc::std::chrono::day::day` initializes a `day` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

### Prototype 1

```cpp
constexpr day();
```

### Prototype 2

```cpp
constexpr day(const day& value) noexcept;
```

### Prototype 3

```cpp
constexpr day(day&& value) noexcept;
```

### Prototype 4

```cpp
explicit constexpr day(unsigned int value) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The day object used for copy construction. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The day object used for move construction; the implicit move of these scalar fields preserves the source field values. |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The day value, where 1 to 31 denote a valid day; 0 and 32 to 255 can also be stored, but ok() evaluates to false. |

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
    asc::std::chrono::day value{29};
    return static_cast<unsigned int>(value) == 29;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
