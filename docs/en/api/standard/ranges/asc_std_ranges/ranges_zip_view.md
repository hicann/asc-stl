# asc::std::ranges::zip_view

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

`zip_view<FirstView, SecondView>` traverses exactly two underlying views in lockstep, representing the current element as a tuple of two element references; the length is the shorter of the two.

## Declaration

```cpp
namespace asc::std::ranges {
template<class FirstView, class SecondView>
class zip_view;
}
```

## Constraints

- Currently only exactly two random-access and sized ranges are supported; arbitrary view packs are not supported.
- The tuple obtained by dereferencing keeps the underlying references and allows writing back to writable elements; it does not copy or take ownership of the underlying elements.
- Const iteration requires both sides to be const-traversable, with each const iterator type identical to its non-const form.
- The actually borrowed underlying storage must cover all iteration accesses.

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
    asc::std::ranges::zip_view<Base, Base> view(base, base);
    auto item = *view.begin();
    return asc::std::get<0>(item) == 1 && asc::std::get<1>(item) == 1 && view.size() == 4;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
