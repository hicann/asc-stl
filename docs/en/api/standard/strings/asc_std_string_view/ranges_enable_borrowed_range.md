# asc::std::ranges::enable_borrowed_range

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

`asc::std::ranges::enable_borrowed_range<basic_string_view<C,T>>` is provided by `<asc/std/string_view>`, originates from the C++20 borrowed-range registration, and ASC-STL provides it in both C++17 and C++20

Standard semantics reference: [cppreference `string_view`](https://en.cppreference.com/w/cpp/header/string_view).

## Declaration

```cpp
namespace asc::std::ranges {
template<class CharT, class Traits>
inline constexpr bool enable_borrowed_range<asc::std::basic_string_view<CharT, Traits>> = true;
} // namespace asc::std::ranges
```

This is a variable template specialization with the value `true`, indicating that the type satisfies the corresponding view/borrowed-range registration.

## Constraints

- borrowed_range only indicates that the iterator does not depend on the view object itself and does not extend the lifetime of the external character storage; the underlying characters must still be valid during access.

- Originates from the C++20 borrowed-range registration; ASC-STL provides it in both C++17 and C++20.

## Example

The following Host example provides concrete inputs and checks the result; the underlying objects and storage remain valid during the check.

```cpp
#include <asc/std/string_view>
#include <asc/std/ranges>

bool example()
{
    static_assert(asc::std::ranges::enable_borrowed_range<asc::std::string_view>);
    return true;
}
```

## Related APIs

- [API list for this header](asc_std_string_view.md)
