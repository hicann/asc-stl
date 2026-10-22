# asc::std::chrono::system_clock::rep

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

`asc::std::chrono::system_clock::rep` is the representation type of the nanosecond count of `system_clock`, currently long long.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Declaration

Member of: [`asc::std::chrono::system_clock`](chrono_system_clock.md).

```cpp
// Declaration excerpt from inside the asc::std::chrono::system_clock class; template parameters and other members are provided by the enclosing class.
using rep = duration::rep;
```

## Constraints

- Arithmetic on calendar fields and timekeeping values can be used on the Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.
- This type provides the time point, the time unit, and related type aliases; the callable clock operations are governed by the corresponding member descriptions.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/chrono>
#include <asc/std/type_traits>

using actual_type = asc::std::chrono::system_clock::rep;
using expected_type = long long;
static_assert(asc::std::is_same_v<actual_type, expected_type>);
```

## Related APIs

- [`asc::std::chrono::system_clock`](chrono_system_clock.md)
- [API list for this header](asc_std_chrono.md)
