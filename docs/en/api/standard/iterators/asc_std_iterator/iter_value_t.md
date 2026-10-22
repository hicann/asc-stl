# asc::std::iter_value_t

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

`asc::std::iter_value_t` computes the result type according to the range or iterator property designated by the name.

Standard semantics reference: [cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator).

## Declaration

The selection rule of `asc::std::iter_value_t<I>` is: first remove the cv/ref of I; an explicit iterator_traits specialization takes precedence; otherwise obtain value_type from indirectly_readable_traits. The following queries the result of the actual public alias; queried_type is an example name.

```cpp
template<class I>
using queried_type = asc::std::iter_value_t<I>;
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
    using selected = asc::std::iter_value_t<const int*>;
    static_assert(asc::std::is_same_v<selected, int>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_iterator.md)
