# asc::std::chrono::year::`operator+=`

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

`asc::std::chrono::year::operator+=` updates the current value by the given distance or operand.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::year`](chrono_year.md).

```cpp
// Excerpt of the declaration inside class asc::std::chrono::year; template parameters and other members are provided by the owning class.
constexpr year& operator+=(const years& value) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The number of years to add to the current year (a years duration counted in years); when the result is outside -32767 to 32767, the stored value is unspecified. |

## Return Value

| Return type | Description |
| --- | --- |
| `year &` | Returns a reference to the current object after the update, which can continue to be used for assignment or compound operations. |

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host snippet demonstrates the call with concrete date or time types; the values must satisfy the constraints on this page.

```cpp
#include <asc/std/chrono>

void example(asc::std::chrono::year& value)
{
    value += asc::std::chrono::years{1};
}
```

## Related APIs

- [`asc::std::chrono::year`](chrono_year.md)
- [API list for this header](asc_std_chrono.md)
