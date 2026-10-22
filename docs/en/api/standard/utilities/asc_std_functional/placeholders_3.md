# asc::std::placeholders::_3

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

`asc::std::placeholders::_3` denotes the placeholder for the 3rd argument of a bind-expression call.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Declaration

The following is the placeholder object declaration; `__ph` is the implementation type, and the caller uses `placeholders::_3` directly without naming its type.

```cpp
namespace asc::std::placeholders {
inline constexpr __ph<3> _3{};
}
```

## Constraints

- Standard callable objects and pointer-to-member forms are supported.

## Example

The following Host example demonstrates this interface with concrete inputs and a checkable result.

```cpp
#include <asc/std/functional>

bool example()
{
    static_assert(asc::std::is_placeholder_v<decltype(asc::std::placeholders::_3)> == 3);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_functional.md)
