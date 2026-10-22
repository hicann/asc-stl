# asc::std::wcscat

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

`asc::std::wcscat` appends a wide string to the end of the destination string.

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Function Prototype

```cpp
namespace asc::std {
wchar_t* wcscat(wchar_t* destination, const wchar_t* source) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `destination` | Output | The destination storage that receives the result. This call executes synchronously and the writes are complete when it returns; the destination storage only needs to remain valid for the duration of the call, and sufficient space must be reserved for the content to be written. |
| `source` | Input | The source data or source object. This call executes synchronously and the reads are complete when it returns; the source storage only needs to remain valid for the duration of the call. |

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

decltype(auto) example(wchar_t * destination, const wchar_t * source)
{
    return asc::std::wcscat(destination, source);
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
