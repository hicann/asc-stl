# asc::std::strided_slice

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

`asc::std::strided_slice` represents the form of multidimensional slicing, dimension ranges, or layout adaptation.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Declaration

```cpp
namespace asc::std {
template<class OffsetType, class ExtentType, class StrideType> struct strided_slice;
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
    asc::std::strided_slice<int, int, int> slice{1, 5, 2};
    return slice.offset == 1 && slice.extent == 5 && slice.stride == 2;
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
