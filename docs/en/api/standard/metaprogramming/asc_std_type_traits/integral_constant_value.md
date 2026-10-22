# asc::std::integral_constant::value

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

`asc::std::integral_constant::value` provides at compile time the value or alignment requirement of the corresponding type trait.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
// Declaration inside the integral_constant<T, V> class.
static constexpr T value = V;
```

## Constraints

- `value` is a static `constexpr` member of type `const T` whose value equals the template argument `V` of the current specialization.

## Example

The following Host snippet instantiates the type trait on this page with concrete type arguments.

```cpp
#include <asc/std/type_traits>

static_assert((asc::std::integral_constant<int, 3>::value) == 3);
```

## Related APIs

- [`asc::std::integral_constant`](integral_constant.md)
- [API list for this header](asc_std_type_traits.md)
