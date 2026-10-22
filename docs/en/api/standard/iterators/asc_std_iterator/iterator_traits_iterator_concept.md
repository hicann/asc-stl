# asc::std::iterator_traits::iterator_concept

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

`asc::std::iterator_traits::iterator_concept` identifies the concept category tag satisfied by the iterator.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

The plain five-member traits branch does not automatically provide `iterator_concept`; an explicit specialization may provide this member according to its own definition.

The following alias belongs only to the object pointer partial specialization of [`iterator_traits<T*>`](iterator_traits.md) and cannot be generalized to all iterators:

```cpp
// Excerpt from inside the object pointer partial specialization of iterator_traits<T*>.
using iterator_concept = contiguous_iterator_tag;
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
    using selected = typename asc::std::iterator_traits<const int*>::iterator_concept;
    static_assert(asc::std::is_same_v<selected, asc::std::contiguous_iterator_tag>);
    return true;
}
```

## Related APIs

- [`asc::std::iterator_traits`](iterator_traits.md)
- [API list for this header](asc_std_iterator.md)
