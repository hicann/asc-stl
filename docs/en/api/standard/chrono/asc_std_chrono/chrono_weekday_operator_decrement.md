# asc::std::chrono::weekday::`operator--`

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

`asc::std::chrono::weekday::operator--` decreases the weekday field by 1 (cycling over seven days).

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::weekday`](chrono_weekday.md).

### Prototype 1

```cpp
// Declaration excerpt from inside the asc::std::chrono::weekday class; template parameters and other members are provided by the enclosing class.
constexpr weekday& operator--() noexcept;
```

### Prototype 2

```cpp
// Declaration excerpt from inside the asc::std::chrono::weekday class; template parameters and other members are provided by the enclosing class.
constexpr weekday operator--(int unused) noexcept;
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
| Prototype 1 | `weekday &` | Returns a reference to the updated current object. |
| Prototype 2 | `weekday` | Returns a copy of the object's value before the modification. |

## Constraints

- Arithmetic on calendar fields and timekeeping values can be used on the Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host example uses concrete inputs and checks the result.

```cpp
#include <asc/std/chrono>

bool example()
{
    asc::std::chrono::weekday value{2};
    const auto previous = value--;
    auto& current = --value;
    return previous.c_encoding() == 2 && value.c_encoding() == 0 && &current == &value;
}
```

## Related APIs

- [`asc::std::chrono::weekday`](chrono_weekday.md)
- [API list for this header](asc_std_chrono.md)
