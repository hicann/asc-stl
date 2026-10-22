# asc::std::chrono::system_clock::is_steady

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

`asc::std::chrono::system_clock::is_steady` indicates whether the count of this clock increases monotonically.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Declaration

Member of: [`system_clock`](chrono_system_clock.md).

```cpp
static constexpr bool is_steady = false;
```

## Constraints

- Operations on calendar fields and timekeeping values are available on Host and in supported AI Core programming modes; date validity is determined by the corresponding `ok()` member.
- This type provides time points, tick units, and related type aliases; callable clock operations are subject to the descriptions of the corresponding members.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>

bool example()
{
    static_assert(!asc::std::chrono::system_clock::is_steady);
    asc::std::chrono::system_clock::time_point epoch{};
    return epoch.time_since_epoch().count() == 0;
}
```

## Related APIs

- [`asc::std::chrono::system_clock`](chrono_system_clock.md)
- [API list for this header](asc_std_chrono.md)
