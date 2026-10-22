# asc::std::format_to_n

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

`asc::std::format_to_n` validates the format string and performs fixed-length formatting within the caller's capacity or result-size constraints.

This interface is provided starting from C++20+ mode.

Standard semantics reference: [cppreference `format`](https://en.cppreference.com/w/cpp/header/format).

## Function Prototype

```cpp
namespace asc::std {
template<class... Args> constexpr format_to_n_result<char*> format_to_n(char* output, ptrdiff_t count, format_string<Args...> format, Args&&... args) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Args` | List of argument types to format, deduced from args. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Output iterator that receives the formatted characters; a raw pointer must point to sufficiently writable storage. At most the specified n characters are written; the returned information distinguishes the actual write position from the full result length. |
| `count` | Input | Maximum number of characters to write; when count <= 0 nothing is written, but the full result length is still computed. |
| `format` | Input | Compile-time validated format string; the replacement fields and format specifiers match the corresponding arguments in args. |
| `args` | Input | Values corresponding to the replacement fields of the format string; formatted according to their actual types. |

## Return Value

| Return type | Description |
| --- | --- |
| `format_to_n_result<char *>` | out is the end of what was actually written; size is the length of the full formatted result, which may be greater than count; no null character is appended automatically. |

## Constraints

- Provided starting from C++20. Supports the default formats of bool, char, and C strings, as well as the default format and the d/x/X/o/b radix formats of standard integers other than bool/char.
- Escaped braces are supported and no dynamic allocation is performed; the format string and the arguments must satisfy the type and field requirements.
- The caller is responsible for the writable buffer capacity and its lifetime; format_to requires the full capacity, and format_to_n writes at most max(count, 0) characters.
- Can be used on the Host, in AI Core SIMD programming, and in AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the result while the object and the underlying storage remain valid.

```cpp
#include <asc/std/format>

bool example()
{
    char output[4]{};
    const auto result = asc::std::format_to_n(output, 2, "{}", 123);
    return result.out == output + 2 && result.size == 3 && output[0] == '1' && output[1] == '2';
}
```

## Related APIs

- [API list for this header](asc_std_format.md)
