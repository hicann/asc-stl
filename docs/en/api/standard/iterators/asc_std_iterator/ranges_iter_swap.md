# asc::std::ranges::iter_swap

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

`asc::std::ranges::iter_swap` is a customization point object that swaps the elements pointed to by two iterators: it calls a discoverable `iter_swap` first, then swaps the dereferenceable results, and finally falls back to element-by-element `swap`.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

`asc::std::ranges::iter_swap` is a callable object. The object and its call operator are provided by the header; its type can be queried through the public name.

```cpp
namespace asc::std::ranges {
using iter_swap_object_type = decltype(::asc::std::ranges::iter_swap);
}
```

## Constraints

- The interface can be used in C++17 and C++20; calls on the device side must still satisfy the call position requirements of the iterators and element operations used.
- `iter_swap(i, j)` swaps the elements pointed to by the two iterators; the applicable custom swap, swap after dereference, and move swap paths are supported.
- The two iterators must be dereferenceable, and the corresponding elements must satisfy the requirements of the actually selected swap path.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4};
    asc::std::ranges::iter_swap(values, values + 1);
    return values[0] == 4 && values[1] == 2;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
