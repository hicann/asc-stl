# asc::std::ranges::subrange

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

`asc::std::ranges::subrange` lazily observes, filters, combines, or transforms an input range; the underlying storage is still managed by the caller.

Standard semantics reference: [cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges).

## Declaration

The declaration summary keeps the public default arguments; the types and member operations must still satisfy the conditions below.

```cpp
namespace asc::std::ranges {
template<class Iter, class Sent = Iter,
    subrange_kind Kind = sized_sentinel_for<Sent, Iter>
        ? subrange_kind::sized : subrange_kind::unsized>
class subrange;
}
```

## Constraints

- Iter must satisfy input_or_output_iterator, and Sent must satisfy sentinel_for<Sent, Iter>.
- When Sent and Iter satisfy sized_sentinel_for, Kind must be sized; otherwise either the sized form storing the count or the unsized form can be selected.
- The default is Sent=Iter, and the default Kind is computed from sized_sentinel_for; C++17 and C++20 currently share this choice.
- subrange stores the iterator, the sentinel, and the necessary count, and does not take ownership of the underlying elements; its validity is limited by the actual element storage.

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
    return base.size() == 4 && *base.next(2).begin() == 3;
}
```

## Related APIs

- [API list for this header](asc_std_ranges.md)
