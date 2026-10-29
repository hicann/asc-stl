# asc::simt_hierarchy::extents

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

`asc::simt_hierarchy::extents` returns the 3D extents of the specified SIMT level.

## Function Prototype

Member of: [`asc::simt_hierarchy`](simt_hierarchy.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::simt_hierarchy; template parameters and other members are provided by the enclosing class.
constexpr asc::extent3d extents(asc::block_level) const noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::simt_hierarchy; template parameters and other members are provided by the enclosing class.
constexpr asc::extent3d extents(asc::grid_level) const noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| Level tag (unnamed parameter) | Input | Level tag: pass asc::block (a block_level value) to select the block level; returns the extent3d 3D sizes of that level. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| Level tag (unnamed parameter) | Input | Level tag: pass asc::grid (a grid_level value) to select the grid level; returns the extent3d 3D sizes of that level. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::extent3d` | Returns the execution hierarchy or launch dimensions composed of the current grid and thread block sizes. |
| Prototype 2 | `asc::extent3d` | Returns the execution hierarchy or launch dimensions composed of the current grid and thread block sizes. |

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
    const auto grid = hierarchy.extents(asc::grid);
    const auto block = hierarchy.extents(asc::block);
    return grid.x == 2 && grid.y == 3 && grid.z == 4 &&
        block.x == 8 && block.y == 4 && block.z == 2;
}
```

## Related APIs

- [`asc::simt_hierarchy`](simt_hierarchy.md)
- [API list for this header](asc_hierarchy.md)
