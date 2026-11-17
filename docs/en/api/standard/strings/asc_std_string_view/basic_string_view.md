# asc::std::basic_string_view

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

`asc::std::basic_string_view` observes a contiguous character sequence in a non-owning way.

Standard semantics reference: [cppreference `string_view`](https://en.cppreference.com/w/cpp/header/string_view).

## Declaration

```cpp
namespace asc::std {
template<class CharT, class Traits = char_traits<CharT>> class basic_string_view;
} // namespace asc::std
```

## Constraints

- This type does not own the character storage. The storage of the original character array or string must cover the entire period of use of the view, pointers, and iterators; after the original storage is destroyed or invalidated by reallocation, it must not be accessed further through the view.
- For string tensors with separate lengths, construct a view from a pointer and a count; no terminating `'\0'` is required, and an embedded null character remains part of the data. `find_first_not_of`/`find_last_not_of` with `remove_prefix`/`remove_suffix` can trim whitespace without copying. Handle an all-whitespace field, for which the search returns `npos`, before computing removal counts; never remove more than the current `size()`.

- Provides construction, iteration, and access interfaces other than at, plus remove_prefix, remove_suffix, swap, data, size, starts_with, ends_with, and non-throwing compare/find interfaces.
- AI Core SIMD programming supports only plain character pointers in the local or generic address space.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/string_view>

bool example()
{
    asc::std::string_view text("hello");
    text.remove_prefix(1);
    return text.size() == 4 && text[0] == 'e' && text.back() == 'o';
}
```

## Related APIs

- [API list for this header](asc_std_string_view.md)
