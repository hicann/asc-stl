# asc::make_strided_iterator

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

Constructs the adaptor, deducing and owning its state. Stores a physical anchor, extent, signed stride and logical position. Positive strides start at the first element; negative strides start at the last.

`<asc/iterator>`

## Declaration

```cpp
namespace asc {
template <class I>
constexpr strided_iterator<I> make_strided_iterator(
    I first, asc::std::iter_difference_t<I> extent, asc::std::iter_difference_t<I> stride = 1);
}  // namespace asc
```

## Constraints

The base is readable and random access. Extent is nonnegative and stride nonzero. Extent5 with strides2/-2 selects0,2,4 /4,2,0. count() is3. Ends never form invalid physical pointers; base() always returns the anchor.

Supports C++17 and C++20. Stored callables are copyable; borrowed objects remain alive. Compare positions only in the same logical sequence. constexpr and conditional noexcept follow actual operations; internal constraint parameters and conditional exception specifications are omitted below.

## Example

```cpp
#include <asc/iterator>

bool example()
{
    int data[5] = {1, 2, 3, 4, 5};
    auto it = asc::make_strided_iterator(data, 5, -2);
    return it.count() == 3 && it[1] == 3 && (it + 3).base() == data;
}
```

## Related APIs

- [<asc/iterator>](asc_iterator.md)
