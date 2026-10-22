# asc::std::format_to_n_result

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

`asc::std::format_to_n_result` holds the output position and the full result size of bounded formatting.

This result type is provided starting from C++17; creating a result object performs no formatting or format string validation.

Standard semantics reference: [cppreference `format`](https://en.cppreference.com/w/cpp/header/format).

## Declaration

```cpp
namespace asc::std {
template<class Out>
struct format_to_n_result {
    Out out;
    ptrdiff_t size;
};
} // namespace asc::std
```

## Constraints

- `Out` is the output position type; `out` records the end position of the write, and `size` records the untruncated result length.
- The aggregate itself does not own the output buffer. A pointer-form `out` is usable only while the corresponding buffer is still valid.
- Typed formatting calls such as `format_to_n` still require C++20 and compiler support for `consteval`, preserving immediate format string validation. The result type being available in C++17 does not mean these calls are also available.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/format>

bool example()
{
    char output[3] = {};
    asc::std::format_to_n_result<char*> result{output + 2, 5};
    return result.out == output + 2 && result.size == 5;
}
```

## Related APIs

- [API list for this header](asc_std_format.md)
