# asc::std::chrono::day::`operator-=`

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

`asc::std::chrono::day::operator-=` updates the current value in reverse by the given distance or operand.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::day`](chrono_day.md).

```cpp
// Declaration excerpt from inside the asc::std::chrono::day class; template parameters and other members are provided by the enclosing class.
constexpr day& operator-=(const days& value) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The number of days (a `days` duration whose count unit is days) subtracted from the current day value; when the difference is outside 0 to 255, the stored value is unspecified. |

## Return Value

| Return type | Description |
| --- | --- |
| `day &` | Returns a reference to the current object after the update, which can continue to take part in assignment or compound operations. |

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host snippet demonstrates the call with concrete date or time types; the values must satisfy the constraints on this page.

```cpp
#include <asc/std/chrono>

bool example()
{
    namespace chrono = asc::std::chrono;
    chrono::day value = chrono::day{10};
    value -= chrono::days{1};
    return static_cast<unsigned>(value) == 9;
}
```

## Related APIs

- [`asc::std::chrono::day`](chrono_day.md)
- [API list for this header](asc_std_chrono.md)
