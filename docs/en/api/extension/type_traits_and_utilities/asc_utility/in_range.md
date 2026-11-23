# asc::in_range

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

Header: `<asc/utility>`.

Checks whether `value` lies in the inclusive numeric interval `[first, last]`. Standard `asc::std::in_range<R>(value)` instead checks whether an integer is representable by type `R`.

## Function Prototype

```cpp
namespace asc {
template <class T>
constexpr bool in_range(T value, T first, T last) noexcept;
}  // namespace asc
```

## Parameters

| Parameter | Meaning |
| --- | --- |
| `T` | One supported numeric type deduced for all three parameters; no common-type deduction. |
| `value` | Value to check, passed by value. |
| `first`, `last` | Included lower and upper bounds; reversed bounds return false. |

## Return Value

First evaluates `first <= value`, then evaluates `value <= last` only if the first comparison is true. Returns `bool` without subtraction or mixed-type integer conversions. Equal bounds accept that value; `first > last` returns false.

Any NaN input returns false. Infinities follow ordinary ordering, and positive and negative zero compare equal. Compiler options must preserve these floating-point semantics. Built-in comparisons cannot throw C++ exceptions, so the function is unconditionally `noexcept`; it supports constant evaluation when permitted by the language rules.

## Constraints

- Requires C++17 and supports C++20. Integer types are `signed char`, `short`, `int`, `long`, `long long`, and their unsigned counterparts. Host also supports `float`, `double`, and `long double`; Device floating-point support is limited to `float`.
- Plain `char`, `bool`, character types, enums, pointers, user-defined comparison types, and extended integers are excluded from overload resolution. Deduction ignores top-level cv. An explicit `T` uses ordinary argument conversions, whose precision, representability, and exceptions remain the caller's responsibility.
- Host inclusion requires no CANN SDK. Device calls use supported SIMT or scalar SIMD contexts with valid types and floating-point comparisons, without exception recovery.

## Example

```cpp
#include <asc/utility>

bool verify_example()
{
    return asc::in_range(4, 1, 4) && !asc::in_range(4, 5, 1) && !asc::in_range(8, 1, 4);
}
```

## Related APIs

- [Header API list](asc_utility.md)
