# asc::std::ranges::iota_view

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

`iota_view<Value, Bound>` stores the start and bound by value, generating a sequence by incrementing the current count value; it does not borrow local scalars used to construct the start. The default bound is unreachable_sentinel_t, which does not automatically produce a finite length.

## Declaration

The declaration summary keeps the public default arguments; the types and member operations must still satisfy the conditions below.

```cpp
namespace asc::std::ranges {
template<class Value, class Bound = unreachable_sentinel_t>
class iota_view;
}
```

## Constraints

- Value must support the increment, comparison, and iteration operations used; an integer Value provides random-access counting.
- Bounded traversal must be able to reach the end condition safely and must not let the counting operation overflow.
- The default Bound is unreachable; complete traversal or size queries requiring a finite length cannot be performed on such an unbounded range.

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
    asc::std::ranges::iota_view<int, int> view(3, 6);
    return *view.begin() == 3 && view.size() == 3;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
