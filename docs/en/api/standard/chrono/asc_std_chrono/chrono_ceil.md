# asc::std::chrono::ceil

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

`asc::std::chrono::ceil` converts a duration or time point to the specified precision, rounding toward positive infinity.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std::chrono {
template<class ToDuration, class Clock, class Duration> [[nodiscard]] constexpr time_point<Clock, ToDuration> ceil(const time_point<Clock, Duration>& value);
} // namespace asc::std::chrono
```

### Prototype 2

```cpp
namespace asc::std::chrono {
template<class ToDuration, class Rep, class Period> [[nodiscard]] constexpr ToDuration ceil(const duration<Rep, Period>& value);
} // namespace asc::std::chrono
```

## Parameters

### Parameters of Prototype 1

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ToDuration` | The target duration type to convert to. |
| `Clock` | The clock type the time point belongs to, such as system_clock. |
| `Duration` | The duration type of the source time point. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The time point to be converted with rounding up. |

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ToDuration` | The duration type of the conversion result, which determines the result's count representation and tick unit. |
| `Rep` | The count representation type of the input duration. |
| `Period` | The number of seconds corresponding to one count unit of the input duration, expressed as a ratio. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The duration to be converted with rounding up. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `time_point<Clock, ToDuration>` | Returns the duration or time point converted according to the selected precision and rounding rule. |
| Prototype 2 | `ToDuration` | Returns the duration or time point converted according to the selected precision and rounding rule. |

## Constraints

- Provides value operations and the six explicit relational operators.
- Supports user-defined clocks, value operations, and the six explicit relational operators.

## Example

The following snippet demonstrates the call on this page with concrete objects.

```cpp
#include <asc/std/chrono>

bool example()
{
    namespace chrono = asc::std::chrono;
    return chrono::ceil<chrono::seconds>(chrono::milliseconds{1500}).count() == 2;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
