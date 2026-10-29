# asc::simt_hierarchy::count

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

`asc::simt_hierarchy::count` returns the number of linear elements contained in the specified SIMT level.

## Function Prototype

Member of: [`asc::simt_hierarchy`](simt_hierarchy.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::simt_hierarchy; template parameters and other members are provided by the enclosing class.
constexpr unsigned long long count(asc::block_level) const noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::simt_hierarchy; template parameters and other members are provided by the enclosing class.
constexpr unsigned long long count(asc::grid_level) const noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| Level tag (unnamed parameter) | Input | Level tag: pass asc::block (a block_level value) to select the block level; returns the total number of elements x*y*z of that level's 3D sizes. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| Level tag (unnamed parameter) | Input | Level tag: pass asc::grid (a grid_level value) to select the grid level; returns the total number of elements x*y*z of that level's 3D sizes. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `unsigned long long` | Returns the unsigned 64-bit count x*y*z of the selected 3D extents; it does not return a size object. |
| Prototype 2 | `unsigned long long` | Returns the unsigned 64-bit count x*y*z of the selected 3D extents; it does not return a size object. |

## Constraints

- The per-axis sizes must satisfy the legal launch limits of the current device, and x*y*z must be representable in unsigned long long; being non-zero alone is not sufficient to guarantee this condition. Value operations here do not validate actual hardware limits.

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
    return hierarchy.count(asc::grid) == 24 && hierarchy.count(asc::block) == 64;
}
```

## Related APIs

- [`asc::simt_hierarchy`](simt_hierarchy.md)
- [API list for this header](asc_hierarchy.md)
