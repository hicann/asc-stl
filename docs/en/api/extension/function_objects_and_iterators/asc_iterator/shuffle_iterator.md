# asc::shuffle_iterator

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

Invokes the deterministic index mapping once per read, never for movement.

`<asc/iterator>`

## Declaration

```cpp
namespace asc {
template <class Index, class Bijection, class Difference = asc::std::ptrdiff_t>
class shuffle_iterator;
}  // namespace asc
```

## Constraints

The mapping is a bijection on a caller-defined finite domain and returns Index. Difference is separately signed. This is neither a Warp operation nor a random shuffle algorithm.

Supports C++17 and C++20. Stored callables are copyable; borrowed objects remain alive. Compare positions only in the same logical sequence. constexpr and conditional noexcept follow actual operations; internal constraint parameters and conditional exception specifications are omitted below.

## Example

```cpp
#include <asc/iterator>

bool example()
{
    auto mapping = [](asc::std::size_t n) { return asc::std::size_t{3} - n; };
    asc::shuffle_iterator<asc::std::size_t, decltype(mapping)> it(mapping);
    return *it == 3 && it[2] == 1;
}
```

## Related APIs

- [<asc/iterator>](asc_iterator.md)
