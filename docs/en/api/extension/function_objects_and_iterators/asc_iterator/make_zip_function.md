# asc::make_zip_function

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

Constructs the adaptor, deducing and owning its state. Stores a callable and expands a standard-layer tuple, pair, array or zip proxy into its arguments.

`<asc/iterator>`

## Declaration

```cpp
namespace asc {
template <class F>
constexpr zip_function<asc::std::decay_t<F>> make_zip_function(F&& function);
}  // namespace asc
```

## Constraints

All four cv/ref overloads preserve callable and element value categories and return decltype(auto). Read adaptation additionally requires a copyable stable const callable.

Supports C++17 and C++20. Stored callables are copyable; borrowed objects remain alive. Compare positions only in the same logical sequence. constexpr and conditional noexcept follow actual operations; internal constraint parameters and conditional exception specifications are omitted below.

## Example

```cpp
#include <asc/iterator>

bool example()
{
    auto f = [](int a, int b) { return a + b; };
    auto it = asc::make_zip_function(f);
    return it(asc::std::tuple<int, int>{3, 7}) == 10;
}
```

## Related APIs

- [<asc/iterator>](asc_iterator.md)
