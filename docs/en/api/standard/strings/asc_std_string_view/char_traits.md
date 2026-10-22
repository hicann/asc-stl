# asc::std::char_traits

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

`asc::std::char_traits` defines the operation policy for character comparison, copying, and length computation.

Standard semantics reference: [cppreference `string_view`](https://en.cppreference.com/w/cpp/header/string_view).

## Declaration

```cpp
namespace asc::std {
template<class CharT> class char_traits;
} // namespace asc::std
```

## Constraints

- Provides the character type and its integer representation type, plus static character operations such as assign, eq, lt, compare, length, find, move, and copy; it does not itself hold a string view or own character storage.
- AI Core SIMD programming supports only plain character pointers in the local or generic address space.

## Example

The following Host example provides concrete inputs and checks the result; the underlying objects and storage remain valid during the check.

```cpp
#include <asc/std/string_view>

bool example()
{
    using T = asc::std::char_traits<char>;
    return T::length("abc") == 3 && T::eq('a', 'a') && T::lt('a', 'b');
}
```

## Related APIs

- [API list for this header](asc_std_string_view.md)
