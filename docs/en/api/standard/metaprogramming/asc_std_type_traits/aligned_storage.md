# asc::std::aligned_storage

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

`asc::std::aligned_storage` computes a raw storage type that satisfies the specified size and alignment.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

`asc::std::aligned_storage<Len, Align>::type` is a trivial standard-layout storage type that holds at least `Len` bytes and satisfies the alignment `Align`. `Align` may be omitted; it defaults to the largest value not greater than `Len` chosen by the implementation from the alignment values of supported fundamental types.

The following shows the usage of explicit alignment and default alignment:

```cpp
using ExplicitStorage = asc::std::aligned_storage<16, 8>::type;
using DefaultStorage = asc::std::aligned_storage<16>::type;
```

## Constraints

- `Len > 0`; an explicit `Align` must be an alignment value supported by the implementation.
- The storage itself is not a constructed target object; it can be accessed as the target type only after placement construction.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // _t is the same as ::type; the storage size is rounded up to the alignment value
    static_assert(asc::std::is_same_v<asc::std::aligned_storage_t<16, 4>, asc::std::aligned_storage<16, 4>::type>);
    static_assert(sizeof(asc::std::aligned_storage_t<16, 4>) == 16);
    static_assert(alignof(asc::std::aligned_storage_t<16, 4>) == 4);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
