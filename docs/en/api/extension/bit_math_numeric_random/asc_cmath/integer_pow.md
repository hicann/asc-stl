# asc::integer_pow

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

Computes an exact nonnegative integer power, returning the base type T.

## Function Prototype

```cpp
namespace asc {
template<class T, class E>
[[nodiscard]] constexpr T integer_pow(T base, E exponent) noexcept;
}
```

## Parameters

Parameter names, types and order are shown in the prototype. T is the integer input/result type; E is an independently selected exponent type, without usual arithmetic conversion with the base.

## Return Value

`T` — Computes an exact nonnegative integer power, returning the base type T.

## Constraints

E is nonnegative and the final mathematical result is representable in T. Exponent zero returns one, including 0^0; positive powers of zero return zero. Base one stays one and base minus one follows exponent parity. Negative exponents and overflow violate the preconditions, including unsigned overflow. No unused final square invalidates an otherwise valid result.

Integer templates accept only signed char, short, int, long, long long and their five unsigned counterparts, with at most 64 value/sign bits. Aliases follow their actual type. bool, plain/other character types, enums, floating types and low-precision wrappers are excluded by substitution. Binary operands have the same T; explicitly unify representable values before calling.

A violated numerical precondition has undefined runtime behavior and cannot form a core constant expression. C++17/20 constexpr and noexcept are supported. Integer promotion does not change the T result. Available on Host, 950PR/950DT SIMT and ordinary SIMD scalar control code.

## Example

```cpp
#include <asc/cmath>

constexpr bool verify_example()
{
    return asc::integer_pow(-2, 7u) == -128 && asc::integer_pow(0, 0) == 1;
}
```

## Related APIs

- [Header API list](asc_cmath.md)
