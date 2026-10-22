# asc::std::reverse_iterator::`operator-`>

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

`asc::std::reverse_iterator::operator->` returns a pointer that can be used to access members of the pointed-to object.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`asc::std::reverse_iterator`](reverse_iterator.md).

```cpp
// Excerpt of the declaration inside reverse_iterator; the class template parameters and the remaining members are provided by the enclosing class.
template<class It = Iter,
    enable_if_t<__reverse_iterator_detail::__has_const_arrow<It>, int> = 0>
constexpr pointer operator->() const;
```

The auxiliary test in the definition excerpt requires the underlying type to be a pointer or to provide an arrow operator callable on a const object; the returned address corresponds to the element before `base()`.

## Parameters

| Parameter | Description |
| --- | --- |
| `It` | The selected type of the underlying iterator, defaulting to `Iter`; it must be a pointer or support const arrow access. |

No function parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `pointer` | Returns a pointer through which members of the currently pointed-to object can be accessed. |

## Constraints

- The underlying iterator must support bidirectional traversal; random-access members additionally require the underlying iterator to support the corresponding offset or subscript operations.
- The reverse iterator accesses the element before `base()`; dereference or arrow access requires that previous position to be valid.
- The adaptor does not own the underlying range; the lifetime of returned references or pointers is bound by the underlying object.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6, 8};
    asc::std::reverse_iterator<int*> iterator(values + 4);
    auto pointer = iterator.operator->();
    return pointer == values + 3 && *pointer == 8;
}
```

## Related APIs

- [`asc::std::reverse_iterator`](reverse_iterator.md)
- [API list for this header](asc_std_iterator.md)
