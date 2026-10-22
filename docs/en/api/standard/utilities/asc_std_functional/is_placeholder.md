# asc::std::is_placeholder

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

`asc::std::is_placeholder` recognizes bind expressions or argument placeholders at compile time.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Declaration

```cpp
namespace asc::std {
template<class T> struct is_placeholder;
} // namespace asc::std
```

Result semantics: the primary template inherits `asc::std::integral_constant<int, 0>` for non-placeholder types; for placeholder types (`asc::std::placeholders::_1` through `_10`), specializations inherit `asc::std::integral_constant<int, N>`, where `N` is the call argument position of the corresponding placeholder (`N >= 1`). The placeholder implementation template parameter (`int N`) is not part of the public primary template parameters.

## Constraints

- Standard callable objects and member pointer forms are supported.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/functional>
#include <asc/std/type_traits>

bool example()
{
    using first = asc::std::remove_cv_t<decltype(asc::std::placeholders::_1)>;
    static_assert(asc::std::is_placeholder<first>::value == 1);
    static_assert(asc::std::is_placeholder<int>::value == 0);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_functional.md)
