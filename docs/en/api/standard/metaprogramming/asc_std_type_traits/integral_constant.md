# asc::std::integral_constant

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

`asc::std::integral_constant` carries a compile-time constant value as a type.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template <class T, T V>
struct integral_constant;
}  // namespace asc::std
```

## Constraints

- `T` and `V` must form a non-type template argument permitted by the current language mode; `value` is `V`, `value_type` is `T`, and `type` is the current specialization itself.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    using two = asc::std::integral_constant<int, 2>;
    // ::value carries the compile-time constant
    static_assert(two::value == 2);
    static_assert(asc::std::is_same_v<two::value_type, int>);
    static_assert(asc::std::is_same_v<two::type, two>);  // type is the specialization itself
    // bool_constant is exactly integral_constant<bool, B>
    static_assert(asc::std::bool_constant<true>::value);
    // Counterexample: false_type evaluates to false
    static_assert(!asc::std::false_type::value);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
