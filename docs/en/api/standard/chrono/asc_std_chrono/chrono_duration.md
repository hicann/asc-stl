# asc::std::chrono::duration

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

`asc::std::chrono::duration` combines the count `Rep` and the seconds-per-tick ratio `Period` into a duration; cross-period arithmetic first forms a common timekeeping unit.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Declaration

```cpp
namespace asc::std::chrono {
template<class Rep, class Period = ratio<1>> class duration;
} // namespace asc::std::chrono
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rep` | The count type that holds the number of ticks; it must not be a duration. |
| `Period` | A positive ratio type giving the number of seconds per tick; defaults to ratio<1>. |

## Constraints

- Rep must not be a duration; Period must be a ratio specialization, and Period::num must be positive.
- Arithmetic and intermediate values must be representable; modulo additionally requires the count to support the remainder operation.
- Default initialization of built-in counts is not guaranteed to be 0; initialize with an explicit count, for example seconds{0}, before reading count().

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/chrono>

bool example()
{
    asc::std::chrono::seconds value(3);
    const auto milliseconds = asc::std::chrono::duration_cast<asc::std::chrono::milliseconds>(value);
    return value.count() == 3 && milliseconds.count() == 3000;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
