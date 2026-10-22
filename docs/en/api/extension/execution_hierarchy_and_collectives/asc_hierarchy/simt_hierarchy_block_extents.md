# asc::simt_hierarchy::block_extents

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

`asc::simt_hierarchy::block_extents` holds the 3D block extents in the SIMT hierarchy.

## Declaration

Member of: [`asc::simt_hierarchy`](simt_hierarchy.md).

```cpp
// Excerpt of the declaration inside asc::simt_hierarchy; template parameters and other members are provided by the enclosing class.
asc::extent3d block_extents;
```

## Constraints

- Provides C++17 constexpr Host/Device hierarchy interfaces.
- Values with extents require every dimension to be non-zero.
- The total extent count is computed as x*y*z in unsigned 64-bit arithmetic.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/hierarchy>

bool example()
{
    asc::simt_hierarchy hierarchy{asc::extent3d{2, 1, 1}, asc::extent3d{32, 1, 1}};
    return hierarchy.grid_extents.count() == 2 && hierarchy.block_extents.count() == 32;
}
```

## Related APIs

- [`asc::simt_hierarchy`](simt_hierarchy.md)
- [API list for this header](asc_hierarchy.md)
