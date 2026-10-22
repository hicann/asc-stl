# asc::std::tuple_element_t

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

`asc::std::tuple_element_t` obtains the type of the element or alternative at the given index.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Declaration

```cpp
namespace asc::std {
template<size_t Index, class T> using tuple_element_t = typename tuple_element<Index, T>::type;
} // namespace asc::std
```

## Constraints

- This is a compile-time type or size query; the type must satisfy the corresponding tuple-like traits, and the index must be within the element range.

## Example

The following Host example uses concrete types and an independent expectation to check an alias or marker result.

```cpp
#include <asc/std/tuple>
#include <asc/std/type_traits>

void use_type()
{
    using selected = asc::std::tuple_element_t<0, asc::std::tuple<int, float>>;
    static_assert(asc::std::is_same_v<selected, int>);
}
```

## Related APIs

- [API list for this header](asc_std_tuple.md)
