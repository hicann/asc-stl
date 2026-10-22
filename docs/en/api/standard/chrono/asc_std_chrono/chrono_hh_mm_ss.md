# asc::std::chrono::hh_mm_ss

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

`asc::std::chrono::hh_mm_ss` decomposes a duration into the sign, the hours, minutes, seconds, and fractional seconds of its absolute value for field-by-field inspection, and reassembles it into a duration according to `precision`.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Declaration

```cpp
namespace asc::std::chrono {
template<class Duration> class hh_mm_ss;
} // namespace asc::std::chrono
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Duration` | The duration type to be decomposed; its count must satisfy the signed conditions of chrono::abs and support the corresponding conversions. |

## Constraints

- Duration must be a duration, and its count must satisfy the signed conditions of chrono::abs; the current implementation does not accept unsigned counts.
- The absolute value of the original duration and the decomposed fields must be representable; must not pass a value whose signed minimum negative value cannot have its absolute value taken.
- The negative sign is stored separately; the hours, minutes, seconds, and fractional seconds fields store the parts of the absolute value.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/chrono>

bool example()
{
    asc::std::chrono::hh_mm_ss<asc::std::chrono::seconds> time(asc::std::chrono::seconds(3661));
    return time.hours().count() == 1 && time.minutes().count() == 1 && time.seconds().count() == 1;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
