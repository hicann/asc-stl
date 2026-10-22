# asc::std::enable_if

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

`enable_if<B, T>` provides `type` only when the condition holds; it is used for C++17 overload constraints.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

### Primary Template Declaration

```cpp
namespace asc::std {
template<bool B, class T = void> struct enable_if;
} // namespace asc::std
```

### Partial Specialization Declaration

```cpp
namespace asc::std {
template<class T> struct enable_if<true, T>;
} // namespace asc::std
```

## Constraints

- `B` is a compile-time Boolean condition; the member type `type` is provided only when `B == true`, and its type is `T`.
- `T` defaults to `void`; when `B == false`, accessing `type` is ill-formed, which can be used to exclude overloads that do not satisfy the condition during template substitution.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // When the condition is true, ::type is the specified type
    static_assert(asc::std::is_same_v<asc::std::enable_if<true, int>::type, int>);
    // The default type argument is void
    static_assert(asc::std::is_same_v<asc::std::enable_if_t<true>, void>);
    // Counterexample: the selected type is not any other type
    static_assert(!asc::std::is_same_v<asc::std::enable_if_t<true, int>, long>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
