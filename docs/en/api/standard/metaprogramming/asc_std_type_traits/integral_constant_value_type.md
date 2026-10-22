# asc::std::integral_constant::value_type

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

`asc::std::integral_constant::value_type` equals the template parameter `T` and denotes the type of the compile-time constant held by this specialization.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

Member of: [`asc::std::integral_constant`](integral_constant.md).

```cpp
// Excerpt of the declaration inside asc::std::integral_constant; template parameters and other members are provided by the owning class.
using value_type = T;
```

## Constraints

- `value_type` equals the template parameter `T` of the current specialization and can be used to interpret `value` and the return type of the call operator.

## Example

The following Host example checks the interface result against an independent expected type or value.

```cpp
#include <asc/std/type_traits>

using value_type = typename asc::std::integral_constant<int, 7>::value_type;
static_assert(asc::std::is_same_v<value_type, int>);
```

## Related APIs

- [`asc::std::integral_constant`](integral_constant.md)
- [API list for this header](asc_std_type_traits.md)
