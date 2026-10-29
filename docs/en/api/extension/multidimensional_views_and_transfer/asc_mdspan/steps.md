# asc::steps

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

Header: `<asc/mdspan>`.

`asc::steps` is an alias for Rank dynamic strides, with ptrdiff_t as the default offset type.

## Declaration

```cpp
namespace asc {
template <asc::std::size_t Rank, class OffsetType = asc::std::ptrdiff_t>
using steps = asc::dstrides<OffsetType, Rank>;
}  // namespace asc
```

## Constraints

- Strides are counted in elements; the number of construction arguments must equal the total number of dimensions or the number of dynamic slots, and queried dimension indices must be less than the rank. The strides and subsequent index multiply-adds must be representable in offset_type.


## Example

The following snippet shows the alias type with concrete template arguments.

```cpp
#include <asc/mdspan>

bool example()
{
    asc::steps<2, int> values(2, 1);
    return values.rank() == 2 && values.rank_dynamic() == 2 &&
        values.stride(0) == 2 && values.stride(1) == 1;
}
```

## Related APIs

- [API list for this header](asc_mdspan.md)
