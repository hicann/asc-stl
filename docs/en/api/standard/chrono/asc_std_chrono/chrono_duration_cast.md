# asc::std::chrono::duration_cast

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

`asc::std::chrono::duration_cast` converts between duration types, converting the count and the period.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

```cpp
namespace asc::std::chrono {
template<class ToDuration, class Rep, class Period> [[nodiscard]] constexpr ToDuration duration_cast(const duration<Rep, Period>& value);
} // namespace asc::std::chrono
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ToDuration` | The duration type of the conversion result; it determines the result's count representation and timekeeping unit. |
| `Rep` | The count representation type of the input duration. |
| `Period` | The number of seconds corresponding to one count unit of the input duration, expressed as a ratio. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The duration to convert; when the target count is an integer, fractional parts that cannot be represented are truncated toward zero; a floating-point target keeps its representable fraction and follows floating-point conversion rounding. |

## Return Value

| Return type | Description |
| --- | --- |
| `ToDuration` | Returns the duration or time point converted according to the selected precision and rounding rule. |

## Constraints

- Provides value operations and the six explicit relational operators.

## Example

The following snippet uses concrete objects to show the call on this page.

```cpp
#include <asc/std/chrono>

bool example()
{
    namespace chrono = asc::std::chrono;
    return chrono::duration_cast<chrono::seconds>(chrono::milliseconds{1500}).count() == 1;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
