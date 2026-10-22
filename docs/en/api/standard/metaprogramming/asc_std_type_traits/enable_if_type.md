# asc::std::enable_if::type

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

`enable_if<B, T>::type` exists only when the condition holds, which can remove templates that do not satisfy the constraints from the set considered for overload resolution.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

Member of: [`asc::std::enable_if`](enable_if.md).

```cpp
// Excerpt of the declaration inside asc::std::enable_if; template parameters and other members are provided by the owning class.
using type = T;
```

## Constraints

- The member `type` is provided only in the specialization whose Boolean template argument is true, and its result is the template type argument `T`; the false form has no such member.

## Example

The following Host example checks the interface result against an independent expected type or value.

```cpp
#include <asc/std/type_traits>

using result_type = typename asc::std::enable_if<true, int>::type;
static_assert(asc::std::is_same_v<result_type, int>);
```

## Related APIs

- [`asc::std::enable_if`](enable_if.md)
- [API list for this header](asc_std_type_traits.md)
