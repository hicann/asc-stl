# asc::std::tuple_size_v

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

Header: `<asc/std/tuple>`.

`asc::std::tuple_size_v` gives the number of tuple elements at compile time.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Declaration

```cpp
namespace asc::std {
template<class T> inline constexpr size_t tuple_size_v = tuple_size<T>::value;
}
```

## Constraints

- This is a compile-time type or size query; the type must satisfy the corresponding tuple-like traits, and the index must be within the element range.

## Example

The following Host example shows this interface with concrete inputs and a checkable result.

```cpp
#include <asc/std/tuple>

bool example()
{
    static_assert(asc::std::tuple_size_v<asc::std::tuple<int, char>> == 2);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_tuple.md)
