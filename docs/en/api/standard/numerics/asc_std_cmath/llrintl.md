# asc::std::llrintl

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

`asc::std::llrintl` is provided by `<asc/std/cmath>`; Host long double rounds according to the rounding mode and converts to long long, the suffix-l alias.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr long long llrintl(long double value) noexcept;
}
```

Available locations: Host. The long double related overloads require Host to have support for this type enabled.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Input value to be rounded according to the current rounding mode and converted to long long (dimensionless). |

## Return Value

The return type is determined per prototype (`long long`). Converts to long long according to the current rounding direction.

## Constraints

- When the input is NaN or infinity, or the rounded result is outside the range representable by the returned integer type, there is no portable numeric result; the specific value and floating-point exceptions are determined by the Host or Device backend, and a fixed integer sentinel must not be relied upon.

- Host long double rounds according to the rounding mode and converts to long long, suffix-l alias.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::llrintl(2.0L);
    return result == 2LL;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
