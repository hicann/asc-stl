# asc::std::move_iterator::iterator_concept

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

`asc::std::move_iterator::iterator_concept` identifies the concept category tag satisfied by the iterator.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

Member of: [`asc::std::move_iterator`](move_iterator.md).

```cpp
// Excerpt of the declaration inside move_iterator; the class template parameters and the remaining members are provided by the enclosing class.
using iterator_concept = conditional_t<random_access_iterator<Iter>, random_access_iterator_tag,
    conditional_t<bidirectional_iterator<Iter>, bidirectional_iterator_tag,
    conditional_t<forward_iterator<Iter>, forward_iterator_tag, input_iterator_tag>>>;
```

The above uses public types to express a type equivalent to the actual selection logic; contiguous iterators are mapped here to the random-access tag.

## Constraints

- The underlying iterator must support the operations on this page; decrement requires bidirectional traversal, and offsets and subscripts require the corresponding random-access operations.
- The adaptor does not own the underlying elements; dereference accesses the element through `asc::std::iter_move`, and moved-from values follow the conventions of the element type.
- Dereference, arrow, and subscript access must point to valid elements; the lifetime of returned references or pointers is bound by the underlying object.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    using selected = typename asc::std::move_iterator<int*>::iterator_concept;
    static_assert(asc::std::is_same_v<selected, asc::std::random_access_iterator_tag>);
    return true;
}
```

## Related APIs

- [`asc::std::move_iterator`](move_iterator.md)
- [API list for this header](asc_std_iterator.md)
