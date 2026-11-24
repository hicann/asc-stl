# `<asc/cmath>`: Issue 92

Implements [Issue 92](https://gitcode.com/cann/asc-stl/issues/92): six exact integer templates and the float/double/long double `sincos` overloads, with the documented execution-space constraints.

Integer arguments use the same standard integer type T and return T; exponent E may differ. Mixed widths/signs and enums require an explicit caller conversion. `ceil_div` now handles all signed operand combinations. `round_up` accepts any positive multiple. Nonnegative powers and square roots preserve exact integer results, including the legal minimum/maximum boundaries. A numerical precondition violation is undefined at runtime and is rejected in constant evaluation. `mul_hi` needs no 128-bit Device type.

The unreviewed `integer_log2` extension is removed: after establishing a positive unsigned input u, use `asc::std::bit_width(u) - 1`. The integer/enum `sincos` template is removed; ordinary language conversions select one of the three floating overloads through the output pointer types. Device double and long double and ordinary SIMD scalar trigonometry remain unavailable.

`sincos` takes radians, requires valid writable nonoverlapping outputs, preserves signed zero, and returns two NaNs for NaN/infinite input. Precision follows the same-type backend; a paired call promises no instruction count or speedup.

C++17 and C++20 are supported. This change does not add a new feature macro or change the package version.
