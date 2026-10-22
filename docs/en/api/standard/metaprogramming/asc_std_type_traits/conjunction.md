# asc::std::conjunction

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

`asc::std::conjunction` performs short-circuit logical AND on a group of Boolean traits.

Standard semantics reference: [cppreference `type_traits`](https://en.cppreference.com/w/cpp/header/type_traits).

## Declaration

```cpp
namespace asc::std {
template <class... Args>
struct conjunction;
}  // namespace asc::std
```

## Constraints

- Each evaluated argument must provide a `value` convertible to `bool`. It inherits from the first argument that is false, and from the last argument when all are true; an empty parameter pack is true, and the remaining arguments are handled by the short-circuit rules.

## Example

The following Host snippet verifies the result of the type trait on this page with concrete type arguments and `static_assert`.

```cpp
#include <asc/std/type_traits>

void use_trait()
{
    // When all predicates are true, the whole is true
    static_assert(asc::std::conjunction<asc::std::true_type, asc::std::is_integral<int>>::value);
    static_assert(asc::std::conjunction_v<asc::std::is_integral<int>, asc::std::true_type>);
    // Counterexample: if any predicate is false, the whole is false
    static_assert(!asc::std::conjunction_v<asc::std::true_type, asc::std::is_integral<double>>);
    struct no_value {};
    // The first argument is already false; the value of the remaining arguments is not instantiated.
    static_assert(!asc::std::conjunction_v<asc::std::false_type, no_value>);
}
```

## Related APIs

- [API list for this header](asc_std_type_traits.md)
