# asc::std::bool_constant

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

`asc::std::bool_constant` carries a compile-time Boolean constant as a type.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template <bool B>
using bool_constant = integral_constant<bool, B>;
}  // namespace asc::std
```

## Constraints

- The Boolean template argument `B` determines the result type; this alias equals `integral_constant<bool, B>`, whose `value` is `B`.

## Example

The following Host example checks the interface result against an independent expected type or value.

```cpp
#include <asc/std/type_traits>

static_assert(asc::std::bool_constant<true>::value);
static_assert(!asc::std::bool_constant<false>::value);
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
