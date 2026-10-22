# asc::std::is_bind_expression_v

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

Header: `<asc/std/functional>`.

`asc::std::is_bind_expression_v` determines whether a type is a bind expression created by `bind`.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Declaration

```cpp
namespace asc::std {
template<class T> inline constexpr bool is_bind_expression_v = is_bind_expression<T>::value;
}
```

## Constraints

- Standard callable objects and member pointer forms are supported.

## Example

The following Host example demonstrates this interface with concrete inputs and a checkable result.

```cpp
#include <asc/std/functional>

bool example()
{
    auto bound = asc::std::bind(asc::std::plus<int>{}, asc::std::placeholders::_1, 1);
    static_assert(asc::std::is_bind_expression_v<decltype(bound)>);
    static_assert(!asc::std::is_bind_expression_v<int>);
    return bound(2) == 3;
}
```

## Related APIs

- [API list for this header](asc_std_functional.md)
