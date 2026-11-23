# asc::minimum::operator()

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

Header: `<asc/functional>`. Compare once, prefer the left operand on equivalence, and construct the smaller value result.

## Declaration

```cpp
// Inside the typed form; declaration constraints are omitted.
constexpr T operator()(const T& left, const T& right) const
    noexcept(/* comparison, bool conversion, and both result constructions */);

// Inside the void specialization.
template<class Left, class Right>
constexpr auto operator()(Left&& left, Right&& right) const
    noexcept(/* comparison, bool conversion, and both result constructions */)
    -> asc::std::common_type_t<asc::std::decay_t<Left>, asc::std::decay_t<Right>>;
```

## Constraints

The comparison is static_cast<bool>(right < left): true selects right, otherwise left. Transparent calls compare const lvalues of the original types, then forward only the selected argument. Typed calls construct from const T&. Both constructions must be valid; invalid comparisons, bool conversions, or constructions exclude the overload. noexcept also accounts for relevant temporary destruction.

The result is a complete, unqualified non-array value type. Transparent argument types must be complete non-volatile non-array objects after removing references. Temporary arguments are supported; pointer/view results keep their own borrowing requirements. Heterogeneous comparisons use ordinary C++ conversions. With strict floating-point semantics, an unordered NaN comparison selects left and equivalent signed zeros retain the left sign; fmin/fmax rules are not used.

C++17 and C++20 are supported. Host, SIMT, and SIMD scalar calls require comparison, conversion, construction, and destruction in the current execution domain. Device calls follow the no-exception execution contract.

## Example

```cpp
#include <asc/functional>
#include <asc/std/type_traits>

bool example()
{
    int left = 3;
    int right = 7;
    auto result = asc::minimum<>{}(left, right);
    static_assert(asc::std::is_same_v<decltype(result), int>);
    return result == 3 && &result != &left && &result != &right;
}
```

## Related APIs

- [Header API list and operation support table](asc_functional.md)
