# asc::std::tuple_element

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

Headers: `<asc/std/array>`, `<asc/std/tuple>`, `<asc/std/utility>`, `<asc/std/complex>`, `<asc/std/ranges>`; the corresponding header must be included according to the target object type.

`asc::std::tuple_element<Index, T>` obtains, through the member type `type`, the element type at the specified index in a supported tuple-like type. The primary template is only a declaration; the valid indexes and cv handling of each partial specialization are as follows.

Standard semantics reference: [cppreference `array`](https://en.cppreference.com/w/cpp/header/array).

## Declaration

### Primary template

```cpp
namespace asc::std {
template<size_t Index, class T> struct tuple_element;
} // namespace asc::std
```

### Partial specializations for cv-qualified types

```cpp
namespace asc::std {
template<size_t Index, class T> struct tuple_element<Index, const T>;
template<size_t Index, class T> struct tuple_element<Index, volatile T>;
template<size_t Index, class T> struct tuple_element<Index, const volatile T>;
} // namespace asc::std
```

Usually the same cv-qualification is added to the element type of the unqualified type; when the element type is itself a reference, the qualification rules for C++ reference types apply. The `const integer_sequence` and `const subrange` below have their own dedicated partial specializations.

### Partial specialization for array

`<asc/std/array>` must be included; when `Index < Size`, `type` is `T`.

```cpp
namespace asc::std {
template<size_t Index, class T, size_t Size>
struct tuple_element<Index, array<T, Size>>;
} // namespace asc::std
```

### Partial specialization for tuple

`<asc/std/tuple>` must be included. A non-empty tuple selects the `Index`-th type item by item; the partial specialization for an empty tuple does not provide `type`.

```cpp
namespace asc::std {
template<size_t Index, class Head, class... Tail>
struct tuple_element<Index, tuple<Head, Tail...>>;
template<class Head, class... Tail>
struct tuple_element<0, tuple<Head, Tail...>>;
template<size_t Index> struct tuple_element<Index, tuple<>>;
} // namespace asc::std
```

### Partial specialization for pair

`<asc/std/utility>` must be included; at index 0, `type` is `T1`, and at index 1, `type` is `T2`.

```cpp
namespace asc::std {
template<class T1, class T2> struct tuple_element<0, pair<T1, T2>>;
template<class T1, class T2> struct tuple_element<1, pair<T1, T2>>;
} // namespace asc::std
```

### Partial specialization for integer_sequence

`<asc/std/utility>` must be included; when `Index < sizeof...(Values)`, `type` is `T` for both of the following forms. The `const` applies to the sequence object and does not make the result of this dedicated partial specialization `const T`.

```cpp
namespace asc::std {
template<size_t Index, class T, T... Values>
struct tuple_element<Index, integer_sequence<T, Values...>>;
template<size_t Index, class T, T... Values>
struct tuple_element<Index, const integer_sequence<T, Values...>>;
} // namespace asc::std
```

### Partial specialization for complex

`<asc/std/complex>` must be included; indexes 0 and 1 correspond to the real and imaginary parts respectively, and `type` is `T` for both. This trait does not widen the range of component types supported by the `complex` object itself.

```cpp
namespace asc::std {
template<size_t Index, class T> struct tuple_element<Index, complex<T>>;
} // namespace asc::std
```

### Partial specialization for subrange

`<asc/std/ranges>` must be included; at index 0, `type` is `Iter`, and at index 1, `type` is `Sent`. The dedicated partial specializations for `const subrange` also return these two types, without adding `const`.

```cpp
namespace asc::std {
template<class Iter, class Sent, ranges::subrange_kind Kind>
struct tuple_element<0, ranges::subrange<Iter, Sent, Kind>>;
template<class Iter, class Sent, ranges::subrange_kind Kind>
struct tuple_element<1, ranges::subrange<Iter, Sent, Kind>>;
template<class Iter, class Sent, ranges::subrange_kind Kind>
struct tuple_element<0, const ranges::subrange<Iter, Sent, Kind>>;
template<class Iter, class Sent, ranges::subrange_kind Kind>
struct tuple_element<1, const ranges::subrange<Iter, Sent, Kind>>;
} // namespace asc::std
```

## Constraints

- `T` must have a corresponding `tuple_element` partial specialization; the primary template itself does not provide `type`, and reference types are not automatically converted to their referenced types.
- `Index` starts from 0 and must be less than the number of elements of the corresponding type. An empty array, an empty tuple, and an empty `integer_sequence` have no valid element indexes.
- `type` describes the element type; it is not an element access and does not create or copy objects; to access object elements, use the corresponding `get` interface.
- cv-qualification is usually propagated to the element type; `const integer_sequence` and `const subrange` are handled by the dedicated partial specializations listed above.
- The common headers corresponding to each type should be included; the instantiation conditions of each object type itself must still be satisfied, for example ASC complex objects currently support only `complex<float>`.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/array>
#include <asc/std/type_traits>

bool example()
{
    using Array = asc::std::array<int, 3>;
    static_assert(asc::std::is_same_v<asc::std::tuple_element<1, Array>::type, int>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_array.md)
