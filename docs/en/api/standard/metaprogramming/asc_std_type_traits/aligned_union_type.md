# asc::std::aligned_union::type

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

`asc::std::aligned_union::type` provides the member type computed by the type trait, mapping, or adaptor.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

`type` is the storage type that satisfies the size and alignment described below. Query it through the owning class:

```cpp
using storage_type = typename asc::std::aligned_union<16, int, float>::type;
```

## Constraints

- The type parameter list must be non-empty, and each listed type must be usable with `sizeof` and `alignof`.
- `alignment_value` is the maximum of the alignment values of the listed types; the storage size is at least the maximum of `Len` and the sizes of the listed types, rounded up to the alignment requirement.
- The result is a raw storage type; before using an object stored in it, the object's lifetime must be correctly established, and after use it must be destroyed according to its type.

## Example

The following Host example checks the interface result against an independent expected type or value.

```cpp
#include <asc/std/type_traits>

using storage_type = typename asc::std::aligned_union<0, int, double>::type;
static_assert(sizeof(storage_type) >= sizeof(double));
static_assert(alignof(storage_type) >= alignof(double));
```

## Related APIs

- [`asc::std::aligned_union`](aligned_union.md)
- [API list for this header](asc_std_type_traits.md)
