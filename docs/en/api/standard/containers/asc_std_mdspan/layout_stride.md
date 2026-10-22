# asc::std::layout_stride

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

`asc::std::layout_stride` maps multidimensional indices to underlying storage offsets according to the specified layout.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Declaration

```cpp
namespace asc::std {
struct layout_stride;
} // namespace asc::std
```

## Constraints

- Host, AI Core SIMD programming, and AI Core SIMT programming are compatible with the plain pointer domain.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/mdspan>
#include <asc/std/type_traits>
#include <asc/std/array>

bool example()
{
    using Extents = asc::std::extents<int, 2, 3>;
    asc::std::array<int, 2> strides{5, 1};
    asc::std::layout_stride::mapping<Extents> mapping(Extents{}, strides);
    return mapping(1, 2) == 7;
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
