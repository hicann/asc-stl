# asc::std::literals::chrono_literals::operator""h

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

`operator"" h` constructs a duration in units of hours; the integer form returns the corresponding integer duration, and the floating-point form returns a duration counted in double.

Standard semantics reference: [cppreference `chrono`](https://en.cppreference.com/w/cpp/header/chrono).

## Function Prototype

Located in the asc::std::literals::chrono_literals namespace.

```cpp
constexpr chrono::hours operator"" h(unsigned long long value) noexcept;
```

```cpp
constexpr chrono::duration<double, ratio<3600, 1>> operator"" h(long double value) noexcept;
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The count value of the literal; the unit is determined by the suffix. The integer form must be representable by the rep of the corresponding integer duration; the floating-point form is converted to a double count without rounding first. |

## Return Value

| Form | Return value |
| --- | --- |
| Integer | The corresponding integer duration, with the count taken from value. |
| Floating point | duration<double, ratio<3600, 1>>, preserving the fractional count representable by double. |

## Constraints

- Different suffixes denote hours, minutes, seconds, milliseconds, microseconds, and nanoseconds respectively.
- Floating-point input may be rounded when converted to double; preserving the full precision or range of long double is not guaranteed.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/chrono>

bool example()
{
    constexpr auto value = asc::std::literals::chrono_literals::operator"" h(1.5L);
    return value.count() == 1.5;
}
```

## Related APIs

- [API list for this header](asc_std_chrono.md)
