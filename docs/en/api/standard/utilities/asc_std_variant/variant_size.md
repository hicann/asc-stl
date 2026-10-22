# asc::std::variant_size

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

Header: `<asc/std/variant>`.

`asc::std::variant_size` obtains the number of alternatives of a variant.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Declaration

```cpp
namespace asc::std {
template<class T> struct variant_size;

template<class... Types>
struct variant_size<variant<Types...>> : integral_constant<size_t, sizeof...(Types)> {};

template<class T> struct variant_size<const T> : variant_size<T> {};
template<class T> struct variant_size<volatile T> : variant_size<T> {};
template<class T> struct variant_size<const volatile T> : variant_size<T> {};
}
```

## Constraints

- The primary template operates on a variant type; the const, volatile, and const volatile forms are partial specializations of this primary template, not another variadic primary template.

- Alternative types on the device side and the selected construction, assignment, and swap operations must not throw.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/variant>

bool example()
{
    static_assert(asc::std::variant_size<asc::std::variant<int, float>>::value == 2);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_variant.md)
