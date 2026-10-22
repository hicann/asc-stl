# asc::std::conditional

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

`conditional<B, T, U>` selects between two types based on a compile-time Boolean value.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

### Primary Template Declaration

```cpp
namespace asc::std {
template<bool B, class If, class Then> struct conditional;
} // namespace asc::std
```

### Partial Specialization Declaration

```cpp
namespace asc::std {
template<class If, class Then> struct conditional<false, If, Then>;
} // namespace asc::std
```

## Constraints

- `B` is a compile-time Boolean condition; when it is `true`, the member type `type` is `If`, and when it is `false`, it is `Then`.
- The partial specialization provides an alternative definition of the primary template when `B == false`; it is not a second function overload.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // A true condition selects the first argument; a false condition selects the second
    static_assert(asc::std::is_same_v<asc::std::conditional<true, int, long>::type, int>);
    static_assert(asc::std::is_same_v<asc::std::conditional_t<false, int, long>, long>);
    // Counterexample: a true condition does not select the second argument
    static_assert(!asc::std::is_same_v<asc::std::conditional_t<true, int, long>, long>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
