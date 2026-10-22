# asc::layout_stride_relaxed

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

`asc::layout_stride_relaxed` provides an mdspan layout mapping policy that allows relaxed stride constraints.

## Declaration

```cpp
namespace asc {
struct layout_stride_relaxed;
}  // namespace asc
```

## Constraints

- The mapping does not own the data; coordinates must be within the extents, the multiply-add of signed strides and the origin must be representable, and all positions covered by the mapping must belong to valid storage. A zero stride can produce duplicate addresses, so is_unique must not be assumed to be true by default.

- The default and Host/GM/UB accessors use non-negative element offsets; when negative strides are used manually, the mapping origin must guarantee that the offsets of all valid coordinates are non-negative and still within the storage.
- DLPack import preserves signed strides and expresses reversed views by relocating the handle and setting a non-negative origin; stride spans that cannot be represented return false and leave the output unchanged.


## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/mdspan>
#include <asc/std/mdspan>

bool example()
{
    using Extents = asc::std::extents<int, 2, 3>;
    asc::dstrides<asc::std::ptrdiff_t, 2> strides(5, 1);
    asc::layout_stride_relaxed::mapping<Extents> mapping(Extents{}, strides);
    return mapping(1, 2) == 7;
}
```

## Related APIs

- [API list for this header](asc_mdspan.md)
