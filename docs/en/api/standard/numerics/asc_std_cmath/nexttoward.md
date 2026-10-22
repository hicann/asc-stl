# asc::std::nexttoward

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

Header: `<asc/std/cmath>`.

`asc::std::nexttoward` is provided by `<asc/std/cmath>`; the next representable value toward toward (C99 contract, second argument long double); Host only, not provided on the device.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float nexttoward(float value, long double toward) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

### Prototype 2

```cpp
namespace asc::std {
[[nodiscard]] constexpr double nexttoward(double value, long double toward) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

### Prototype 3

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double nexttoward(
    long double value, long double toward) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Starting floating-point value for finding the adjacent representable value (dimensionless). |
| `toward` | Input | Target value indicating the direction of movement (long double precision, dimensionless); when value equals toward, returns toward converted to the return type, preserving the sign of the target zero. |

## Return Value

The return type is determined per prototype (`float`, `double`, `long double`). Returns the adjacent value in the result format toward the long double target; returns the converted target value when the values are numerically equal, preserving the sign of the target zero.

## Constraints

- When the two values are equal, returns the target direction argument converted to the result type; +0 and -0 compare equal, in which case the sign of the target zero is preserved.

- The next representable value toward toward (C99 contract, second argument long double); Host only, not provided on the device.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto value = asc::std::nexttoward(1.0F, 2.0L);
    return value > 1.0F && value < 2.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
