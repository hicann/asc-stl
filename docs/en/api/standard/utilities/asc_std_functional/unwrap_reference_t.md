# asc::std::unwrap_reference_t

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

`asc::std::unwrap_reference_t` obtains the reference type stored in a reference wrapper or the type decayed according to the rules.

Standard semantics reference: [cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional).

## Declaration

```cpp
namespace asc::std {
template<class T> using unwrap_reference_t = typename unwrap_reference<T>::type;
} // namespace asc::std
```

## Constraints

- Standard callable objects and pointer-to-member forms are supported.

## Example

The following Host example checks the alias or marker result with concrete types and an independent expectation.

```cpp
#include <asc/std/functional>
#include <asc/std/type_traits>

void use_type()
{
    using selected = asc::std::unwrap_reference_t<int>;
    static_assert(asc::std::is_same_v<selected, int>);
}
```

## Related APIs

- [API list for this header](asc_std_functional.md)
