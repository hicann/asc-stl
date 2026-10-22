# asc::std::submdspan

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

`asc::std::submdspan` creates a subview from a multidimensional view according to per-dimension slice specifications; the returned view stores its own mapping and accessor and borrows the original element storage.

## Function Prototype

The following is a declaration summary with the internal SFINAE filtering parameters omitted; the slices must be usable for the source layout's `submdspan_mapping`.

```cpp
namespace asc::std {
template<class T, class Extents, class Layout, class Accessor, class... Slices>
constexpr auto submdspan(
    const mdspan<T, Extents, Layout, Accessor>& source, Slices... slices);
}
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type; the subview accesses the same objects in the original storage. |
| `Extents` | The static/dynamic dimension information and index type of the source view. |
| `Layout` | The source layout policy; it determines its mapping type. |
| `Accessor` | The source accessor type; the subview uses its offset_policy. |
| `Slices` | The list of per-dimension slice types; the count equals the rank of the source view. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `source` | Input | The view to be sliced; the function reads its handle, mapping, and accessor, and does not own or copy elements. |
| `slices` | Input | Per-dimension specification of an integer index, full_extent, a half-open range, or strided_slice; for the exact boundaries, see submdspan_mapping. |

## Return Value

Returns an mdspan with the corresponding element type, result dimensions, result layout, and `Accessor::offset_policy`. The original view object may be destroyed before the subview, but the underlying element storage and the resources the accessor depends on must remain valid.

## Constraints

- The number and values of the slices must satisfy the requirements of the source mapping; every computed access position must be in valid storage.
- The returned view does not own the storage; modifications through a writable subview act directly on the original elements.
- A result that keeps the original strides is not necessarily contiguous; contiguity must not be assumed merely from the product of the result dimensions.
- The corresponding layout mapping and accessor must be available at the selected execution location.

## Example

```cpp
#include <asc/std/mdspan>

bool example()
{
    int values[6] = {1, 2, 3, 4, 5, 6};
    asc::std::mdspan<int, asc::std::extents<int, 2, 3>> view(values);
    auto row = asc::std::submdspan(view, 1, asc::std::full_extent);
    auto column = asc::std::submdspan(view, asc::std::full_extent, 1);
    column(1) = 9;
    return row.extent(0) == 3 && row(0) == 4 &&
        column.extent(0) == 2 && column(0) == 2 && values[4] == 9;
}
```

## Related APIs

- [submdspan_mapping](submdspan_mapping.md): the slice forms and layout computation rules.
- [mdspan](mdspan.md): a borrowing multidimensional data view.
