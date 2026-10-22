# asc::std::reverse_iterator::iterator_category

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

`asc::std::reverse_iterator::iterator_category` identifies the legacy category tag of the iterator.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

Member of: [`asc::std::reverse_iterator`](reverse_iterator.md).

```cpp
// Excerpt of the declaration inside reverse_iterator; the class template parameters and the remaining members are provided by the enclosing class.
using iterator_category = conditional_t<
    __reverse_iterator_detail::__has_random_access_traversal<Iter>,
    random_access_iterator_tag,
    __reverse_iterator_detail::__iterator_traits_category_or_concept_t<Iter>>;
```

This is an excerpt of the definition, with the auxiliary types provided by the header: when the underlying effective traversal tag reaches random access, it is mapped to the random-access tag; otherwise the underlying category or concept tag is carried over.

## Constraints

- The underlying iterator must support bidirectional traversal; random-access members additionally require the underlying iterator to support the corresponding offset or subscript operations.
- The reverse iterator accesses the element before `base()`; dereference or arrow access requires that previous position to be valid.
- The adaptor does not own the underlying range; the lifetime of returned references or pointers is bound by the underlying object.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    using selected = typename asc::std::reverse_iterator<int*>::iterator_category;
    static_assert(asc::std::is_same_v<selected, asc::std::random_access_iterator_tag>);
    return true;
}
```

## Related APIs

- [`asc::std::reverse_iterator`](reverse_iterator.md)
- [API list for this header](asc_std_iterator.md)
