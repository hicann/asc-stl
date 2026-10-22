# asc::std::aligned_union

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

`asc::std::aligned_union` computes a raw storage type that can hold the listed types and satisfies the maximum alignment.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<size_t Len, class Type0, class ...Types> struct aligned_union;
} // namespace asc::std
```

## Constraints

- The type parameter list must be non-empty, and each listed type must be usable with `sizeof` and `alignof`.
- `alignment_value` is the maximum of the alignment values of the listed types; the storage size is at least the maximum of `Len` and the sizes of the listed types, rounded up to the alignment requirement.
- The result is a raw storage type; before using an object stored in it, the object's lifetime must be correctly established, and after use it must be destroyed according to its type.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    using union_type = asc::std::aligned_union<8, char, int>;
    // alignment_value is the maximum of the member alignments
    static_assert(union_type::alignment_value == alignof(int));
    // _t is the same as ::type; the storage holds at least the requested length and the member sizes
    static_assert(asc::std::is_same_v<asc::std::aligned_union_t<8, char, int>, union_type::type>);
    static_assert(sizeof(asc::std::aligned_union_t<8, char, int>) == 8);
    static_assert(alignof(asc::std::aligned_union_t<8, char, int>) == alignof(int));
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
