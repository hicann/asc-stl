# asc::std::make_signed

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

Header: `<asc/std/type_traits>`.

`asc::std::make_signed` yields the type that preserves the width rules and adjusts integer signedness.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<class T> struct make_signed;
} // namespace asc::std
```

## Constraints

- `T` must be an integral or enumeration type other than `bool`, and a signed result type of the corresponding width must exist; floating-point, pointer, or `void` types must not be used.
- The conversion keeps the `const` and `volatile` qualification of the input type; it changes the type and does not perform a value conversion.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // Positive example: the corresponding signed type of unsigned int is int, and the top-level const is preserved
    static_assert(asc::std::is_same_v<asc::std::make_signed_t<unsigned int>, int>);
    static_assert(asc::std::is_same_v<typename asc::std::make_signed<const unsigned long>::type, const long>);
    // Counterexample: make_signed_t<unsigned int> is not unsigned int itself
    static_assert(!asc::std::is_same_v<asc::std::make_signed_t<unsigned int>, unsigned int>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
