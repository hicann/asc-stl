# asc::std::chrono::weekday::`operator-=`

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

`asc::std::chrono::weekday::operator-=` updates the current value in reverse by the given distance or operand.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::weekday`](chrono_weekday.md).

```cpp
// Excerpt of the declaration inside class asc::std::chrono::weekday; template parameters and other members are provided by the owning class.
constexpr weekday& operator-=(const days& offset) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `offset` | Input | Provides the object reference used to "update the current value in reverse by the given distance or operand"; the referenced object must remain valid during the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `weekday &` | Returns a reference to the current object after the update, which can continue to be used for assignment or compound operations. |

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host snippet demonstrates the call with concrete date or time types; the values must satisfy the constraints on this page.

```cpp
#include <asc/std/chrono>

bool example()
{
    namespace chrono = asc::std::chrono;
    chrono::weekday value = chrono::weekday{3};
    value -= chrono::days{1};
    return value.c_encoding() == 2;
}
```

## Related APIs

- [`asc::std::chrono::weekday`](chrono_weekday.md)
- [API list for this header](asc_std_chrono.md)
