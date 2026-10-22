# asc::std::mbrtowc

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

Header: `<asc/std/cwchar>`.

`asc::std::mbrtowc` processes wide characters or multibyte sequences under a multibyte conversion state saved by the caller.

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Function Prototype

```cpp
namespace asc::std {
size_t mbrtowc(wchar_t* output, const char* input, size_t count, mbstate_t* state) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | The writable wchar_t pointer that receives the decoding result; when it is null, the conversion state is still processed, but no character is saved. |
| `input` | Input | The start of the multibyte sequence to decode, from which at most the number of bytes specified by the length parameter is read; the buffer is not required to be zero-terminated. A null pointer is handled according to the empty-string call rule of the corresponding function. |
| `count` | Input | The maximum number of input bytes that may be read; the output object must be valid at the time of writing. |
| `state` | Input/Output | The mbstate_t object that stores the multibyte conversion progress; it is updated according to the conversion result, and a null pointer uses the internal state. |

## Return Value

| Return type | Description |
| --- | --- |
| `size_t` | Returns the number of input bytes consumed by the completed character and writes to output as needed; returns 0 for the null character, size_t(-1) for an encoding error, and size_t(-2) for insufficient input. |

## Constraints

- The Host behavior follows the interface of the same name provided by the system `<cwchar>`; character conversion and collation are affected by the current C locale.
- Device is fixed to stateless single-byte conversion and supports only ASCII and the null character; out-of-range input reports failure as described in the return value of this interface.
- Different character sequences use independent state objects; string output buffers must have sufficient capacity.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cwchar>
#include <asc/std/cstddef>

decltype(auto) example(wchar_t * output, const char * input, asc::std::size_t count, asc::std::mbstate_t * state)
{
    return asc::std::mbrtowc(output, input, count, state);
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
