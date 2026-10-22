# asc::std::submdspan_extents

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

`asc::std::submdspan_extents` computes the result `extents` from the slice of each dimension, without creating an element view or accessing storage. An integer slice removes that dimension, `full_extent` keeps that dimension, and a range or strided slice produces the corresponding extent.

## Function Prototype

```cpp
namespace asc::std {
template<class Extents, class... Slices,
    enable_if_t<(Extents::rank() == sizeof...(Slices)), int> = 0>
constexpr auto submdspan_extents(const Extents& source, Slices... slices);
}
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Extents` | The source dimension type. |
| `Slices` | The pack of per-dimension slice types; the count must equal the source `rank()`. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `source` | Input | The source per-dimension extents; only metadata is read. |
| `slices` | Input | For each dimension, an integer index, `full_extent`, a half-open range [first,last), or a `strided_slice`. The extent of a strided slice is the covering length, and the result count is ceil(extent/stride). |

## Return Value

| Return type | Description |
| --- | --- |
| The deduced `extents` type | Stores the remaining dimensions and their extents by value; an integer slice keeps no dimension, and extents determinable at compile time keep a static extent. The result does not borrow source and stores no element addresses. |

## Constraints

- The number of slices must equal source.`rank()`.
- An integer slice must be within the valid index range of the corresponding dimension; a half-open range must satisfy 0 <= first <= last <= the extent of the source dimension.
- The offset and extent of a `strided_slice` must cover a valid subinterval within the source dimension, and stride must be positive.
- All index, extent, difference, and stride computations must be representable by the result `index_type`.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/mdspan>
#include <asc/std/utility>

bool example()
{
    using shape_type = asc::std::extents<asc::std::size_t, 4, 5>;
    const auto interval = asc::std::submdspan_extents(shape_type{}, asc::std::full_extent,
        asc::std::pair<int, int>{1, 4});
    const auto selected = asc::std::submdspan_extents(shape_type{}, asc::std::full_extent, 2);
    static_assert(decltype(selected)::rank() == 1);
    return interval.extent(0) == 4 && interval.extent(1) == 3 && selected.extent(0) == 4;
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
