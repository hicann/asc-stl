# asc::std::chrono::time_point_cast

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

`asc::std::chrono::time_point_cast` converts a time point to a time point type at the specified precision.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

```cpp
namespace asc::std::chrono {
template<class ToDuration, class Clock, class Duration> [[nodiscard]] constexpr time_point<Clock, ToDuration> time_point_cast(const time_point<Clock, Duration>& value);
} // namespace asc::std::chrono
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ToDuration` | The target duration type to convert to, serving as the timekeeping precision of the resulting time point. |
| `Clock` | The clock type the time point belongs to, such as system_clock. |
| `Duration` | The duration type of the source time point. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The time point to convert; when the target count is an integer, fractional parts that cannot be represented are truncated toward zero; a floating-point target keeps its representable fractional part and is rounded according to floating-point conversion. |

## Return Value

| Return type | Description |
| --- | --- |
| `time_point<Clock, ToDuration>` | Returns the duration or time point converted according to the selected precision and rounding rule. |

## Constraints

- Supports user-defined clocks, value arithmetic, and the six explicit relational operators.

## Example

The following snippet uses concrete objects to show the call on this page.

```cpp
#include <asc/std/chrono>

bool example()
{
    namespace chrono = asc::std::chrono;
    chrono::time_point<chrono::system_clock, chrono::milliseconds> value(chrono::milliseconds{1500});
    return chrono::time_point_cast<chrono::seconds>(value).time_since_epoch().count() == 1;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
