# asc::zip_transform_iterator

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

`asc::zip_transform_iterator` combines multiple iterators and invokes the transform function on dereference.

## Declaration

```cpp
namespace asc {
template<class Function, class... Iterators> class zip_transform_iterator;
} // namespace asc
```

## Constraints

- Provides lazy, non-owning iterator adaptors and their factories.
- Operands must be valid at the current execution location.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/iterator>

int add_values(int left, int right) { return left + right; }

bool example()
{
    int left[2] = {1, 2};
    int right[2] = {3, 4};
    asc::zip_transform_iterator<int(*)(int, int), int*, int*> iterator(add_values, left, right);
    const bool first = *iterator == 4;
    ++iterator;
    return first && *iterator == 6;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
