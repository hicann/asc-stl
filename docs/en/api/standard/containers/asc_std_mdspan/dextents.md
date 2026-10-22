# asc::std::dextents

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

`asc::std::dextents` constructs a runtime dimension-length type with the specified number of dimensions.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Declaration

dextents is an alias of `extents` in which every dimension is `dynamic_extent`. The following queries the resulting type with a public template; dynamic_shape_type is only an example name, not another public interface.

```cpp
template<class IndexType, asc::std::size_t Rank>
using dynamic_shape_type = asc::std::dextents<IndexType, Rank>;
```

## Constraints

- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/mdspan>

using shape_type = asc::std::dextents<int, 3>;
static_assert(shape_type::rank() == 3 && shape_type::rank_dynamic() == 3);

bool example()
{
    const shape_type shape(2, 3, 4);
    return shape.extent(0) == 2 && shape.extent(1) == 3 && shape.extent(2) == 4;
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
