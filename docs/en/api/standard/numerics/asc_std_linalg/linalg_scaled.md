# asc::std::linalg::scaled

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

Header: `<asc/std/linalg>`.

`asc::std::linalg::scaled` creates a non-owning multidimensional view that scales elements by a scalar.

Standard semantics reference: [cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg).

## Function Prototype

The following return type is expressed through the accessor's public member type; `add_const_t` is equivalent to the return type in the header.

```cpp
namespace asc::std::linalg {
template<class ScalingFactor, class Element, class Extents, class Layout, class Accessor>
constexpr mdspan<add_const_t<typename scaled_accessor<ScalingFactor, Accessor>::element_type>,
    Extents, Layout, scaled_accessor<ScalingFactor, Accessor>>
scaled(ScalingFactor scaling_factor, mdspan<Element, Extents, Layout, Accessor> input);
} // namespace asc::std::linalg
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ScalingFactor` | Type of the scaling factor; must be multipliable with element values. |
| `Element` | Element type of the underlying multidimensional view. |
| `Extents` | Extents type of the underlying multidimensional view. |
| `Layout` | Layout type of the underlying multidimensional view. |
| `Accessor` | Accessor type of the underlying multidimensional view. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `scaling_factor` | Input | Scalar scaling factor; every element in the view is read after being scaled by this factor. |
| `input` | Input | Provides a non-owning multidimensional data view; the underlying storage must remain valid while the view is in use. |

## Return Value

| Return type | Description |
| --- | --- |
| `mdspan<add_const_t<typename scaled_accessor<ScalingFactor, Accessor>::element_type>, Extents, Layout, scaled_accessor<ScalingFactor, Accessor>>` | Returns a non-owning multidimensional view that scales elements by a scalar. |

## Constraints

- The scaling factor must be multipliable with the underlying element type; the result type is determined by the multiplication expression.
- The returned view borrows the storage of `input` and copies the mapping and the scaling accessor; the underlying storage must remain valid while the returned view is in use.
- Reads compute the result through the scaling accessor and do not modify the underlying elements; device use additionally requires the underlying accessor, the storage address space, and the multiplication operation to support the corresponding programming mode.

## Example

The following Host example provides concrete inputs and checks the results.

```cpp
#include <asc/std/linalg>
#include <asc/std/cstddef>

bool example()
{
    int values[6] = {1, 2, 3, 4, 5, 6};
    using Extents = asc::std::extents<asc::std::size_t, 2, 3>;
    asc::std::mdspan<int, Extents> view(values);
    const auto scaled = asc::std::linalg::scaled(2, view);
    // Read the borrowing view while values is still valid; do not return the view beyond the array's lifetime.
    return scaled(1, 2) == 12 && values[5] == 6;
}
```

## Related APIs

- [API list for this header](asc_std_linalg.md)
