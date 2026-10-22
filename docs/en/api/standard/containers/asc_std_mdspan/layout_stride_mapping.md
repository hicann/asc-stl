# asc::std::layout_stride::mapping

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

`layout_stride::mapping<Extents>` maps multidimensional indices to linear storage offsets with per-dimension strides provided by the caller.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Declaration

Member of: [`asc::std::layout_stride`](layout_stride.md).

```cpp
// Excerpt of the declaration inside the asc::std::layout_stride class; template parameters and other members are provided by the owning class.
template<class Extents> class mapping;
```

## Constraints

- Host, AI Core SIMD programming, and AI Core SIMT programming are compatible with the plain pointer domain.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>

bool example()
{
    using shape = asc::std::extents<int, 2, 3>;
    asc::std::array<int, 2> strides{{4, 1}};
    asc::std::layout_stride::mapping<shape> mapping(shape{}, strides);
    return mapping(1, 2) == 6 && mapping.required_span_size() == 7 && !mapping.is_exhaustive();
}
```

## Related APIs

- [`asc::std::layout_stride`](layout_stride.md)
- [API list for this header](asc_std_mdspan.md)
