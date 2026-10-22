# asc::std::ranges::view_base

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

`asc::std::ranges::view_base` marks non-borrowable results of temporary ranges or provides view adaptor helper capability.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

```cpp
namespace asc::std::ranges {
struct view_base;
} // namespace asc::std::ranges
```

## Constraints

- Element access and iteration of the view do not allocate additional storage; the lifetime of the underlying range must cover all uses of the borrowing views.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/ranges>

struct View : asc::std::ranges::view_base {
    int* first = nullptr;
    int* last = nullptr;
    int* begin() const { return first; }
    int* end() const { return last; }
};

bool example()
{
    static_assert(asc::std::ranges::enable_view<View>);
    int values[] = {2, 4};
    View view;
    view.first = values;
    view.last = values + 2;
    return *view.begin() == 2;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
