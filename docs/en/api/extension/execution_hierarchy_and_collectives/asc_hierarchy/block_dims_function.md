# asc::block_dims (Function)

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

`asc::block_dims` creates a 3D size description for the block level.

## Function Prototype

```cpp
namespace asc {
constexpr asc::level_dimensions<asc::block_level> block_dims(asc::extent3d extents) noexcept;
} // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `extents` | Input | The valid length of each dimension; the number of dimensions and the value ranges must satisfy the constraints on this page. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::level_dimensions<asc::block_level>` | Returns the execution hierarchy or launch dimensions composed of the current grid and thread block sizes. |

## Constraints

- Provides C++17 constexpr Host/Device hierarchy interfaces.
- Values with extents require every dimension to be non-zero.
- The total extent count is computed as x*y*z in unsigned 64-bit arithmetic.

## Example

This Host example uses concrete types or dimensions and checks independent expected values without querying a running Device context.

```cpp
#include <asc/hierarchy>
#include <asc/std/type_traits>

bool example()
{
    const auto dimensions = asc::block_dims(asc::extent3d(8, 4, 2));
    static_assert(asc::std::is_same_v<decltype(dimensions), const asc::level_dimensions<asc::block_level>>);
    const auto extents = dimensions.extents;
    return extents.x == 8 && extents.y == 4 && extents.z == 2 && extents.count() == 64;
}
```

## Related APIs

- [API list for this header](asc_hierarchy.md)
