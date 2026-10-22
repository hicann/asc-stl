# asc::std::mdspan

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

Header: `<asc/std/mdspan>`.

`asc::std::mdspan` associates a multidimensional data handle, extents, a layout, and an accessor in a non-owning way.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Declaration

```cpp
namespace asc::std {
template<class Element, class Extents, class Layout = layout_right,
    class Accessor = default_accessor<Element>>
class mdspan;
}
```

## Constraints

- `Element` must be a non-array, non-abstract type and must agree with `Accessor::element_type`; `Extents` must be an `extents` specialization.
- `Layout` must provide a `mapping` type for the selected dimensions; the accessor determines the data handle, reference, and access rules.
- Starting from C++17, the one-dimensional `operator[]` and the access forms that keep indices in an `array`/`span` are provided; the multi-argument `operator[]` is available only when the language mode is higher than C++20 and `__cpp_multidimensional_subscript >= 202110L`.
- In C++17 and C++20, the `operator()` extension can be used to access elements with per-dimension subscripts; in that form the number of subscripts must equal the number of dimensions.
- The view does not take ownership of the storage. During access, the storage must be valid and cover the range required by the layout mapping and the accessor; a layout with gaps may require more storage than the number of logical elements.
- Host, AI Core SIMD programming, and AI Core SIMT programming support plain pointers; the validity of other address spaces and handles is defined by the accessor.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/mdspan>

bool example()
{
    int values[6] = {1, 2, 3, 4, 5, 6};
    asc::std::mdspan<int, asc::std::extents<int, 2, 3>> view(values);
    view(1, 2) = 9;
    return view.extent(0) == 2 && view.extent(1) == 3 && values[5] == 9;
}
```

## Related APIs

- [API list for this header](asc_std_mdspan.md)
