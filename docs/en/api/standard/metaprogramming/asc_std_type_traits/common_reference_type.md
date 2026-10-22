# asc::std::common_reference::type

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

`asc::std::common_reference::type` provides the member type computed by the type trait, mapping, or adaptor.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

When `common_reference<Types...>` can resolve a type under the common reference rules, the member `type` is provided. Query it through the owning trait class:

```cpp
using reference_type = typename asc::std::common_reference<int&, const int&>::type;
```

## Constraints

- When no common reference type is available, `type` is not provided and must not be unconditionally written as one of the input types. For the exact decision order, see [common_reference](common_reference.md).

## Example

The following Host example checks the interface result against an independent expected type or value.

```cpp
#include <asc/std/type_traits>

using result_type = typename asc::std::common_reference<int&, const int&>::type;
static_assert(asc::std::is_same_v<result_type, const int&>);
```

## Related APIs

- [`asc::std::common_reference`](common_reference.md)
- [API list for this header](asc_std_type_traits.md)
