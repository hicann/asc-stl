# asc::dstrides

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

`asc::dstrides` is an mdspan strides type with dynamic strides.

## Declaration

`asc::dstrides<OffsetType, Rank>` is an alias template equivalent to `asc::strides` with `Rank` `asc::dynamic_stride` arguments, so the caller does not need to name the internal helper type.

```cpp
using Rank2 = asc::dstrides<int, 2>;
using Equivalent = asc::strides<int, asc::dynamic_stride, asc::dynamic_stride>;
```

## Constraints

- `OffsetType` is an integer type that can represent strides, and `Rank` is the number of dimensions.
- Strides for all dimensions are provided at construction; strides may be negative, and subsequent view accesses must still fall within valid storage.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/mdspan>
#include <asc/std/type_traits>

bool example()
{
    using Strides = asc::dstrides<int, 2>;
    static_assert(asc::std::is_same_v<Strides, asc::strides<int, asc::dynamic_stride, asc::dynamic_stride>>);
    Strides strides(3, 1);
    return strides.stride(0) == 3 && strides.stride(1) == 1;
}
```

## Related APIs

- [API list for this header](asc_mdspan.md)
