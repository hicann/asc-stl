# asc::counting_iterator

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

`asc::counting_iterator` produces a lightweight iterator adaptor that increments according to a stepping rule.

## Declaration

```cpp
namespace asc {
template <class Start, class Difference = asc::std::ptrdiff_t>
class counting_iterator;
}  // namespace asc
```

## Constraints

- This adaptor provides only the lightweight operations described on this page and does not satisfy the complete set of traits and operations of the standard RandomAccessIterator; for example, zip supports only pre-increment and equality comparison, and must not be assumed usable for arbitrary standard algorithms requiring random access.

- Provides lazy, non-owning iterator adaptors and their factories.
- Operands must be valid at the current execution location.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/iterator>

bool example()
{
    asc::counting_iterator<int> iterator(3);
    const bool first = *iterator == 3;
    ++iterator;
    return first && *iterator == 4;
}
```

## Related APIs

- [API list for this header](asc_iterator.md)
