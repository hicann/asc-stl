# asc::is_associative_v

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

Header: `<asc/functional>`.

`asc::is_associative_v` indicates whether the given operator is associative on the given type.

## Declaration

```cpp
namespace asc {
template <class Operator, class T>
inline constexpr bool is_associative_v =
    detail::metadata_domain<Operator, T>::valid && detail::metadata_unsigned<T>::value &&
    detail::is_associative_op<typename detail::metadata_domain<Operator, T>::tag>::value &&
    (!detail::metadata_same<typename detail::metadata_domain<Operator, T>::tag, detail::multiply_op>::value ||
        detail::metadata_same<T, unsigned int>::value || detail::metadata_same<T, unsigned long>::value ||
        detail::metadata_same<T, unsigned long long>::value);
}  // namespace asc
```

## Constraints

- The declaration shows the primary template; there are separate specializations that are true for Boolean-logic combinations over bool and for minimum<T>/maximum<T> over value domains satisfying a total order.

- Standard operators register only matching `Operator<T>`/`T` combinations or the transparent `Operator<void>`; unmatched value types return false.
- For integer addition the identity element is 0; for multiplication the identity element is 1 and the absorbing element is 0. Logical operations register only bool; bitwise operations register only unsigned integers.
- Arithmetic associativity is registered for unsigned types; multiplication is further limited to unsigned int, unsigned long, and unsigned long long to avoid signed overflow after narrow-integer promotion. Floating-point addition/multiplication is not registered.
- The existing registrations for minimum/maximum require the caller to use a value domain satisfying a total order; NaN and non-total-order custom comparisons must not be assumed safe for regrouping on this basis.

## Example

The following snippet reads the interface value with concrete template arguments.

```cpp
#include <asc/functional>

inline constexpr auto example = asc::is_associative_v<asc::minimum<int>, int>;
static_assert(example, "the selected documented type has this capability");
```

## Related APIs

- [API list for this header](asc_functional.md)
