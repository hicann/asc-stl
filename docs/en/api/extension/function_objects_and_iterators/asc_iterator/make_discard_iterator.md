# asc::make_discard_iterator

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

Constructs the adaptor, deducing and owning its state. Discards assignment without reading, moving or converting the argument; its expression is still evaluated.

`<asc/iterator>`

## Declaration

```cpp
namespace asc {
constexpr discard_iterator make_discard_iterator(asc::std::ptrdiff_t position = 0) noexcept;
}  // namespace asc
```

## Constraints

The default position0 is valid and uses signed ptrdiff_t. Output and extra navigation operations do not provide readability.

Supports C++17 and C++20. Stored callables are copyable; borrowed objects remain alive. Compare positions only in the same logical sequence. constexpr and conditional noexcept follow actual operations; internal constraint parameters and conditional exception specifications are omitted below.

## Example

```cpp
#include <asc/iterator>

bool example()
{
    int evaluated = 0;
    auto it = asc::make_discard_iterator();
    *it++ = ++evaluated;
    return evaluated == 1 && it.index() == 1;
}
```

## Related APIs

- [<asc/iterator>](asc_iterator.md)
