# asc::std::literals::chrono_literals::operator""y

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

`asc::std::literals::chrono_literals::operator""y` constructs a calendar year value from an integer literal.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

```cpp
// Excerpt of the declaration inside class asc::std::literals::chrono_literals; template parameters and other members are provided by the owning class.
constexpr chrono::year operator""y(unsigned long long value) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The integer literal value (unsigned); converted to a year object denoting the year, e.g. 2026y denotes the year 2026. |

## Return Value

| Return type | Description |
| --- | --- |
| `chrono::year` | Returns the day or year value constructed from the integer literal. |

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/chrono>

bool example()
{
    namespace chrono = asc::std::chrono;
    return static_cast<int>(asc::std::literals::chrono_literals::operator""y(2024)) == 2024;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
