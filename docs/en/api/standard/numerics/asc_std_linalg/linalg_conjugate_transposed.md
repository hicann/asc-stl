# asc::std::linalg::conjugate_transposed

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

`asc::std::linalg::conjugate_transposed` creates a conjugate-transposed non-owning multidimensional view.

Standard semantics reference: [cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg).

## Function Prototype

```cpp
namespace asc::std::linalg {
template<class ElementType, class Extents, class Layout, class Accessor> constexpr auto conjugate_transposed(mdspan<ElementType, Extents, Layout, Accessor> input);
} // namespace asc::std::linalg
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ElementType` | Element type accessed by the view; determines the types of reads, transformations, and return values. |
| `Extents` | Dimension, index mapping, layout, or access policy type used by the multidimensional view. |
| `Layout` | Dimension, index mapping, layout, or access policy type used by the multidimensional view. |
| `Accessor` | Dimension, index mapping, layout, or access policy type used by the multidimensional view. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `input` | Input | Provides a non-owning multidimensional data view; the underlying storage must remain valid while the view is in use. |

## Return Value

| Return type | Description |
| --- | --- |
| `auto` | Returns a conjugate-transposed non-owning multidimensional view. |

## Constraints

- Transposition applies only to rank-2 matrix views or mappings; the two dimensions and the corresponding strides are swapped, and no arbitrary-rank axis permutation is provided.

- For the delivered valid instances of the mdspan, accessor, scaling, and conjugation operations it depends on, the availability is Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the results while the object and the underlying storage are still valid.

```cpp
#include <asc/std/linalg>

bool example()
{
    int values[6] = {1, 2, 3, 4, 5, 6};
    using E = asc::std::extents<int, 2, 3>;
    asc::std::mdspan<int, E> view(values);
    const auto result = asc::std::linalg::conjugate_transposed(view);
    return result.extent(0) == 3 && result.extent(1) == 2 &&
        result.accessor().access(result.data_handle(), result.mapping()(2, 1)) == 6;
}
```

## Related APIs

- [API list for this header](asc_std_linalg.md)
