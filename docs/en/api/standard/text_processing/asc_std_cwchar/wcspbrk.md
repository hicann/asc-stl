# asc::std::wcspbrk

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

`asc::std::wcspbrk` finds the first character that belongs to the given character set.

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Function Prototype

### Prototype 1

```cpp
namespace asc::std {
const wchar_t* wcspbrk(const wchar_t* input, const wchar_t* accepted) noexcept;
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
wchar_t* wcspbrk(wchar_t* input, const wchar_t* accepted) noexcept;
} // namespace asc::std
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `input` | Input | The string to scan, terminated by a zero wide character. |
| `accepted` | Input | The set of accepted characters, terminated by a zero wide character. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `input` | Input | The string to scan, terminated by a zero wide character. |
| `accepted` | Input | The set of accepted characters, terminated by a zero wide character. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `const wchar_t *` | Returns the pointer to the matching position; returns a null pointer when there is no match. |
| Prototype 2 | `wchar_t *` | Returns the pointer to the matching position; returns a null pointer when there is no match. |

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
    return asc::std::wcspbrk(input, accepted);
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
