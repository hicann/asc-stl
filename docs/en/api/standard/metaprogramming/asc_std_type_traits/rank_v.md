# asc::std::rank_v

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

`asc::std::rank_v` obtains the number of dimensions of an array type, providing the result as a size_t variable template.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

The following declaration summary uses the `value` of the public trait class to express the equivalent constant value.

```cpp
namespace asc::std {
template<class T>
inline constexpr size_t rank_v = rank<T>::value;
} // namespace asc::std
```

## Constraints

- Provides the trait class and the _v helper form.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/type_traits>

static_assert((asc::std::rank_v<int>) == 0);
static_assert(asc::std::rank_v<int[][3]> == 2);
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
