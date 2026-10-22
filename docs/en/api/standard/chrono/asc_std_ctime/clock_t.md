# asc::std::clock_t

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

Header: `<asc/std/ctime>`.

`asc::std::clock_t` is the processor clock count type returned by clock(); Host reuses the platform time.h, and the device side uses long long.

Standard semantics reference: [cppreference `ctime`](https://en.cppreference.com/w/cpp/header/ctime).

## Declaration

Host uses the same-named type from the system `<time.h>`; the device side uses `long long`.

```cpp
namespace asc::std {
// Host
using ::clock_t;
}
```

The corresponding type declaration on the device side is:

```cpp
namespace asc::std {
using clock_t = long long;
}
```

## Constraints

- Host uses the standard clock.
- In AI Core SIMD programming, get_sys_cnt is used; in AI Core SIMT programming, clock64 is used.
- The device-side counter frequency is the 1 GHz declared on this page, and difftime only performs the value computation.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/ctime>

bool example()
{
    asc::std::clock_t begin = 2;
    asc::std::clock_t end = 5;
    return end - begin == 3;
}
```

## Related APIs

- [API list for this header](asc_std_ctime.md)
