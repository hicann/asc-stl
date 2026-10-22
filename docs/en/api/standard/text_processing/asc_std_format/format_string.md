# asc::std::format_string

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

Header: `<asc/std/format>`.

`asc::std::format_string` identifies the char format string type whose format syntax is validated at compile time.

This interface is provided starting from C++20+ mode.

Standard semantics reference: [cppreference `format`](https://en.cppreference.com/w/cpp/header/format).

## Declaration

```cpp
namespace asc::std {
template<class ...Args> using format_string = basic_format_string<char, type_identity_t<Args>...>;
} // namespace asc::std
```

## Constraints

- The compile-time char-array constructor and the format_string alias of basic_format_string<char,Args...>.
- format_to_n_result<char*> and its out/size members.
- Inside the format string, only the validated {} placeholders, escaped braces, and the standard integer d/x/X/o/b syntax for types other than bool/char are accepted.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following snippet shows the alias type with concrete template arguments.

```cpp
#include <asc/std/format>

void use_type()
{
    using selected = asc::std::format_string<int>;
}
```

## Related APIs

- [API list for this header](asc_std_format.md)
