# asc::std::wcsspn

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

`asc::std::wcsspn` counts the length of the initial run of characters that belong to the given character set.

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Function Prototype

```cpp
namespace asc::std {
size_t wcsspn(const wchar_t* input, const wchar_t* accepted) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `input` | Input | The string to scan, terminated by a zero wide character. |
| `accepted` | Input | The set of accepted characters, terminated by a zero wide character. |

## Return Value

| Return type | Description |
| --- | --- |
| `size_t` | Returns the number of leading consecutive characters that satisfy this interface's matching rule. |

## Constraints

- 18 standard function names and 23 callable signatures: wmemcpy/wmemmove/wmemchr/wmemcmp/wmemset, wcscpy/wcsncpy/wcscat/wcsncat, wcschr/wcsrchr, wcscmp/wcsncmp, wcsspn/wcscspn/wcspbrk/wcsstr/wcslen.
- The 5 search functions include const and mutable pointer overloads.
- Host delegates to the system, and Device is a pure computation implementation.
- Host, AI Core SIMD programming, and AI Core SIMT programming are compatible with the plain-pointer domain.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/cwchar>

decltype(auto) example(const wchar_t * input, const wchar_t * accepted)
{
    return asc::std::wcsspn(input, accepted);
}

bool verify_example()
{
    return example(L"abcde", L"abc") == 3;
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
