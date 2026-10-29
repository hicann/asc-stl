# asc::std::timespec_get

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

`asc::std::timespec_get` is provided by `<asc/std/ctime>`; it is a host-only base time acquisition that forwards to ::timespec_get with base TIME_UTC

Standard semantics reference: [cppreference `ctime`](https://en.cppreference.com/w/cpp/header/ctime).

## Function Prototype

The following entry point is provided only on the Host.

```cpp
namespace asc::std {
[[nodiscard]] int timespec_get(timespec* ts, int base) noexcept;
}
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `ts` | Output | The output time structure; must point to a valid writable timespec object. |
| `base` | Input | The time base; use TIME_UTC to request the current calendar time. Unsupported bases return 0. |

## Return Value

| Return type | Description |
| --- | --- |
| `int` | On success, returns base and writes to ts; on failure, returns 0. |

## Constraints

- Returns the calendar time value since the epoch, available on the host side.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/ctime>

bool example()
{
    asc::std::timespec value{};
    const int status = asc::std::timespec_get(&value, TIME_UTC);
    return status == TIME_UTC && value.tv_nsec >= 0 && value.tv_nsec < 1000000000L;
}
```

## Related APIs

- [API list for this header](asc_std_ctime.md)
