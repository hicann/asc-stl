# asc::std::contiguous_iterator_tag

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

`asc::std::contiguous_iterator_tag` identifies the corresponding iterator capability or end-sentinel category.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

```cpp
namespace asc::std {
struct contiguous_iterator_tag : asc::std::random_access_iterator_tag {};
} // namespace asc::std
```

## Constraints

- Provides the C++20 public iterator concepts and traits interfaces.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/iterator>
#include <asc/std/type_traits>

bool example()
{
    static_assert(asc::std::is_base_of_v<asc::std::random_access_iterator_tag, asc::std::contiguous_iterator_tag>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
