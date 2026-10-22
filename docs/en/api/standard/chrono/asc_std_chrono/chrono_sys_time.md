# asc::std::chrono::sys_time

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

`asc::std::chrono::sys_time` is a time point alias whose `Clock` is `system_clock` and whose timekeeping precision is `Duration`; it stores the count since the system epoch.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Declaration

```cpp
namespace asc::std::chrono {
template<class Duration> using sys_time = time_point<system_clock, Duration>;
} // namespace asc::std::chrono
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Duration` | The duration type of the system time point, which determines the count precision. |

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/chrono>
#include <asc/std/type_traits>

using actual_type = asc::std::chrono::sys_time<asc::std::chrono::seconds>;
using expected_type = asc::std::chrono::time_point<asc::std::chrono::system_clock, asc::std::chrono::seconds>;
static_assert(asc::std::is_same_v<actual_type, expected_type>);
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
