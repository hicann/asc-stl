# asc::std::chrono::make24

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

`asc::std::chrono::make24` converts a 12-hour clock value to the 24-hour clock according to the ante meridiem or post meridiem flag.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

```cpp
namespace asc::std::chrono {
[[nodiscard]] constexpr hours make24(const hours& value, bool pm) noexcept;
} // namespace asc::std::chrono
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The hour (hours, with a count unit of hours) expressed in the 12-hour clock, taking values 1 to 12. |
| `pm` | Input | The ante meridiem/post meridiem flag: true means post meridiem and false means ante meridiem; the hour is converted to the 24-hour clock value from 0 to 23 accordingly. |

## Return Value

| Return type | Description |
| --- | --- |
| `hours` | Returns the converted 12-hour clock or 24-hour clock hour value. |

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/chrono>

decltype(auto) example(const asc::std::chrono::hours & value, bool pm)
{
    return asc::std::chrono::make24(value, pm);
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
