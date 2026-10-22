# asc::std::conditional_t

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

Header: `<asc/std/type_traits>`.

`asc::std::conditional_t` selects one of two types based on a compile-time Boolean condition, providing the result as a type alias.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<bool Value, class If, class Then> using conditional_t = typename conditional<Value, If, Then>::type;
} // namespace asc::std
```

## Constraints

- This helper form uses the same type preconditions and decision rules as [`asc::std::conditional`](conditional.md); the result corresponds to the `type` of the trait class.

## Example

The following Host example checks the interface result against an independent expected type or value.

```cpp
#include <asc/std/type_traits>

using result_type = asc::std::conditional_t<true, int, long>;
static_assert(asc::std::is_same_v<result_type, int>);
static_assert(asc::std::is_same_v<asc::std::conditional_t<false, int, long>, long>);
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
