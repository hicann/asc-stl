# asc::std::iter_move

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

`asc::std::iter_move` obtains a movable reference or value according to the iterator customization rules.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

`asc::std::iter_move` is an initialized constant callable object, called as `asc::std::iter_move(iterator)`. The implementation class is not a public type; the object_type below is only an example alias for querying it.

```cpp
using object_type = decltype(asc::std::iter_move);
```

A customized iter_move found via ADL is called first; otherwise, when the dereference result is an lvalue, its rvalue reference is obtained, and in the other cases the corresponding dereference result is returned.

## Constraints

- The iterator must be dereferenceable, and the customized or fallback expression must be valid; the customization may return a movable result type different from the plain dereference.
- When a reference is returned, it still borrows the original element storage; this operation does not extend the storage's lifetime and does not by itself guarantee that a subsequent move construction has occurred.

## Example

The following Host example checks the result of the call while the underlying object is alive.

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    int values[2] = {2, 4};
    int&& reference = asc::std::iter_move(values);
    static_assert(asc::std::is_same_v<decltype(reference), int&&>);
    reference = 7;
    return &reference == values && values[0] == 7 && values[1] == 4;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
