# asc::std::strided_slice

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

`asc::std::strided_slice` describes a regularly sampled interval along one source dimension for `submdspan`. Its members are `offset` (the first source index), `extent` (the length of the covered source interval), and `stride` (the sampling step).

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Declaration

```cpp
namespace asc::std {
template<class OffsetType, class ExtentType, class StrideType> struct strided_slice;
} // namespace asc::std
```

## Constraints

- The member types are signed/unsigned integer types or supported integral-constant-like types. The integer values and the resulting mapping must be representable by the source index type.
- Use `0 <= offset <= source.extent(d)`, `0 <= extent <= source.extent(d) - offset`, and a positive `stride`. The selected source indices are `offset + j * stride` for `0 <= j < count`.
- `extent` is the covered source interval length, not the number of selected elements. The result dimension is `count = extent == 0 ? 0 : 1 + (extent - 1) / stride`. For example, `{1, 5, 2}` selects indices 1, 3, and 5, giving three elements; `{6, 0, 2}` gives an empty slice of a dimension of length 6.
- The slice keeps its dimension. Together with the source mapping it determines the result strides; a nonempty step greater than one may produce a noncontiguous subview. The view does not copy or own elements.
- Host, AI Core SIMD programming, and AI Core SIMT programming are compatible with the plain pointer domain.

## Example

The following Host example samples every second element and checks the resulting dimension and values.

```cpp
#include <asc/std/mdspan>

bool example()
{
    int values[6] = {10, 11, 12, 13, 14, 15};
    asc::std::mdspan<int, asc::std::extents<int, 6>> source(values);
    auto sampled = asc::std::submdspan(source, asc::std::strided_slice<int, int, int>{1, 5, 2});
    auto empty = asc::std::submdspan(source, asc::std::strided_slice<int, int, int>{6, 0, 2});
    return sampled.extent(0) == 3 && sampled(0) == 11 && sampled(1) == 13 &&
        sampled(2) == 15 && sampled.stride(0) == 2 && empty.empty();
}
```

## Related APIs

- [submdspan](submdspan.md): construct a borrowing subview.
- [submdspan_mapping](submdspan_mapping.md): combine slices with the source layout.
- [Padded crop and transpose example](../../../../../../examples/standard/mdspan_matrix/README_en.md).
