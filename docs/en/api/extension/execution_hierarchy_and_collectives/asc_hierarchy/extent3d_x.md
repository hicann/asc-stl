# asc::extent3d::x

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

`asc::extent3d::x` holds the size of the X dimension of the 3D extents.

## Declaration

Member of: [`asc::extent3d`](extent3d.md).

```cpp
// Excerpt of the declaration inside asc::extent3d; template parameters and other members are provided by the enclosing class.
unsigned int x;
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
    asc::extent3d dimensions(2, 3, 4);
    return dimensions.x == 2 && dimensions.y == 3 && dimensions.z == 4 && dimensions.count() == 24;
}
```

## Related APIs

- [`asc::extent3d`](extent3d.md)
- [API list for this header](asc_hierarchy.md)
