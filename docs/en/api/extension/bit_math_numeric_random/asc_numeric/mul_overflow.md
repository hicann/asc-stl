# asc::mul_overflow

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

Header: `<asc/numeric>`.

Computes the exact product of two same-type integers and checks representability in T.

## Function Prototype

```cpp
namespace asc {
template <class T>
[[nodiscard]] constexpr checked_result<T> mul_overflow(T left, T right) noexcept;
template <class T>
[[nodiscard]] constexpr bool mul_overflow(T left, T right, T& result) noexcept;
}  // namespace asc
```

## Parameters

| Parameter | Kind | Description |
| --- | --- | --- |
| `T` | Template | The common supported integer type. |
| `left` | Input | Left operand passed by value. |
| `right` | Input | Right operand passed by value. |
| `result` | Output | Present only in the output-reference form; always written on success or failure. |

## Return Value

Success stores the specified value with failed=false; failure stores zero in the destination type with failed=true. Output-reference forms always write back and return true on failure, with the same value and flag as object forms. Output may alias an input variable; computation uses the prior input values. Functions are constexpr, noexcept and [[nodiscard]]; constant evaluation reports failure using the same flag, without throwing or terminating.

## Constraints

A product outside the range of T fails. Checking a 64-bit result does not require wider Device integers.

- T, To and From are unqualified signed char, short, int, long, long long or their five unsigned counterparts, with at most 64 value-plus-sign bits. Fixed-width and size aliases follow their underlying types.
- bool, plain/wide/UTF characters, enums, floating-point, extended integers and low-precision wrappers do not participate in function overloads. Invalid checked_result<T> instantiations are diagnosed.
- Arithmetic deduces one common T. Ordinary argument conversions before a call with explicit T are outside the check; use overflow_cast first when needed.
- C++17 and C++20 share the same contract. Pure Host usage needs no SDK. Initial Device support covers corresponding scalar integer operations on Ascend950PR/950DT CANN/BiSheng SIMT and ordinary SIMD scalar code.

## Example

```cpp
#include <asc/numeric>
#include <asc/std/limits>

bool verify_example()
{
    const auto product = asc::mul_overflow(asc::std::numeric_limits<unsigned long long>::max(), 2ULL);
    int value = 3;
    const bool failed = asc::mul_overflow(value, value, value);
    return product.failed && product.value == 0ULL && !failed && value == 9;
}
```

## Related APIs

- [<asc/numeric>](asc_numeric.md)
