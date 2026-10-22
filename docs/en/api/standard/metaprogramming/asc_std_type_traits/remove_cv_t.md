# asc::std::remove_cv_t

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

`asc::std::remove_cv_t` yields the type obtained by removing the qualification, reference, or extent indicated by the name, providing the result as a type alias.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<class T> using remove_cv_t = remove_volatile_t<remove_const_t<T>>;
} // namespace asc::std
```

## Constraints

- This helper form uses the same type preconditions and decision rules as [`asc::std::remove_cv`](remove_cv.md); the result corresponds to the `type` of the trait class.

## Example

The following Host example checks the interface result against an independent expected type or value.

```cpp
#include <asc/std/type_traits>

using result_type = asc::std::remove_cv_t<const volatile int>;
static_assert(asc::std::is_same_v<result_type, int>);
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
