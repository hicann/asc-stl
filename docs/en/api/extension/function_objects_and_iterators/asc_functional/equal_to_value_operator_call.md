# asc::equal_to_value::operator()

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

Header: `<asc/functional>`. Compare the input on the left with the stored value on the right and return bool.

## Declaration

```cpp
// Inside equal_to_value<T>; declaration constraints are omitted.
template<class U>
constexpr bool operator()(const U& input) const
    noexcept(noexcept(static_cast<bool>(input == value_)));
```

## Constraints

Heterogeneous const-lvalue comparisons use static_cast<bool>(input == value_) without consuming the stored value. Invalid equality or explicit bool conversion excludes the call. noexcept covers comparison, conversion, and temporary destruction. C++20 rewritten candidates follow the language rules.

C++17 and C++20 are supported. Host, SIMT, and SIMD scalar calls require comparison, conversion, construction, and destruction in the current execution domain. Device calls follow the no-exception execution contract.

## Example

```cpp
#include <asc/functional>

bool example()
{
    const asc::equal_to_value<int> equal(7);
    return equal(7L) && !equal(8L);
}
```

## Related APIs

- [Header API list and operation support table](asc_functional.md)
