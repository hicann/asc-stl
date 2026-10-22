# asc::std::submdspan_mapping

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

`asc::std::submdspan_mapping` computes the result layout mapping and the element offset relative to the source data origin from per-dimension slice specifications, without reading or owning element storage.

## Function Prototype

The following is a declaration summary with the internal SFINAE filtering parameters omitted; for the participation conditions, see Constraints.

```cpp
namespace asc::std {
template<class LayoutMapping, class... Slices>
constexpr auto submdspan_mapping(const LayoutMapping& mapping, Slices... slices);
}
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `LayoutMapping` | The source mapping type; mapping overloads are currently provided for layout_left, layout_right, and layout_stride. |
| `Slices` | The list of slice types for each source dimension; the length must equal the source rank. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `mapping` | Input | Provides the per-dimension extents, strides, and the index-to-linear-offset mapping; valid for the duration of the call. |
| `slices` | Input | Provides, in source dimension order, integer indices, full_extent, half-open range pairs, or strided_slice. An integer index removes that dimension; the other forms keep it. |

## Return Value

Returns `submdspan_mapping_result<ResultMapping>`. The `mapping` member is the independently stored result mapping, and `offset` is the element offset relative to the source origin, not a byte offset. When contiguity is preserved, the result may keep the source's left/right layout; otherwise a `layout_stride` that keeps the original strides is used.

## Constraints

- The number of slices equals the number of dimensions of the source mapping, and the result rank equals the number of non-integer slices.
- An integer index satisfies `0 <= index < extent`.
- A range pair denotes the half-open interval `[first, last)` satisfying `0 <= first <= last <= extent`; for example, `[1, 3)` keeps two positions.
- `full_extent` keeps the full range of the current dimension.
- The offset, covering range, and positive stride of a `strided_slice` must place all access positions within the source dimensions; the kept extent is computed from the covering range and the stride.
- The computed mappings, indices, strides, and element offsets must be representable by the corresponding integer types.
- The operation is a synchronous computation; when the constant-expression conditions are met, it can be evaluated at compile time. The returned mapping does not borrow the source mapping object.

## Example

The following example verifies the original strides kept when selecting a column and trimming an inner dimension.

```cpp
#include <asc/std/mdspan>
#include <asc/std/utility>

bool example()
{
    using shape = asc::std::extents<int, 2, 3>;
    asc::std::layout_right::mapping<shape> mapping(shape{});
    const auto column = asc::std::submdspan_mapping(mapping, asc::std::full_extent, 1);
    const auto range = asc::std::submdspan_mapping(
        mapping, asc::std::full_extent, asc::std::pair<int, int>{1, 3});
    return column.offset == 1 && column.mapping.stride(0) == 3 &&
        range.offset == 1 && range.mapping.extents().extent(1) == 2 &&
        range.mapping(1, 1) == 4;
}
```

## Related APIs

- [submdspan](submdspan.md): applies the result mapping to an actual data view.
- [strided_slice](strided_slice.md): the offset, range, and stride of a strided slice.
