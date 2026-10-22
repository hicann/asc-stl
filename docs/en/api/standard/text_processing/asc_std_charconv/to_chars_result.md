# asc::std::to_chars_result

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

Header: `<asc/std/charconv>`.

`asc::std::to_chars_result` holds the position where the character write stopped and the error status.

Standard semantics reference: [cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv).

## Declaration

```cpp
namespace asc::std {
struct to_chars_result;
} // namespace asc::std
```

## Constraints

- Supports all standard signed/unsigned integer types and bases 2 through 36.
- In AI Core SIMD programming, the buffer must be a plain char pointer in the local or generic address space.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/charconv>

bool example()
{
    char text[4] = {};
    asc::std::to_chars_result result = asc::std::to_chars(text, text + 4, 42);
    return result.ec == asc::std::errc{} && result.ptr == text + 2 && text[0] == '4' && text[1] == '2';
}
```

## Related APIs

- [API list for this header](asc_std_charconv.md)
