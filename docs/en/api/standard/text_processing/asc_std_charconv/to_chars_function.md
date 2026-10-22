# asc::std::to_chars (function)

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

`asc::std::to_chars` writes an integer to a character buffer provided by the caller in the specified base.

Standard semantics reference: [cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv).

## Function Prototype

The overloads are in the `asc::std` namespace; the conditions for selecting the integer template exclude bool and the character encoding types.

```cpp
namespace asc::std {
constexpr to_chars_result to_chars(char* first, char* last, char value, int base = 10) noexcept;
}
```

## Parameters

**Template Parameters (integer template only)**

| Parameter | Description |
| --- | --- |
| `T` | A standard signed or unsigned integer type; excludes bool, char, wchar_t, char8_t, char16_t, and char32_t. char and signed/unsigned char have separate fixed overloads. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `first` | Output | The start of the valid character range; it must belong to the same buffer as last. |
| `last` | Input | One past the end of the character range. |
| `value` | Input | The integer value to write out. |
| `base` | Input | The base, from 2 to 36; defaults to 10 when omitted. |

## Return Value

| Return type | Description |
| --- | --- |
| `to_chars_result` | ptr points to the end of the output; success is indicated by an empty error code in ec; value_too_large is reported when the capacity is insufficient, and invalid_argument is reported when base is invalid; no terminating null character is written automatically. |

## Constraints

- Supports all standard signed/unsigned integer types and bases 2 through 36.
- In AI Core SIMD programming, the buffer must be a plain char pointer in the local or generic address space.

## Example

The following Host example provides concrete inputs and checks the result while the object and the underlying storage remain valid.

```cpp
#include <asc/std/charconv>

bool example()
{
    char output[4]{};
    const auto result = asc::std::to_chars(output, output + 4, char(42));
    return result.ptr == output + 2 && result.ec == asc::std::errc{} && output[0] == '4' && output[1] == '2';
}
```

## Related APIs

- [API list for this header](asc_std_charconv.md)
