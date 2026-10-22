# asc::std::tuple_element::type

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

Header: `<asc/std/tuple>`, `<asc/std/utility>`.

`tuple_element<Index, T>::type` identifies the element type at the specified index in a supported tuple-like object.

Standard semantics reference: [cppreference `tuple`](https://en.cppreference.com/w/cpp/header/tuple).

## Declaration

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::std::tuple_element; template parameters and other members are provided by the owning class.
using type = T;
```

This prototype corresponds to the headers: `<asc/std/tuple>`, `<asc/std/utility>`.

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::std::tuple_element; template parameters and other members are provided by the owning class.
using type = const tuple_element_t<Index, T>;
```

This prototype corresponds to the headers: `<asc/std/tuple>`, `<asc/std/utility>`.

### Prototype 3

```cpp
// Excerpt of the declaration inside class asc::std::tuple_element; template parameters and other members are provided by the owning class.
using type = const volatile tuple_element_t<Index, T>;
```

This prototype corresponds to the headers: `<asc/std/tuple>`, `<asc/std/utility>`.

### Prototype 4

```cpp
// Excerpt of the declaration inside class asc::std::tuple_element; template parameters and other members are provided by the owning class.
using type = volatile tuple_element_t<Index, T>;
```

This prototype corresponds to the headers: `<asc/std/tuple>`, `<asc/std/utility>`.

## Constraints

- This is a compile-time type or size query; the type must satisfy the corresponding tuple-like traits, and the index must be within the element range.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/tuple>
#include <asc/std/type_traits>

bool example()
{
    using Tuple = asc::std::tuple<int, float>;
    static_assert(asc::std::is_same_v<asc::std::tuple_element<1, Tuple>::type, float>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_tuple.md)
