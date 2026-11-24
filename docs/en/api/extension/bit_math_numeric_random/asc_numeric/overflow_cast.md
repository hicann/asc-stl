# asc::overflow_cast

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

Checks whether the original integer is representable in To and preserves its value on success.

## Function Prototype

```cpp
namespace asc {
template <class To, class From>
[[nodiscard]] constexpr checked_result<To> overflow_cast(From value) noexcept;
}  // namespace asc
```

## Parameters

| Parameter | Kind | Description |
| --- | --- | --- |
| `To` | Template | Destination integer type. |
| `From` | Template | Source integer type deduced from the argument. |
| `value` | Input | Original integer value to check. |

## Return Value

Success stores the specified value with failed=false; failure stores zero in the destination type with failed=true. Output-reference forms always write back and return true on failure, with the same value and flag as object forms. Output may alias an input variable; computation uses the prior input values. Functions are constexpr, noexcept and [[nodiscard]]; constant evaluation reports failure using the same flag, without throwing or terminating.

## Constraints

Check the original value against the minimum and maximum of To. Negative-to-unsigned conversions fail; round-trip equality is not a representability test.

- T, To and From are unqualified signed char, short, int, long, long long or their five unsigned counterparts, with at most 64 value-plus-sign bits. Fixed-width and size aliases follow their underlying types.
- bool, plain/wide/UTF characters, enums, floating-point, extended integers and low-precision wrappers do not participate in function overloads. Invalid checked_result<T> instantiations are diagnosed.
- Arithmetic deduces one common T. Ordinary argument conversions before a call with explicit T are outside the check; use overflow_cast first when needed.
- C++17 and C++20 share the same contract. Pure Host usage needs no SDK. Initial Device support covers corresponding scalar integer operations on Ascend950PR/950DT CANN/BiSheng SIMT and ordinary SIMD scalar code.

## Example

```cpp
#include <asc/numeric>

bool verify_example()
{
    const auto valid = asc::overflow_cast<unsigned char>(42);
    const auto invalid = asc::overflow_cast<unsigned>(-1);
    return !valid.failed && valid.value == 42 && invalid.failed && invalid.value == 0;
}
```

## Related APIs

- [<asc/numeric>](asc_numeric.md)
