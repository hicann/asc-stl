# asc::std::basic_common_reference

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

`basic_common_reference` is the computation point for common reference types specialized by users; it takes two types and their qualification propagation templates.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template <class T, class U, template <class> class TQual, template <class> class UQual, class = void>
struct basic_common_reference;
}  // namespace asc::std
```

## Constraints

- This primary template acts as the customization point for common reference computation and by default provides no result member `type`; custom specializations express the corresponding reference/cv-qualifications through `TQual` and `UQual` and must satisfy the common reference semantics.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

struct Measure {};
struct Width : Measure {};
struct Height : Measure {};

// The two own types share the Measure base class; the customization point preserves the references and cv-qualifiers of the inputs.
namespace asc::std {
template <template <class> class TQual, template <class> class UQual>
struct basic_common_reference<Width, Height, TQual, UQual> {
    using type = common_reference_t<TQual<Measure>, UQual<Measure>>;
};
template <template <class> class TQual, template <class> class UQual>
struct basic_common_reference<Height, Width, TQual, UQual> : basic_common_reference<Width, Height, UQual, TQual> {};
}  // namespace asc::std

void use_trait()
{
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<Width, Height>, Measure>);
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<Width&, Height&>, Measure&>);
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<const Width&, Height&>, const Measure&>);
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<Height&, Width&>, Measure&>);
    // Both sides are convertible to the selected common reference; this checks more than the customization point returning a type name.
    static_assert(asc::std::is_convertible_v<Width&, asc::std::common_reference_t<Width&, Height&>>);
    static_assert(asc::std::is_convertible_v<Height&, asc::std::common_reference_t<Width&, Height&>>);
    static_assert(asc::std::is_same_v<asc::std::common_reference_t<int, long>, long>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
