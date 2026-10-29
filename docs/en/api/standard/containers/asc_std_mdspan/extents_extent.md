# asc::std::extents::extent

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

`asc::std::extents::extent` returns the dynamic or static extent of the specified dimension.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

Member of: [`asc::std::extents`](extents.md).

```cpp
// Excerpt of the declaration inside the asc::std::extents class; template parameters and other members are provided by the owning class.
constexpr index_type extent(rank_type index) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `index` | Input | The number of the dimension whose extent is to be queried, starting from 0; it must be smaller than the total number of dimensions (rank()), and the static or dynamic extent of that dimension is returned. |

## Return Value

| Return type | Description |
| --- | --- |
| `index_type` | Returns the dynamic or static extent of the specified dimension. |

## Constraints

- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host snippet demonstrates the call with concrete types; pointers, ranges, and indices must satisfy the constraints on this page.

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>
#include <cstddef>
#include <type_traits>

bool example()
{
    asc::std::extents<int, 2, 3> shape;
    return shape.extent(0) == 2 && shape.extent(1) == 3;
}
```

## Related APIs

- [`asc::std::extents`](extents.md)
- [API list for this header](asc_std_mdspan.md)
