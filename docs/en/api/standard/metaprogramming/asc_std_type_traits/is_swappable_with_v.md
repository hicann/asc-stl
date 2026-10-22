# asc::std::is_swappable_with_v

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

`asc::std::is_swappable_with_v` determines at compile time whether swapping with another type is possible, providing the result as a bool variable template.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

The following declaration summary uses the `value` of the public trait class to express the equivalent constant value.

```cpp
namespace asc::std {
template<class T, class U>
inline constexpr bool is_swappable_with_v = is_swappable_with<T, U>::value;
} // namespace asc::std
```

## Constraints

- Provides the trait class and the _v helper form.

## Example

The following Host snippet instantiates the type trait on this page with concrete type arguments.

```cpp
#include <asc/std/type_traits>

static_assert((asc::std::is_swappable_with_v<int&, int&>) == true);
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
