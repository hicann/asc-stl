# asc::std::chrono::weekday_indexed::ok

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

`asc::std::chrono::weekday_indexed::ok` determines whether the current calendar field combination represents a valid date.

`weekday_indexed` combines two fields, the weekday and the index: it returns `true` when the weekday value is in `[0, 6]` (0 for Sunday, 6 for Saturday) and the index value is in `[1, 5]` (denoting the nth weekday of the month), and returns `false` otherwise.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Member of: [`asc::std::chrono::weekday_indexed`](chrono_weekday_indexed.md).

```cpp
// Declaration excerpt from inside the asc::std::chrono::weekday_indexed class; template parameters and other members are provided by the enclosing class.
[[nodiscard]] constexpr bool ok() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, and `false` otherwise. |

## Constraints

- Arithmetic on calendar fields and timekeeping values can be used on the Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::weekday_indexed value{asc::std::chrono::weekday{4}, 4};
    return value.ok();
}
```

## Related APIs

- [`asc::std::chrono::weekday_indexed`](chrono_weekday_indexed.md)
- [API list for this header](asc_std_chrono.md)
