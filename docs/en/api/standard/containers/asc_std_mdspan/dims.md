# asc::std::dims

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

`asc::std::dims` constructs a runtime dimension-length type with the specified number of dimensions.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Declaration

```cpp
namespace asc::std {
template<size_t Rank, class IndexType = size_t>
using dims = dextents<IndexType, Rank>;
}
```

## Constraints

- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/mdspan>
#include <asc/std/type_traits>

using shape_type = asc::std::dims<2>;
static_assert(asc::std::is_same_v<shape_type::index_type, asc::std::size_t>);
static_assert(shape_type::rank_dynamic() == 2);

bool example()
{
    const shape_type shape(2, 3);
    return shape.extent(0) == 2 && shape.extent(1) == 3;
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
