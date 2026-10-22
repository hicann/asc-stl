# asc::std::time

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

`asc::std::time` is provided by `<asc/std/ctime>`; it returns the calendar time value since the epoch and is available on the host side.

Standard semantics reference: [cppreference `ctime`](https://en.cppreference.com/w/cpp/header/ctime).

## Function Prototype

The following entry point is provided only on the Host.

```cpp
namespace asc::std {
[[nodiscard]] time_t time(time_t* timer) noexcept;
}
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `timer` | Output | May be null; when non-null, the calendar time equal to the return value is written to it. |

## Return Value

| Return type | Description |
| --- | --- |
| `time_t` | The current calendar time; returns time_t(-1) when it cannot be obtained. When timer is non-null, the result is also written to *timer. |

## Constraints

- Returns the calendar time value since the epoch, available on the host side.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/ctime>

decltype(auto) example(time_t* timer)
{
    return asc::std::time(timer);
}
```

## Related APIs

- [API list for this header](asc_std_ctime.md)
