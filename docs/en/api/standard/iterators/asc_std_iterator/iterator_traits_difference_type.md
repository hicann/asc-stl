# asc::std::iterator_traits::difference_type

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

`asc::std::iterator_traits::difference_type` identifies the signed type of the iterator distance.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

The legacy five-member traits branch obtains the type from `Iter::difference_type`; if the selected traits branch does not provide it, this member does not exist.

The following alias belongs only to the object pointer partial specialization of [`iterator_traits<T*>`](iterator_traits.md) and cannot be generalized to all iterators:

```cpp
// Excerpt from inside the object pointer partial specialization of iterator_traits<T*>.
using difference_type = ptrdiff_t;
```

## Constraints

- Whether a member exists and its type are determined by the selected traits branch; custom iterators should provide matching associated types.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    struct custom_iterator {
        using difference_type = short;
        using value_type = long;
        using pointer = long*;
        using reference = long&;
        using iterator_category = asc::std::input_iterator_tag;
    };
    using selected = typename asc::std::iterator_traits<custom_iterator>::difference_type;
    static_assert(asc::std::is_same_v<selected, short>);
    return true;
}
```

## Related APIs

- [`asc::std::iterator_traits`](iterator_traits.md)
- [API list for this header](asc_std_iterator.md)
