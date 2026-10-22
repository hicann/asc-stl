# asc::std::type_identity

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

`asc::std::type_identity` preserves the original type to delay or suppress template argument deduction.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<class T> struct type_identity;
} // namespace asc::std
```

## Constraints

- The member `type` is exactly equal to the template argument `T`; it is used to preserve type identity and to construct non-deduced contexts, and it does not perform type conversion.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // Positive example: type_identity returns the passed-in type unchanged
    static_assert(asc::std::is_same_v<asc::std::type_identity_t<int>, int>);
    static_assert(asc::std::is_same_v<typename asc::std::type_identity<const float>::type, const float>);
    // Counterexample: type_identity_t<int> is not long
    static_assert(!asc::std::is_same_v<asc::std::type_identity_t<int>, long>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
