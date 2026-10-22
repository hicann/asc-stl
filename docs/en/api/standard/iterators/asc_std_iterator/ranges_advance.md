# asc::std::ranges::advance

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

Header: `<asc/std/iterator>`.

`asc::std::ranges::advance` updates the iterator by the specified distance or end sentinel; when both a distance and a bound are given, it stops when the distance is completed or the bound is reached, and returns the uncompleted distance.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

`asc::std::ranges::advance` is a callable object. The object and its call operator are provided by the header; its type can be queried through the public name.

```cpp
namespace asc::std::ranges {
using advance_object_type = decltype(::asc::std::ranges::advance);
}
```

## Constraints

- The interface can be used in C++17 and C++20; calls on the device side must still satisfy the call position requirements of the iterators and element operations used.
- `advance(i, n)` updates `i` by the signed distance; `advance(i, bound)` advances to the sentinel.
- `advance(i, n, bound)` stops when the distance is completed or the bound is reached, and returns the uncompleted distance.
- A non-negative move requires the range from the current position to the bound to be valid; a negative move requires a bidirectional iterator, and a negative move with a bound additionally requires the bound and the iterator to be of the same type.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6, 8};
    int* iterator = values;
    asc::std::ranges::advance(iterator, 2);
    auto remaining = asc::std::ranges::advance(iterator, 3, values + 4);
    return iterator == values + 4 && remaining == 1;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
