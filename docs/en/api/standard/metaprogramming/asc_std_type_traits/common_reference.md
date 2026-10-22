# asc::std::common_reference

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

`asc::std::common_reference` computes the reference type commonly usable by a group of types.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<class... Types>
struct common_reference;
} // namespace asc::std
```

## Constraints

- Under the common reference rules, the reference common type, a customized `basic_common_reference`, the conditional expression, and `common_type` are tried in order. The multi-argument form merges recursively; when no suitable result exists, `type` is not provided.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // Common reference type of an lvalue reference combination
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<int&, const int&>, const int&>);
    // Non-reference types take the common type of the conditional expression result
    static_assert(asc::std::is_same_v<asc::std::common_reference<short, int>::type, int>);
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<int, double>, double>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
