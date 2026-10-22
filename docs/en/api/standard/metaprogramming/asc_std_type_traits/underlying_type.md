# asc::std::underlying_type

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

`asc::std::underlying_type` obtains the underlying integer type of an enum type.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template<class T> struct underlying_type;
} // namespace asc::std
```

## Constraints

- `T` must be an enumeration type, and its underlying integer type must already be determined.
- For non-enumeration types, the presence of the result member `type` must not be assumed; when used in templates, check the enumeration condition first or participate through substitution failure constraints.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    enum class sample_enum : unsigned int { value };
    // Positive example: an enumeration with the underlying type fixed to unsigned int
    static_assert(asc::std::is_same_v<asc::std::underlying_type_t<sample_enum>, unsigned int>);
    static_assert(asc::std::is_same_v<typename asc::std::underlying_type<sample_enum>::type, unsigned int>);
    // Counterexample: the underlying type is not int
    static_assert(!asc::std::is_same_v<asc::std::underlying_type_t<sample_enum>, int>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
