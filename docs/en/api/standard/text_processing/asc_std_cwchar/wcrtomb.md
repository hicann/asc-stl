# asc::std::wcrtomb

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

`asc::std::wcrtomb` processes wide characters or multibyte sequences under a multibyte conversion state saved by the caller.

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Function Prototype

```cpp
namespace asc::std {
size_t wcrtomb(char* output, wchar_t input, mbstate_t* state) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | The pointer to the destination buffer that receives the multibyte result, whose capacity must be at least MB_CUR_MAX bytes; when it is a null pointer, no external storage is written. |
| `input` | Input | The wide character to convert to a multibyte sequence. |
| `state` | Input/Output | The mbstate_t conversion state, maintained across calls; this conversion continues from that state and updates it when it finishes. |

## Return Value

| Return type | Description |
| --- | --- |
| `size_t` | Returns the number of bytes of the multibyte sequence written, including the bytes required for the null character; returns size_t(-1) for an encoding error. |

## Constraints

- The Host behavior follows the interface of the same name provided by the system `<cwchar>`; character conversion and collation are affected by the current C locale.
- Device is fixed to stateless single-byte conversion and supports only ASCII and the null character; out-of-range input reports failure as described in the return value of this interface.
- Different character sequences use independent state objects; string output buffers must have sufficient capacity.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cwchar>

decltype(auto) example(char * output, wchar_t input, asc::std::mbstate_t * state)
{
    return asc::std::wcrtomb(output, input, state);
}

bool verify_example()
{
    asc::std::mbstate_t state{};
    char output[8] = {};
    return example(output, L'A', &state) == 1 && output[0] == 'A';
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
