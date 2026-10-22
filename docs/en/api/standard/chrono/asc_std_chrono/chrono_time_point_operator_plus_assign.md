# asc::std::chrono::time_point::`operator+=`

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

`asc::std::chrono::time_point::operator+=` updates the current value by the given distance or operand.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::time_point`](chrono_time_point.md).

```cpp
// Declaration excerpt from inside the asc::std::chrono::time_point class; template parameters and other members are provided by the enclosing class.
constexpr time_point<Clock, Duration>& operator+=(const duration& value);
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The duration accumulated onto the current time point; the timekeeping unit is determined by its period, and the result is still relative to the same Clock. |

## Return Value

| Return type | Description |
| --- | --- |
| `time_point<Clock, Duration> &` | Returns a reference to the updated current object, which can continue to be used for assignment or compound operations. |

## Constraints

- Supports user-defined clocks, value arithmetic, and the six explicit relational operators.

## Example

The following Host snippet demonstrates the call with concrete date or time types; the values must satisfy the constraints on this page.

```cpp
#include <asc/std/chrono>

void example(asc::std::chrono::time_point<asc::std::chrono::system_clock>& value)
{
    value += asc::std::chrono::system_clock::duration{1};
}
```

## Related APIs

- [`asc::std::chrono::time_point`](chrono_time_point.md)
- [API list for this header](asc_std_chrono.md)
