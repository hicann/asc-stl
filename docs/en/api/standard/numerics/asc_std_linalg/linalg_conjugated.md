# asc::std::linalg::conjugated

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

`asc::std::linalg::conjugated` creates a non-owning multidimensional view that observes elements as their complex conjugates.

Standard semantics reference: [cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std::linalg {
template<class ElementType, class Extents, class Layout, class Accessor> constexpr auto conjugated(mdspan<ElementType, Extents, Layout, Accessor> input);
} // namespace asc::std::linalg
```

### Prototype 2

```cpp
namespace asc::std::linalg {
template<class ElementType, class Extents, class Layout, class NestedAccessor> constexpr auto conjugated(mdspan<ElementType, Extents, Layout, conjugated_accessor<NestedAccessor>> input);
} // namespace asc::std::linalg
```

## Parameters

### Parameters of Prototype 1

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

### Parameters of Prototype 2

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `ElementType` | Element type accessed by the view; determines the types of reads, transformations, and return values. |
| `Extents` | Dimension, index mapping, layout, or access policy type used by the multidimensional view. |
| `Layout` | Dimension, index mapping, layout, or access policy type used by the multidimensional view. |
| `NestedAccessor` | Underlying accessor type; provides the data handle, element access, and offset operations. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `input` | Input | Provides a non-owning multidimensional data view; the underlying storage must remain valid while the view is in use. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `auto` | Returns a non-owning multidimensional view that observes elements as their complex conjugates. |
| Prototype 2 | `auto` | Returns a non-owning multidimensional view that observes elements as their complex conjugates. |

## Constraints

- For the delivered valid instances of the mdspan, accessor, scaling, and conjugation operations it depends on, the availability is Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the results while the object and the underlying storage are still valid.

```cpp
#include <asc/std/linalg>
#include <asc/std/complex>

bool example()
{
    asc::std::complex<float> values[1] = {{2.0F, 3.0F}};
    using E = asc::std::extents<int, 1, 1>;
    asc::std::mdspan<asc::std::complex<float>, E> view(values);
    const auto result = asc::std::linalg::conjugated(view);
    const auto value = result.accessor().access(result.data_handle(), result.mapping()(0, 0));
    return value.real() == 2.0F && value.imag() == -3.0F && values[0].imag() == 3.0F;
}
```

## Related APIs

- [API list for this header](asc_std_linalg.md)
