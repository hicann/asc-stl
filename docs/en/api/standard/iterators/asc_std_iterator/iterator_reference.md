# asc::std::iterator::reference

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

`asc::std::iterator::reference` identifies the writable element reference type.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

Member of: [`asc::std::iterator`](iterator.md).

```cpp
// Excerpt of the declaration inside asc::std::iterator; template parameters and other members are provided by the enclosing class.
using reference = Reference;
```

## Constraints

- Provides the C++20 public iterator concepts and traits interfaces.

## Example

The following Host snippet instantiates the interface on this page with concrete iterator or container types.

```cpp
#include <asc/std/iterator>

#include <asc/std/type_traits>

void example()
{
    using selected = typename asc::std::iterator<asc::std::random_access_iterator_tag, int>::reference;
    static_assert(asc::std::is_same_v<selected, int&>);
}
```

## Related APIs

- [`asc::std::iterator`](iterator.md)
- [API list for this header](asc_std_iterator.md)
