# asc::std::mbsrtowcs

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

`asc::std::mbsrtowcs` processes wide characters or multibyte sequences under a multibyte conversion state saved by the caller.

This interface is available on Host (full interface) and Device (C locale related interfaces).

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Function Prototype

```cpp
namespace asc::std {
size_t mbsrtowcs(wchar_t* destination, const char** source, size_t count, mbstate_t* state) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `destination` | Output | The destination storage that receives the result. This call executes synchronously and the writes are complete when it returns; the destination storage only needs to remain valid for the duration of the call, and sufficient space must be reserved for the content to be written. |
| `source` | Input/Output | The pointer to the current input cursor; when the null character conversion completes, the cursor is set to null, otherwise it is updated to the next unconverted position. A length query with a null destination does not modify the cursor; the source sequence must remain valid for the duration of the call. |
| `count` | Input | When destination is non-null, the maximum number of wchar_t elements to write; when it is null, the full output length is computed. |
| `state` | Input/Output | The mbstate_t object that stores the multibyte conversion progress; it is updated according to the conversion result, and a null pointer uses the internal state. |

## Return Value

| Return type | Description |
| --- | --- |
| `size_t` | Returns the number of wchar_t elements produced, excluding the terminating null character; returns size_t(-1) for an encoding error. When destination is null, the required number of elements is computed. |

## Constraints

- The Host behavior follows the interface of the same name provided by the system `<cwchar>`; character conversion and collation are affected by the current C locale.
- Device is fixed to stateless single-byte conversion and supports only ASCII and the null character; out-of-range input reports failure as described in the return value of this interface.
- Different character sequences use independent state objects; string output buffers must have sufficient capacity.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cwchar>
#include <asc/std/cstddef>

decltype(auto) example(wchar_t * destination, const char ** source, asc::std::size_t count, asc::std::mbstate_t * state)
{
    return asc::std::mbsrtowcs(destination, source, count, state);
}

bool verify_example()
{
    asc::std::mbstate_t state{};
    const char* source = "AB";
    wchar_t output[4] = {};
    return example(output, &source, 4, &state) == 2 && source == nullptr && output[0] == L'A' && output[1] == L'B' && output[2] == 0;
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
