# asc::std::variant_alternative_t

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

Header: `<asc/std/variant>`.

`asc::std::variant_alternative_t` obtains the type of the element or alternative at the given index.

Standard semantics reference: [cppreference `variant`](https://en.cppreference.com/w/cpp/header/variant).

## Declaration

```cpp
namespace asc::std {
template<::std::size_t Index, class T> using variant_alternative_t = typename variant_alternative<Index, T>::type;
} // namespace asc::std
```

## Constraints

- Alternative types on the device side and the selected construction, assignment, and swap operations must not throw.

## Example

The following Host example checks the alias or tag result with concrete types and an independent expectation.

```cpp
#include <asc/std/variant>
#include <asc/std/type_traits>

void use_type()
{
    using selected = asc::std::variant_alternative_t<0, asc::std::variant<int, float>>;
    static_assert(asc::std::is_same_v<selected, int>);
}
```

## Related APIs

- [API list for this header](asc_std_variant.md)
