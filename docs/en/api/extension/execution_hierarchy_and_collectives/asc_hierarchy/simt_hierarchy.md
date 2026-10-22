# asc::simt_hierarchy

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

`asc::simt_hierarchy` describes the 3D hierarchy relationship between the SIMT grid and blocks.

## Declaration

```cpp
namespace asc {
struct simt_hierarchy;
}  // namespace asc
```

## Constraints

- The per-axis sizes must satisfy the legal launch limits of the current device, and x*y*z must be representable in unsigned long long; being non-zero alone is not sufficient to guarantee this condition. Value operations here do not validate actual hardware limits.

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

- [API list for this header](asc_hierarchy.md)
