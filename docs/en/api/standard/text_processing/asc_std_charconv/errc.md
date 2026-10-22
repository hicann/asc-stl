# asc::std::errc

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

Header: `<asc/std/charconv>`, `<asc/std/system_error>`.

`asc::std::errc` lists the error values supported by the integer conversions and the lightweight error interfaces in this release.

Standard semantics reference: [cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv).

## Declaration

```cpp
namespace asc::std {
enum class errc;
} // namespace asc::std
```

This prototype corresponds to the headers: `<asc/std/charconv>`, `<asc/std/system_error>`.

## Constraints

- Supports all standard signed/unsigned integer types and bases 2 through 36.
- In AI Core SIMD programming, the buffer must be a plain char pointer in the local or generic address space.
- Provides the invalid_argument, result_out_of_range, and value_too_large error values, the corresponding traits, and enumeration comparison operations.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/charconv>

bool example()
{
    const char text[] = "x";
    int value = 7;
    auto result = asc::std::from_chars(text, text + 1, value);
    return result.ec == asc::std::errc::invalid_argument && value == 7;
}
```

## Related APIs

- [API list for this header](asc_std_charconv.md)
