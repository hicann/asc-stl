# asc::std::aligned_union::alignment_value

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

`asc::std::aligned_union::alignment_value` provides at compile time the value or alignment requirement of the corresponding type trait.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

`alignment_value` is a static `const size_t` integral constant of `aligned_union<Len, First, Types...>` that can be used in constant expressions; its value is the maximum of the alignment values of all the listed types.

```cpp
using storage = asc::std::aligned_union<16, int, float>;
static_assert(storage::alignment_value == (alignof(int) > alignof(float) ? alignof(int) : alignof(float)));
```

## Constraints

- The type parameter list must be non-empty, and each listed type must be usable with `sizeof` and `alignof`.
- `alignment_value` is the maximum of the alignment values of the listed types; the storage size is at least the maximum of `Len` and the sizes of the listed types, rounded up to the alignment requirement.
- The result is a raw storage type; before using an object stored in it, the object's lifetime must be correctly established, and after use it must be destroyed according to its type.

## Example

The following Host snippet instantiates the type trait on this page with concrete type arguments.

```cpp
#include <asc/std/type_traits>

static_assert((asc::std::aligned_union<16, int, float>::alignment_value) == (alignof(int) > alignof(float) ? alignof(int) : alignof(float)));
```

## Related APIs

- [`asc::std::aligned_union`](aligned_union.md)
- [API list for this header](asc_std_type_traits.md)
