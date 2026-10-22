# asc::std::ranges::repeat_view

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

`repeat_view<T, Bound>` stores one value of T; each dereference of the iterator returns a const T& to that value, and the number of repetitions is determined by Bound. The default Bound is ptrdiff_t, and the default number of repetitions is 0.

## Declaration

The declaration summary keeps the public default arguments; the types and member operations must still satisfy the conditions below.

```cpp
namespace asc::std::ranges {
template<class T, class Bound = ptrdiff_t>
class repeat_view;
}
```

## Constraints

- T must be a cv-unqualified object type and movable-constructible; Bound must satisfy semiregular and be an integer type with a usable difference type, or unreachable_sentinel_t.
- The bounded repetition count must be non-negative; explicit value construction must provide the bound argument.
- views::repeat provides only the two-argument form taking the value and the bound; the single-argument unbounded factory is not provided.
- Each dereference borrows the same value stored inside the view; the view must cover the lifetime of the references and iterator uses.

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
    asc::std::ranges::repeat_view<int, int> view(7, 3);
    return *view.begin() == 7 && view.size() == 3;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
