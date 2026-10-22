# asc::strided_iterator

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

Header: `<asc/iterator>`.

`asc::strided_iterator` is a fixed-stride adaptor that borrows an underlying random access iterator. It supports the full set of random access operations for positive or negative non-zero strides, including bidirectional movement, subscripting, order comparison, iterator distance, and the standard iterator traits; a single movement corresponds to moving the underlying iterator by one stride.

## Declaration

```cpp
namespace asc {
template<class Iterator, class Stride = asc::std::ptrdiff_t> class strided_iterator;
} // namespace asc
```

## Constraints

- The stride must be non-zero.
- Iterators participating in distance or order comparison must use the same stride, and their underlying positions must be aligned by the stride.
- The iterator and its underlying range must remain valid during use.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/iterator>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    asc::strided_iterator<int*> iterator(values, 2);
    const bool first = *iterator == 1;
    ++iterator;
    return first && *iterator == 3;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
