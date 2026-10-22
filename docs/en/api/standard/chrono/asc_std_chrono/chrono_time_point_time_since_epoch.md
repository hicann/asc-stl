# asc::std::chrono::time_point::time_since_epoch

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

`asc::std::chrono::time_point::time_since_epoch` returns the duration of the time point from its clock epoch.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::time_point`](chrono_time_point.md).

```cpp
// Declaration excerpt from inside the asc::std::chrono::time_point class; template parameters and other members are provided by the enclosing class.
[[nodiscard]] constexpr duration time_since_epoch() const;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `duration` | Returns the duration of the time point from its clock epoch. |

## Constraints

- Supports user-defined clocks, value arithmetic, and the six explicit relational operators.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::time_point<asc::std::chrono::system_clock, asc::std::chrono::seconds> value{asc::std::chrono::seconds{7}};
    return value.time_since_epoch().count() == 7;
}
```

## Related APIs

- [`asc::std::chrono::time_point`](chrono_time_point.md)
- [API list for this header](asc_std_chrono.md)
