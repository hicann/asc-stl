# asc::make_permutation_iterator

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

Constructs the adaptor, deducing and owning its state. Accesses random-access data through readable indices, retaining references, proxies and constness.

`<asc/iterator>`

## Declaration

```cpp
namespace asc {
template <class I, class J>
constexpr permutation_iterator<I, J> make_permutation_iterator(I data_first, J index_current);
}  // namespace asc
```

## Constraints

Indices must be nonnegative, representable and in range. Repeats support gather and ordered writes. Rearrangement requires independent targets; the caller prevents write races. Positions follow the index iterator.

Supports C++17 and C++20. Stored callables are copyable; borrowed objects remain alive. Compare positions only in the same logical sequence. constexpr and conditional noexcept follow actual operations; internal constraint parameters and conditional exception specifications are omitted below.

## Example

```cpp
#include <asc/iterator>

bool example()
{
    int data[3] = {10, 20, 30};
    int indices[2] = {2, 0};
    auto it = asc::make_permutation_iterator(data, indices);
    it[1] = 7;
    return *it == 30 && data[0] == 7;
}
```

## Related APIs

- [<asc/iterator>](asc_iterator.md)
