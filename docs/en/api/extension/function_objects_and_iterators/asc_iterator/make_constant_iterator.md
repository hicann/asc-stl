# asc::make_constant_iterator

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

Constructs the adaptor, deducing and owning its state. Owns a copyable constant and returns T by value without exposing an internal reference.

`<asc/iterator>`

## Declaration

```cpp
namespace asc {
template <class D = asc::std::ptrdiff_t, class T>
constexpr constant_iterator<asc::std::decay_t<T>, D> make_constant_iterator(T&& value, D position = 0);
}  // namespace asc
```

## Constraints

T is a complete unqualified non-array object. Difference is signed. The legacy category is input; the C++20 concept can be random access.

Supports C++17 and C++20. Stored callables are copyable; borrowed objects remain alive. Compare positions only in the same logical sequence. constexpr and conditional noexcept follow actual operations; internal constraint parameters and conditional exception specifications are omitted below.

## Example

```cpp
#include <asc/iterator>

bool example()
{
    auto it = asc::make_constant_iterator(7);
    it += 2;
    return it[1] == 7 && it.index() == 2;
}
```

## Related APIs

- [<asc/iterator>](asc_iterator.md)
