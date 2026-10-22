# asc::std::decay::type

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

`asc::std::decay::type` provides the member type computed by the type trait, mapping, or adaptor.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

`asc::std::decay<T>::type` first removes references from T: arrays convert to a pointer to their element, functions convert to a function pointer, and the other types have their top-level cv-qualifiers removed.

```cpp
using ArrayResult = asc::std::decay<int[3]>::type;  // int*
using ValueResult = asc::std::decay<const int&>::type; // int
```

## Constraints

- The member `type` is the result computed by the owning trait class. References are removed first; arrays convert to a pointer to their first element, functions convert to a function pointer, and the other types have their top-level cv-qualifiers removed. It only computes a type and creates no object.

## Example

The following Host example checks the interface result against an independent expected type or value.

```cpp
#include <asc/std/type_traits>

using result_type = typename asc::std::decay<const int&>::type;
static_assert(asc::std::is_same_v<result_type, int>);
static_assert(asc::std::is_same_v<asc::std::decay_t<int[3]>, int*>);
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
