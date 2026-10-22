# asc::std::mdspan::stride

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

`asc::std::mdspan::stride` returns the stride between adjacent elements of the specified dimension.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

Member of: [`mdspan`](mdspan.md). This query is not declared `noexcept`.

```cpp
constexpr index_type stride(rank_type rank_index) const;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `rank_index` | Input | The number of the dimension whose stride is to be queried, starting from 0; it must satisfy `rank_index` < `rank()`, and the number of elements by which adjacent elements of that dimension are separated is returned. |

## Return Value

| Return type | Description |
| --- | --- |
| `index_type` | Returns the stride between adjacent elements of the specified dimension. |

## Constraints

- This query is provided starting from C++17; for the element access forms and language conditions, see [`mdspan`](mdspan.md#constraints).

- `rank_index` must be smaller than `rank()`; the mapping must support the stride query, and the result must be representable by `index_type`.

## Example

The following Host snippet demonstrates the call with concrete capacities or dimensions; the object and indices must satisfy the constraints on this page.

```cpp
#include <asc/std/mdspan>
#include <asc/std/cstddef>

decltype(auto) example(const asc::std::mdspan<int, asc::std::extents<asc::std::size_t, 2, 3>, asc::std::layout_right, asc::std::default_accessor<int>>& view)
{
    return view.stride(0);
}
```

## Related APIs

- [`asc::std::mdspan`](mdspan.md)
- [API list for this header](asc_std_mdspan.md)
