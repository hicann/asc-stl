# asc::std::iterator

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

`asc::std::iterator` provides the category and value types needed by the legacy iterator type definitions.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

```cpp
namespace asc::std {
template<class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&> struct iterator;
} // namespace asc::std
```

## Constraints

- Provides the C++20 public iterator concepts and traits interfaces.

## Example

The following Host example checks the result of the call while the object is valid.

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    using legacy = asc::std::iterator<asc::std::input_iterator_tag, int>;
    static_assert(asc::std::is_same_v<legacy::difference_type, asc::std::ptrdiff_t>);
    static_assert(asc::std::is_same_v<legacy::pointer, int*>);
    static_assert(asc::std::is_same_v<legacy::reference, int&>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
