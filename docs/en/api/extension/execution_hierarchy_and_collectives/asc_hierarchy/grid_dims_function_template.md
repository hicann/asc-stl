# asc::grid_dims (Function template)

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

`asc::grid_dims` creates a 3D size description for the grid level.

## Function Prototype

```cpp
namespace asc {
template<unsigned int X, unsigned int Y = 1, unsigned int Z = 1> constexpr asc::level_dimensions<asc::grid_level> grid_dims() noexcept;
} // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `X` | A compile-time value used by the selected prototype; the allowed range is bounded by the declaration and the constraints. |
| `Y` | A compile-time value used by the selected prototype; the allowed range is bounded by the declaration and the constraints. |
| `Z` | A compile-time value used by the selected prototype; the allowed range is bounded by the declaration and the constraints. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::level_dimensions<asc::grid_level>` | Returns the execution hierarchy or launch dimensions composed of the current grid and thread block sizes. |

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
    const auto dimensions = asc::grid_dims<2, 3, 4>();
    static_assert(asc::std::is_same_v<decltype(dimensions), const asc::level_dimensions<asc::grid_level>>);
    const auto extents = dimensions.extents;
    return extents.x == 2 && extents.y == 3 && extents.z == 4 && extents.count() == 24;
}
```

## Related APIs

- [API list for this header](asc_hierarchy.md)
