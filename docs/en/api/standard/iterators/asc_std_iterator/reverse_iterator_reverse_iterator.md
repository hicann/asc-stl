# asc::std::reverse_iterator::reverse_iterator

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

`asc::std::reverse_iterator::reverse_iterator` initializes a `reverse_iterator` object with the constructor forms listed on this page.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Function Prototype

Member of: [`asc::std::reverse_iterator`](reverse_iterator.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside reverse_iterator.
constexpr explicit reverse_iterator(Iter value) noexcept(is_nothrow_copy_constructible_v<Iter>);
```

### Prototype 2

```cpp
// Excerpt of the declaration inside reverse_iterator.
template<class It = Iter, enable_if_t<is_default_constructible_v<It>, int> = 0>
constexpr reverse_iterator() noexcept(is_nothrow_default_constructible_v<It>);
```

### Prototype 3

```cpp
// Excerpt of the declaration inside reverse_iterator.
template<class Other, enable_if_t<!is_same_v<Other, Iter> && is_convertible_v<const Other&, Iter>, int> = 0>
constexpr reverse_iterator(const reverse_iterator<Other>& other)
    noexcept(noexcept(Iter(declval<const Other&>())));
```

The exception condition of the converting constructor uses an equivalent public expression to indicate whether the underlying conversion throws.

## Parameters

| Parameter | Description |
| --- | --- |
| `It` | The selected type for default construction, defaulting to the enclosing class's `Iter`; it must be default constructible. |
| `Other` | The underlying iterator type of the conversion source adaptor; it must satisfy the conversion condition of the prototype. |

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The wrapped underlying iterator; the stored iterator must remain valid in subsequent operations. |
| `other` | Input | The conversion source adaptor; this object is constructed from its underlying iterator. |

## Return Value

No return value.

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
    int values[] = {2, 4};
    asc::std::reverse_iterator<int*> empty;
    asc::std::reverse_iterator<int*> direct(values + 2);
    asc::std::reverse_iterator<const int*> converted(direct);
    static_assert(!asc::std::is_convertible_v<int*, asc::std::reverse_iterator<int*>>);
    return empty.base() == nullptr && converted.base() == values + 2 && *converted == 4;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
