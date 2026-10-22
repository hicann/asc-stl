# asc::std::literals::string_view_literals

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

Header: `<asc/std/string_view>`.

`asc::std::literals::string_view_literals` organizes the public namespace for the corresponding string view literal operators.

Standard semantics reference: [cppreference `string_view`](https://en.cppreference.com/w/cpp/header/string_view).

## Declaration

```cpp
namespace asc::std {
inline namespace literals {
inline namespace string_view_literals {}
}
}
```

## Constraints

- Organizes the sv literal operators; the literal for each character type produces the corresponding basic_string_view, and no view member functions are provided. The view borrows the static storage of the string literal.
- AI Core SIMD programming supports only plain character pointers in the local or generic address space.

## Example

The following Host example provides concrete inputs and checks the result; the underlying objects and storage remain valid during the check.

```cpp
#include <asc/std/string_view>

bool example()
{
    constexpr auto value = asc::std::literals::string_view_literals::operator""sv("abc", 3);
    static_assert(value.size() == 3 && value[1] == 'b');
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_string_view.md)
