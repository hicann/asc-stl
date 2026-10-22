# asc::std::add_pointer

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

`asc::std::add_pointer` yields the type obtained by adding the qualification, reference, or pointer indicated by the name.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<class T> struct add_pointer;
} // namespace asc::std
```

## Constraints

- First the reference of `T` is removed, then a pointer type is formed; special function types for which a pointer cannot be formed keep the original type. This operation does not take an address.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // Both ::type and _t yield the pointer type
    static_assert(asc::std::is_same_v<asc::std::add_pointer<int>::type, int*>);
    // A reference argument has its reference removed before the pointer is added
    static_assert(asc::std::is_same_v<asc::std::add_pointer_t<int&>, int*>);
    static_assert(asc::std::is_same_v<asc::std::add_pointer_t<void>, void*>);
    // Counterexample: after adding a pointer, the type is not the original int
    static_assert(!asc::std::is_same_v<asc::std::add_pointer_t<int>, int>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
