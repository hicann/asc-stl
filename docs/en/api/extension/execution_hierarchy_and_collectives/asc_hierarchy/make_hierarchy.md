# asc::make_hierarchy

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

Header: `<asc/hierarchy>`.

`asc::make_hierarchy` constructs a SIMT hierarchy description from grid and block sizes.

## Function Prototype

```cpp
namespace asc {
constexpr asc::simt_hierarchy make_hierarchy(asc::level_dimensions<asc::grid_level> grid, asc::level_dimensions<asc::block_level> block) noexcept;
} // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `grid` | Input | The grid-level dimension description (level_dimensions<grid_level>, obtained from grid_dims): carries the 3D grid sizes, each dimension non-zero. |
| `block` | Input | The block-level dimension description (level_dimensions<block_level>, obtained from block_dims): carries the 3D block sizes, each dimension non-zero. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::simt_hierarchy` | Returns the execution hierarchy or launch dimensions composed of the current grid and thread block sizes. |

## Constraints

- Provides C++17 constexpr Host/Device hierarchy interfaces.
- Values with extents require every dimension to be non-zero.
- The total extent count is computed as x*y*z in unsigned 64-bit arithmetic.

## Example

This Host example uses concrete types or dimensions and checks independent expected values without querying a running Device context.

```cpp
#include <asc/hierarchy>

bool example()
{
    const auto hierarchy = asc::make_hierarchy(asc::grid_dims<2, 3, 4>(), asc::block_dims<8, 4, 2>());
    return hierarchy.grid_extents.x == 2 && hierarchy.grid_extents.y == 3 && hierarchy.grid_extents.z == 4 &&
        hierarchy.block_extents.x == 8 && hierarchy.block_extents.y == 4 && hierarchy.block_extents.z == 2 &&
        hierarchy.count(asc::grid) == 24 && hierarchy.count(asc::block) == 64;
}
```

## Related APIs

- [API list for this header](asc_hierarchy.md)
