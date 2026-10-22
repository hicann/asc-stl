# asc::has_absorbing_element_v

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

`asc::has_absorbing_element_v` indicates whether an absorbing element is registered for the given operator and value type.

## Declaration

```cpp
namespace asc {
template <class Operator, class T>
inline constexpr bool has_absorbing_element_v = detail::metadata_elements<Operator, T>::has_absorbing;
}  // namespace asc
```

## Constraints

- Standard operators register only matching `Operator<T>`/`T` combinations or the transparent `Operator<void>`; unmatched value types return false.
- For integer addition the identity element is 0; for multiplication the identity element is 1 and the absorbing element is 0. Logical operations register only bool; bitwise operations register only unsigned integers.
- Arithmetic associativity is registered for unsigned types; multiplication is further limited to unsigned int, unsigned long, and unsigned long long to avoid signed overflow after narrow-integer promotion. Floating-point addition/multiplication is not registered.
- The existing registrations for minimum/maximum require the caller to use a value domain satisfying a total order; NaN and non-total-order custom comparisons must not be assumed safe for regrouping on this basis.

## Example

The following snippet checks a registered combination and an unregistered combination respectively.

```cpp
#include <asc/functional>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

void example()
{
    static_assert(asc::has_absorbing_element_v<asc::std::multiplies<int>, int>);
    static_assert(!asc::has_absorbing_element_v<asc::std::plus<float>, float>);
}
```

## Related APIs

- [API list for this header](asc_functional.md)
