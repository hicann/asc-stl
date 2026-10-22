# asc::extent3d::`operator!=`

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

`asc::extent3d::operator!=` compares whether at least one dimension of two 3D extents differs.

## Function Prototype

Member of: [`asc::extent3d`](extent3d.md).

```cpp
// Excerpt of the declaration inside asc::extent3d; template parameters and other members are provided by the enclosing class.
constexpr bool operator!=(asc::extent3d other) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input | The other operand of the comparison; this comparison does not modify the object. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- Provides C++17 constexpr Host/Device hierarchy interfaces.
- Values with extents require every dimension to be non-zero.
- The total extent count is computed as x*y*z in unsigned 64-bit arithmetic.

## Example

The following Host snippet demonstrates the interface on this page with concrete types; the lifetimes of objects and pointers must satisfy the constraints on this page.

```cpp
#include <asc/hierarchy>

decltype(auto) example(asc::extent3d left, asc::extent3d right)
{
    const bool different = left != right;
    return different;
}
```

## Related APIs

- [`asc::extent3d`](extent3d.md)
- [API list for this header](asc_hierarchy.md)
