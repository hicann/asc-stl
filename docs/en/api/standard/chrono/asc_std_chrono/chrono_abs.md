# asc::std::chrono::abs

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

`asc::std::chrono::abs` returns the non-negative value of a duration.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

```cpp
namespace asc::std::chrono {
template<class Rep, class Period> [[nodiscard]] constexpr duration<Rep, Period> abs(duration<Rep, Period> value);
} // namespace asc::std::chrono
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep` | The count representation type of the input duration. |
| `Period` | The number of seconds corresponding to one count unit of the input duration, expressed as a ratio. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The duration whose absolute value is to be taken; returns the non-negative duration under the same tick unit, where the tick unit is determined by period. |

## Return Value

| Return type | Description |
| --- | --- |
| `duration<Rep, Period>` | Returns the non-negative value of the duration. |

## Constraints

- Participates in overload resolution only when Rep's numeric_limits::is_signed is true; unsigned counts do not participate.
- The result must be representable by Rep. When the positive value of the signed minimum negative value cannot be represented, the function must not be called.
- The tick period is unchanged; returns the same duration type as the input.

## Example

The following snippet demonstrates the call on this page with concrete objects.

```cpp
#include <asc/std/chrono>

bool example()
{
    namespace chrono = asc::std::chrono;
    return chrono::abs(chrono::seconds{-3}).count() == 3;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
