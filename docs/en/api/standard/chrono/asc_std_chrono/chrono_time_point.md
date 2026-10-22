# asc::std::chrono::time_point

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

`asc::std::chrono::time_point` stores a `Duration` since the epoch of a `Clock`, distinguishes different time lines, and performs time point offsets or differences at the selected precision.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Declaration

```cpp
namespace asc::std::chrono {
template<class Clock, class Duration = typename Clock::duration> class time_point;
} // namespace asc::std::chrono
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Clock` | The time line label; cross-time-point operations require the same Clock. |
| `Duration` | The duration type that stores the epoch offset, defaulting to Clock::duration. |

## Constraints

- Supports user-defined clocks, value arithmetic, and the six explicit relational operators.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/chrono>

bool example()
{
    using point = asc::std::chrono::time_point<asc::std::chrono::system_clock, asc::std::chrono::seconds>;
    point start(asc::std::chrono::seconds(3));
    const point end = start + asc::std::chrono::seconds(2);
    return start.time_since_epoch().count() == 3 && (end - start).count() == 2;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
