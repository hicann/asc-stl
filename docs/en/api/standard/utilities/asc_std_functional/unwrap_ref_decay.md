# asc::std::unwrap_ref_decay

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

`asc::std::unwrap_ref_decay` computes the result type of unwrapping a reference wrapper and decaying the type.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Declaration

```cpp
namespace asc::std {
template<class T> struct unwrap_ref_decay;
} // namespace asc::std
```

## Constraints

- Standard callable objects and pointer-to-member forms are supported.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/functional>
#include <asc/std/type_traits>

bool example()
{
    static_assert(asc::std::is_same_v<typename asc::std::unwrap_ref_decay<const asc::std::reference_wrapper<int>&>::type, int&>);
    static_assert(asc::std::is_same_v<typename asc::std::unwrap_ref_decay<int(&)[3]>::type, int*>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_functional.md)
