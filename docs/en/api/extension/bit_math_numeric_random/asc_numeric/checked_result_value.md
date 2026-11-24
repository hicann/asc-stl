# asc::checked_result::value

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

value stores the successful result or a zero placeholder after failure.

## Function Prototype

```cpp
namespace asc {
template <class T>
struct checked_result {
    T value{};
    bool failed{};
};
}  // namespace asc
```

## Constraints

A failed value cannot be used as a valid size or index. Zero can also be successful; inspect failed to distinguish it.

- T, To and From are unqualified signed char, short, int, long, long long or their five unsigned counterparts, with at most 64 value-plus-sign bits. Fixed-width and size aliases follow their underlying types.
- bool, plain/wide/UTF characters, enums, floating-point, extended integers and low-precision wrappers do not participate in function overloads. Invalid checked_result<T> instantiations are diagnosed.
- Arithmetic deduces one common T. Ordinary argument conversions before a call with explicit T are outside the check; use overflow_cast first when needed.
- C++17 and C++20 share the same contract. Pure Host usage needs no SDK. Initial Device support covers corresponding scalar integer operations on Ascend950PR/950DT CANN/BiSheng SIMT and ordinary SIMD scalar code.

## Example

```cpp
#include <asc/numeric>

bool verify_example()
{
    const asc::checked_result<int> result{42, false};
    return !result.failed && result.value == 42;
}
```

## Related APIs

- [<asc/numeric>](asc_numeric.md)
