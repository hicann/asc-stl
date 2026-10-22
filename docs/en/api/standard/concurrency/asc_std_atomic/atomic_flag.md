# asc::std::atomic_flag

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

Header: `<asc/std/atomic>`.

`asc::std::atomic_flag` holds a flag that can be atomically set and cleared.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Declaration

```cpp
namespace asc::std {
class atomic_flag;
} // namespace asc::std
```

## Constraints

- This type can be constructed and operated in Host or AI Core SIMT programming; objects shared by SIMT threads must be located in GM.
- The initial flag is `false`; initialization must be completed before concurrent access begins, and copy construction and copy assignment are not available.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic_flag flag{};
    flag.clear();
    const bool was_set = flag.test_and_set();
    return !was_set && flag.test_and_set();
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
