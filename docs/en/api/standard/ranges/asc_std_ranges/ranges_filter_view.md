# asc::std::ranges::filter_view

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

Header: `<asc/std/ranges>`.

`asc::std::ranges::filter_view` lazily observes, filters, combines, or transforms the input range; the underlying storage is still managed by the caller.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

```cpp
namespace asc::std::ranges {
template<class View, class Pred> class filter_view;
} // namespace asc::std::ranges
```

## Constraints

- Element access and iteration on the view do not allocate additional storage; the underlying range's lifetime must cover all uses of borrowed views.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/tuple>

bool example()
{
    int values[] = {1, 2, 3, 4};
    using Base = asc::std::ranges::subrange<int*>;
    Base base(values, values + 4);
    auto predicate = [](int value) { return value % 2 == 0; };
    asc::std::ranges::filter_view<Base, decltype(predicate)> view(base, predicate);
    auto iterator = view.begin();
    if (*iterator != 2) return false;
    return *++iterator == 4;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
