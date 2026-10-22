# asc::std::ranges::view_interface

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

`asc::std::ranges::view_interface` marks non-borrowable results of temporary ranges or provides view adaptor helper capability.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

```cpp
namespace asc::std::ranges {
template<class Derived> class view_interface;
} // namespace asc::std::ranges
```

## Constraints

- Element access and iteration of the view do not allocate additional storage; the lifetime of the underlying range must cover all uses of the borrowing views.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/tuple>

struct View : asc::std::ranges::view_interface<View> {
    int* first = nullptr;
    int* last = nullptr;
    int* begin() const { return first; }
    int* end() const { return last; }
};

bool example()
{
    int values[] = {2, 4, 6};
    View view;
    view.first = values;
    view.last = values + 3;
    return view.front() == 2 && view.back() == 6 && view.size() == 3;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
