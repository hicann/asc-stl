# asc::std::tuple_size

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

`asc::std::tuple_size<T>` obtains at compile time the number of elements of a supported tuple-like type, providing the result through the static member `value`. The primary template is only a declaration; concrete types are supported through partial specializations.

Standard semantics reference: [cppreference `array`](https://en.cppreference.com/w/cpp/header/array).

## Declaration

### Primary template

```cpp
namespace asc::std {
template<class T> struct tuple_size;
} // namespace asc::std
```

### Partial specializations for cv-qualified types

The following is a declaration summary in the publicly matched form. The actual implementation provides the corresponding result only when the unqualified `tuple_size<T>` is complete and has `value`; internal conditional dispatch names are omitted.

```cpp
namespace asc::std {
template<class T> struct tuple_size<const T>;
template<class T> struct tuple_size<volatile T>;
template<class T> struct tuple_size<const volatile T>;
} // namespace asc::std
```

These partial specializations keep the number of elements of the cv-unqualified type and do not remove reference qualification.

### Partial specialization for array

`<asc/std/array>` must be included; `value` equals `Size`.

```cpp
namespace asc::std {
template<class T, size_t Size> struct tuple_size<array<T, Size>>;
} // namespace asc::std
```

### Partial specialization for tuple

`<asc/std/tuple>` must be included; `value` equals `sizeof...(Types)`.

```cpp
namespace asc::std {
template<class... Types> struct tuple_size<tuple<Types...>>;
} // namespace asc::std
```

### Partial specialization for pair

`<asc/std/utility>` must be included; `value` equals 2.

```cpp
namespace asc::std {
template<class T1, class T2> struct tuple_size<pair<T1, T2>>;
} // namespace asc::std
```

### Partial specialization for integer_sequence

`<asc/std/utility>` must be included; `value` equals `sizeof...(Values)`.

```cpp
namespace asc::std {
template<class T, T... Values> struct tuple_size<integer_sequence<T, Values...>>;
} // namespace asc::std
```

### Partial specialization for complex

`<asc/std/complex>` must be included; `value` equals 2. This trait does not widen the range of component types supported by the `complex` object itself.

```cpp
namespace asc::std {
template<class T> struct tuple_size<complex<T>>;
} // namespace asc::std
```

### Partial specialization for subrange

`<asc/std/ranges>` must be included; `value` equals 2, corresponding to the start iterator and the end sentinel respectively.

```cpp
namespace asc::std {
template<class Iter, class Sent, ranges::subrange_kind Kind>
struct tuple_size<ranges::subrange<Iter, Sent, Kind>>;
} // namespace asc::std
```

## Constraints

- `T` must be a type with a corresponding `tuple_size` partial specialization; the primary template itself does not provide `value`.
- `array<T, 0>`, an empty `tuple<>`, and an empty `integer_sequence` have 0 elements; they have no accessible element 0.
- cv-qualified types use the count of the corresponding unqualified type; reference types are not automatically converted to their referenced types.
- The common headers corresponding to each object type should be included; do not assume that `<asc/std/array>` provides all other object types merely because this page is in the array directory.
- This trait only provides the number of elements at compile time and performs no object construction, element access, memory allocation, or comparison.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/array>

bool example()
{
    static_assert(asc::std::tuple_size<asc::std::array<int, 3>>::value == 3);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_array.md)
