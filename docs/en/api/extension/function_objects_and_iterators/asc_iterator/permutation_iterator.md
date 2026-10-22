# asc::permutation_iterator

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

`asc::permutation_iterator` uses an index iterator to permute access to the elements of a data iterator.

## Declaration

```cpp
namespace asc {
template<class Iterator, class IndexIterator = Iterator> class permutation_iterator;
} // namespace asc
```

## Constraints

- Provides lazy, non-owning iterator adaptors and their factories.
- Operands must be valid at the current execution location.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/iterator>

bool example()
{
    int values[3] = {10, 20, 30};
    int indices[2] = {2, 0};
    asc::permutation_iterator<int*, int*> iterator(values, indices);
    const bool first = *iterator == 30;
    ++iterator;
    return first && *iterator == 10;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
