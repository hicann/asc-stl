# asc::std::from_chars (function template)

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

`asc::std::from_chars` parses an integer from a character range in the specified base.

Standard semantics reference: [cppreference `charconv`](https://en.cppreference.com/w/cpp/header/charconv).

## Function Prototype

The overloads are in the `asc::std` namespace; the conditions for selecting the integer template exclude bool and the character encoding types.

```cpp
namespace asc::std {
template<class T, enable_if_t<__is_integer_v<T>, int> = 0>
constexpr from_chars_result from_chars(const char* first, const char* last, T& value, int base = 10) noexcept;
}
```

```cpp
namespace asc::std {
constexpr from_chars_result from_chars(const char* first, const char* last, signed char& value, int base = 10) noexcept;
}
```

```cpp
namespace asc::std {
constexpr from_chars_result from_chars(const char* first, const char* last, unsigned char& value, int base = 10) noexcept;
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
| `first` | Input | The start of the valid character range; it must belong to the same buffer as last. |
| `last` | Input | One past the end of the character range. |
| `value` | Input/Output | Receives the parsed value; kept unchanged on failure. |
| `base` | Input | The base, from 2 to 36; defaults to 10 when omitted. |

## Return Value

| Return type | Description |
| --- | --- |
| `from_chars_result` | ptr points to where parsing stopped; success is indicated by an empty error code in ec, and value is written; when no character matches or the value is outside the representable range, the corresponding error is reported and value is kept unchanged. |

## Constraints

- Supports all standard signed/unsigned integer types and bases 2 through 36.
- Leading whitespace and `+` are not accepted; only signed destinations accept `-`. A `0x` prefix is not skipped automatically, even when `base` is 16.
- In a string-tensor-to-integer operator, `ec == errc{}` only means that a numeric prefix was parsed successfully. To accept an entire field, also require `ptr == last`: `"42x"` parses 42 successfully and stops at `x`. Any whitespace trimming is an explicit caller policy. On failure, do not reuse the old `value` as this row's output.
- In AI Core SIMD programming, the buffer must be a plain char pointer in the local or generic address space.

## Example

The following Host example provides concrete inputs and checks the result while the object and the underlying storage remain valid.

```cpp
#include <asc/std/charconv>

bool example()
{
    const char input[] = "42";
    int value = 0;
    const auto result = asc::std::from_chars(input, input + 2, value);
    if (result.ptr != input + 2 || result.ec != asc::std::errc{} || value != 42) {
        return false;
    }
    const char partial[] = "42x";
    const auto prefix = asc::std::from_chars(partial, partial + 3, value);
    const bool whole_field = prefix.ec == asc::std::errc{} && prefix.ptr == partial + 3;
    return prefix.ec == asc::std::errc{} && prefix.ptr == partial + 2 && !whole_field;
}
```

## Related APIs

- [API list for this header](asc_std_charconv.md)
