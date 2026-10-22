# asc::std::mdspan::static_extent

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

`asc::std::mdspan::static_extent` returns the compile-time static extent of the specified dimension.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

Member of: [`asc::std::mdspan`](mdspan.md).

```cpp
// Excerpt of the declaration inside the asc::std::mdspan class; template parameters and other members are provided by the owning class.
static constexpr size_t static_extent(rank_type rank_index) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `rank_index` | Input | The number of the dimension whose static extent is to be queried, starting from 0; it must satisfy `rank_index` < `rank()`, and `dynamic_extent` is returned when that dimension is dynamic. |

## Return Value

| Return type | Description |
| --- | --- |
| `size_t` | Returns the compile-time static extent of the specified dimension. |

## Constraints

- This query is provided starting from C++17; for the element access forms and language conditions, see [`mdspan`](mdspan.md#constraints).

- A static query; `rank_index` must be smaller than `rank()`, and a dynamic dimension returns the `dynamic_extent` marker.

## Example

The following Host snippet demonstrates the call with concrete capacities or dimensions; the object and indices must satisfy the constraints on this page.

```cpp
#include <asc/std/mdspan>
#include <asc/std/cstddef>

decltype(auto) example()
{
    return asc::std::mdspan<int, asc::std::extents<asc::std::size_t, 2, 3>, asc::std::layout_right, asc::std::default_accessor<int>>::static_extent(0);
}
```

## Related APIs

- [`asc::std::mdspan`](mdspan.md)
- [API list for this header](asc_std_mdspan.md)
