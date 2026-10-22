# asc::std::signbit

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

`asc::std::signbit` determines whether the sign bit of a floating-point value is set; on the device side, the applicable scope is subject to the float and execution-location constraints on this page.

For available locations by type, see the individual prototypes and the constraints.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__is_extended_arithmetic_v<Tp>, int> = 0>
[[nodiscard]] constexpr bool signbit(Tp x) noexcept;
}
```

Available locations: Host, AI Core SIMD programming, AI Core SIMT programming.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Tp` | Numeric type; must satisfy the integer, floating-point, or mixed arithmetic selection conditions in the corresponding prototype. |

The unnamed default int template parameter is used for overload selection; the caller does not need to provide it.

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `x` | Input | Input value (dimensionless) whose sign bit is to be checked for being set (negative numbers or -0). |

## Return Value

The return type is determined per prototype (`bool`). Returns true when the sign bit is 1, including negative zero and NaN with a negative sign.

## Constraints

- Provides float function overloads, evaluation-type aliases, comparison functions, nanf, and classification macros.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::signbit(-1.0F);
    return result == true;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
