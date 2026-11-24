# asc::sincos

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

Header: `<asc/cmath>`.

Takes an angle in radians, writes its sine to sin_out and cosine to cos_out, and returns void.

## Function Prototype

```cpp
namespace asc {
void sincos(float value, float* sin_out, float* cos_out) noexcept;
void sincos(double value, double* sin_out, double* cos_out) noexcept;
void sincos(long double value, long double* sin_out, long double* cos_out) noexcept;
}
```

## Parameters

`value` is in radians; sin_out and cos_out point to the sine and cosine objects.

## Return Value

`void` — Takes an angle in radians, writes its sine to sin_out and cosine to cos_out, and returns void.

## Constraints

Both pointers are nonnull and aligned, referring to live writable objects accessible in the calling execution space. The complete output storage regions do not overlap. SIMT outputs may reside in accessible GM, UB, or thread stack storage; the caller coordinates concurrent access.

Signed zero is preserved for sine, with cosine one. NaN or either infinity produces two NaNs without a payload guarantee. All finite angles, including large values, follow the same-type sin/cos backend accuracy under identical environment and math options. No uniform ULP bound, bitwise equality, or correct rounding is promised. Special values require a configuration preserving NaNs, infinities and signed zero; relaxed math follows the compiler documentation. No common errno or floating-exception behavior is specified. The overloads are not constexpr, and a single call promises neither one instruction nor a speedup.

There is no integer/enum template. Ordinary conversions select the floating overload through the output pointer types; integer conversions may round, bool means zero or one radian, and scoped enums require explicit conversion. Convert low-precision formats explicitly first.

float: Host and 950 SIMT with CANN simt_api/math_functions.h providing sincosf; double: Host only; long double: only when enabled by the Host/standard-layer configuration. No scalar sincos is provided in ordinary SIMD control code.

## Example

```cpp
#include <asc/cmath>

bool verify_example()
{
    float sine{}, cosine{};
    asc::sincos(-0.0F, &sine, &cosine);
    return sine == 0.0F && asc::std::signbit(sine) && cosine == 1.0F;
}
```

## Related APIs

- [Header API list](asc_cmath.md)
