# asc::std::submdspan_mapping_result

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

`asc::std::submdspan_mapping_result` produces a non-owning subview of an existing multidimensional view, or the corresponding mapping, from slice specifications.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Declaration

```cpp
namespace asc::std {
template<class Mapping> struct submdspan_mapping_result;
} // namespace asc::std
```

## Constraints

- All valid combinations of integer rank-reducing/full/pair-like/strided slices, zero and any rank, static/dynamic/mixed/empty extents, layout_left/layout_right/layout_stride sources, and standard-layout preservation or layout_stride fallback.
- Host, AI Core SIMD programming, and AI Core SIMT programming are compatible with the plain pointer domain.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/mdspan>

bool example()
{
    using shape = asc::std::extents<int, 2, 3>;
    asc::std::layout_right::mapping<shape> mapping(shape{});
    const auto row = asc::std::submdspan_mapping(mapping, 1, asc::std::full_extent);
    return row.offset == 3 && row.mapping.extents().extent(0) == 3;
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
