# asc::std::chrono::day::`operator--`

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

`asc::std::chrono::day::operator--` decrements the day field by 1.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::day`](chrono_day.md).

### Prototype 1

```cpp
// Declaration excerpt from inside the asc::std::chrono::day class; template parameters and other members are provided by the enclosing class.
constexpr day& operator--() noexcept;
```

### Prototype 2

```cpp
// Declaration excerpt from inside the asc::std::chrono::day class; template parameters and other members are provided by the enclosing class.
constexpr day operator--(int unused) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `unused` | Input | Placeholder parameter used to distinguish the postfix form; usually written as `value--`, with 0 passed automatically by the language. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `day &` | Returns a reference to the current object after the update. |
| Prototype 2 | `day` | Returns a copy of the object's value before the modification. |

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host example uses concrete inputs and checks the result.

```cpp
#include <asc/std/chrono>

bool example()
{
    asc::std::chrono::day value{2};
    const auto previous = value--;
    auto& current = --value;
    return static_cast<unsigned>(previous) == 2 && static_cast<unsigned>(value) == 0 && &current == &value;
}
```

## Related APIs

- [`asc::std::chrono::day`](chrono_day.md)
- [API list for this header](asc_std_chrono.md)
