# asc::std::logbf

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

`asc::std::logbf` returns the floating-point exponent of a floating-point value; the applicable device-side scope is governed by the float and execution-location constraints on this page.

The available locations for this interface are Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath).

## Function Prototype

Each overload is available starting from C++17. Execution-location restrictions are described per prototype below; execution-location macros are omitted.

### Prototype 1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float logbf(
    float value) noexcept;
}
```

Available locations: Host, AI Core SIMT programming. The following constexpr applies to Host; the Device declaration is not constexpr and the call is executed at run time.

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Input value whose normalized exponent is to be extracted (dimensionless); ±0 returns -inf, ±inf returns +inf, and NaN returns NaN. |

## Return Value

The return type is determined per prototype (`float`). Returns the exponent as a floating-point value; zero returns negative infinity and infinity returns positive infinity.

## Constraints

- Provides the float overload and the standard *f aliases; the underlying capability is provided by the Ascend C development suite.

## Example

The following Host example provides concrete inputs and expected results.

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::logbf(8.0F);
    return result == 3.0F;
}
```

## Related APIs

- [API list for this header](asc_std_cmath.md)
