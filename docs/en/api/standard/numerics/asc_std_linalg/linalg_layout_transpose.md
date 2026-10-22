# asc::std::linalg::layout_transpose

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

`asc::std::linalg::layout_transpose` maps multidimensional indices to underlying storage offsets according to the specified layout.

Standard semantics reference: [cppreference `linalg`](https://en.cppreference.com/w/cpp/header/linalg).

## Declaration

```cpp
namespace asc::std::linalg {
template<class Layout> class layout_transpose;
} // namespace asc::std::linalg
```

## Constraints

- Transposition applies only to rank-2 matrix views or mappings; the two dimensions and the corresponding strides are swapped, and no arbitrary-rank axis permutation is provided.

- For the delivered valid instances of the mdspan, accessor, scaling, and conjugation operations it depends on, the availability is Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/linalg>
#include <asc/std/complex>
#include <asc/std/type_traits>

bool example()
{
    using Layout = asc::std::linalg::layout_transpose<asc::std::layout_right>;
    using Extents = asc::std::extents<int, 3, 2>;
    using NestedExtents = asc::std::extents<int, 2, 3>;
    asc::std::layout_right::mapping<NestedExtents> original;
    Layout::mapping<Extents> transposed(original);
    static_assert(asc::std::is_same_v<Layout::nested_layout_type, asc::std::layout_right>);
    return transposed(2, 1) == original(1, 2);
}
```

## Related APIs

- [API list for this header](asc_std_linalg.md)
