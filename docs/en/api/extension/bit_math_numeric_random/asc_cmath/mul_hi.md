# asc::mul_hi

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

For W unsigned value bits of T, returns floor(left*right/2^W), the high W bits of the full mathematical product.

## Function Prototype

```cpp
namespace asc {
template<class T>
[[nodiscard]] constexpr T mul_hi(T left, T right) noexcept;
}
```

## Parameters

Parameter names, types and order are shown in the prototype. T is the integer input/result type; E is an independently selected exponent type, without usual arithmetic conversion with the base.

## Return Value

`T` — For W unsigned value bits of T, returns floor(left*right/2^W), the high W bits of the full mathematical product.

## Constraints

Both inputs have the same supported standard unsigned integer type. The complete product may use 2W bits and need not fit T. Device 128-bit integers are not required. Narrow inputs use their original width W.

Integer templates accept only signed char, short, int, long, long long and their five unsigned counterparts, with at most 64 value/sign bits. Aliases follow their actual type. bool, plain/other character types, enums, floating types and low-precision wrappers are excluded by substitution. Binary operands have the same T; explicitly unify representable values before calling.

A violated numerical precondition has undefined runtime behavior and cannot form a core constant expression. C++17/20 constexpr and noexcept are supported. Integer promotion does not change the T result. Available on Host, 950PR/950DT SIMT and ordinary SIMD scalar control code.

## Example

```cpp
#include <asc/cmath>

constexpr bool verify_example()
{
    return asc::mul_hi(~0ULL, ~0ULL) == ~0ULL - 1;
}
```

## Related APIs

- [Header API list](asc_cmath.md)
