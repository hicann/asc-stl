# asc::std::wmemset

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

`asc::std::wmemset` writes the specified number of wchar_t elements as the same wchar_t element value.

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Function Prototype

```cpp
namespace asc::std {
wchar_t* wmemset(wchar_t* destination, wchar_t value, size_t count) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `destination` | Output | The destination storage that receives the result. This call executes synchronously and the writes are complete when it returns; the destination storage only needs to remain valid for the duration of the call, and sufficient space must be reserved for the content to be written. |
| `value` | Input | The wide character used for filling. |
| `count` | Input | The number of wchar_t elements to write. |

## Return Value

| Return type | Description |
| --- | --- |
| `wchar_t *` | Returns the pointer to the start of the destination buffer. |

## Constraints

- 18 standard function names and 23 callable signatures: wmemcpy/wmemmove/wmemchr/wmemcmp/wmemset, wcscpy/wcsncpy/wcscat/wcsncat, wcschr/wcsrchr, wcscmp/wcsncmp, wcsspn/wcscspn/wcspbrk/wcsstr/wcslen.
- The 5 search functions include const and mutable pointer overloads.
- Host delegates to the system, and Device is a pure computation implementation.
- Host, AI Core SIMD programming, and AI Core SIMT programming are compatible with the plain-pointer domain.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cwchar>
#include <asc/std/cstddef>

decltype(auto) example(wchar_t * destination, wchar_t value, asc::std::size_t count)
{
    return asc::std::wmemset(destination, value, count);
}

bool verify_example()
{
    wchar_t output[4] = {};
    return example(output, L'x', 3) == output && output[0] == L'x' && output[1] == L'x' && output[2] == L'x' && output[3] == 0;
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
