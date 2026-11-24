# asc::make_zip_transform_iterator

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

Constructs the adaptor, deducing and owning its state. The alias transform_iterator<zip_function<F>,zip_iterator<I...>> reads components and expands them into the callable.

`<asc/iterator>`

## Declaration

```cpp
namespace asc {
template <class F, class... I>
constexpr zip_transform_iterator<asc::std::decay_t<F>, I...> make_zip_transform_iterator(F&& function, I... current);
}  // namespace asc
```

## Constraints

All components are readable. Position, end, movement and result rules are shared with the component adaptors. References cannot escape temporary value components.

Supports C++17 and C++20. Stored callables are copyable; borrowed objects remain alive. Compare positions only in the same logical sequence. constexpr and conditional noexcept follow actual operations; internal constraint parameters and conditional exception specifications are omitted below.

## Example

```cpp
#include <asc/iterator>

bool example()
{
    int a[2] = {1, 2}, b[2] = {10, 20};
    auto f = [](int x, int y) { return x + y; };
    auto it = asc::make_zip_transform_iterator(f, a, b);
    return *it == 11 && it[1] == 22;
}
```

## Related APIs

- [<asc/iterator>](asc_iterator.md)
