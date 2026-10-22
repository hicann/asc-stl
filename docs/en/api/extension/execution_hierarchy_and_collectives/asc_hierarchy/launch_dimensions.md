# asc::launch_dimensions

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

`asc::launch_dimensions` holds both the 3D grid and block sizes used by a kernel launch.

## Declaration

```cpp
namespace asc {
struct launch_dimensions;
} // namespace asc
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
    asc::launch_dimensions dimensions{asc::extent3d{2, 1, 1}, asc::extent3d{32, 1, 1}};
    return dimensions.grid.count() == 2 && dimensions.block.count() == 32;
}
```

## Related APIs

- [API list for this header](asc_hierarchy.md)
