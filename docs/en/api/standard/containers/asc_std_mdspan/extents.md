# asc::std::extents

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

Header: `<asc/std/mdspan>`.

`asc::std::extents` holds the static and dynamic dimension lengths of a multidimensional index space.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Declaration

```cpp
namespace asc::std {
template<class IndexType, size_t ...StaticExtents> class extents;
} // namespace asc::std
```

## Constraints

- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/mdspan>

bool example()
{
    using shape = asc::std::extents<int, 2, asc::std::dynamic_extent>;
    shape sizes(3);
    static_assert(shape::rank() == 2 && shape::rank_dynamic() == 1);
    return sizes.extent(0) == 2 && sizes.extent(1) == 3;
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
