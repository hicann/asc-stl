# asc::std::chrono::hh_mm_ss::hh_mm_ss

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

`asc::std::chrono::hh_mm_ss::hh_mm_ss` initializes an `hh_mm_ss` object according to the construction forms listed on this page.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

### Prototype 1

```cpp
constexpr hh_mm_ss() noexcept;
```

### Prototype 2

```cpp
explicit constexpr hh_mm_ss(Duration duration) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `duration` | Input | The duration to be decomposed into hours, minutes, and seconds; the timekeeping unit is determined by its period, and a negative duration records the sign and is decomposed by its absolute value. |

## Return Value

No return value.

## Constraints

- Duration must be a duration, and its count must satisfy the signed conditions of chrono::abs; the current implementation does not accept unsigned counts.
- The absolute value of the original duration and the decomposed fields must be representable; must not pass a value whose signed minimum negative value cannot have its absolute value taken.
- The negative sign is stored separately; the hours, minutes, seconds, and fractional seconds fields store the parts of the absolute value.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/chrono>
#include <asc/std/limits>

bool example()
{
    asc::std::chrono::hh_mm_ss<asc::std::chrono::seconds> value{asc::std::chrono::seconds{3661}};
    return value.to_duration().count() == 3661;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
