# asc::std::true_type

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

`asc::std::true_type` represents the compile-time true value type.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
using true_type = integral_constant<bool, true>;
}  // namespace asc::std
```

## Constraints

- This name is a type alias of `integral_constant<bool, true>`; the members of the constant wrapper are accessible through that type, and `value` is `true`.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/type_traits>

bool example()
{
    static_assert(asc::std::true_type::value);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
