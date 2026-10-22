# asc::std::integral_constant::type

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

`asc::std::integral_constant::type` is a type alias for the current `integral_constant<T, V>` specialization itself.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

Member of: [`asc::std::integral_constant`](integral_constant.md).

```cpp
// Excerpt of the declaration inside asc::std::integral_constant; template parameters and other members are provided by the owning class.
using type = integral_constant<T, V>;
```

## Constraints

- `type` equals the current `integral_constant<T, V>` specialization; querying this alias constructs no object.

## Example

The following Host example checks the interface result against an independent expected type or value.

```cpp
#include <asc/std/type_traits>

using seven = typename asc::std::integral_constant<int, 7>::type;
static_assert(seven::value == 7);
static_assert(seven{}() == 7);
```

## Related APIs

- [`asc::std::integral_constant`](integral_constant.md)
- [API list for this header](asc_std_type_traits.md)
