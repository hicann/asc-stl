# asc::std::mbrtoc32

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

Include the public header `<asc/std/cuchar>` and use `asc::std::mbrtoc32` to convert multibyte input to one UTF code unit. Host uses the system conversion interface; the device side handles only ASCII and the null character.

Host semantics reference: [cppreference character conversion interface](https://en.cppreference.com/w/cpp/header/cuchar).

## Function Prototype

Host imports the system `std::mbrtoc32` via `using`; the exception specification and parameter names follow the system declaration. The following is the device-side declaration; the execution-location macro is omitted. The `__SIZE_TYPE__` used by the device-side implementation is equivalent to the public `asc::std::size_t`.

```cpp
namespace asc::std {
size_t mbrtoc32(char32_t* output, const char* input, size_t count, mbstate_t* state) noexcept;
}
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | When non-null, points to a writable char32_t element; when null, only the conversion result is computed. |
| `input` | Input | The input byte sequence. When non-null on the device side and count is non-zero, only the first byte is read; when null, the reset path is taken. |
| `count` | Input | The maximum number of bytes to read from the input, in bytes. The device side returns `size_t(-2)` when input is non-null and count is 0. |
| `state` | Input/Output | Host keeps the conversion state across calls. The device side resets a non-null state to its initial value only when input is null; other paths do not update it. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::std::size_t` | Host: normally returns the number of bytes consumed; returns 0 for the null character, `size_t(-1)` for an invalid sequence, and `size_t(-2)` for insufficient input; Device side: returns 0 when input is null or the first byte is the null character; returns 1 for a valid non-null ASCII character; returns `size_t(-1)` for anything beyond ASCII; returns `size_t(-2)` when input is non-null and count is 0. |

## Constraints

- The device side supports only ASCII and the null character and does not save incomplete multibyte input. When input is null, it writes the null character to a non-null output and resets a non-null state; do not assume this behavior is identical on all Host systems.
- The input and output storage must remain valid during the call; the input range and output capacity conform to the parameter descriptions.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/cuchar>

bool example()
{
    char32_t output{};
    asc::std::mbstate_t state{};
    auto count = asc::std::mbrtoc32(&output, "A", 1, &state);
    return count == 1 && output == U'A';
}
```

## Related APIs

- [API list for this header](asc_std_cuchar.md)
