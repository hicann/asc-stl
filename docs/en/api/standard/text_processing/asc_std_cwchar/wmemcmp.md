# asc::std::wmemcmp

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

`asc::std::wmemcmp` compares two memory regions element by element as wchar_t elements.

Standard semantics reference: [cppreference `cwchar`](https://en.cppreference.com/w/cpp/header/cwchar).

## Function Prototype

```cpp
namespace asc::std {
int wmemcmp(const wchar_t* left, const wchar_t* right, size_t count) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | The address of the first element of the left wide character array in the comparison; at least count wide characters must be readable. |
| `right` | Input | The address of the first element of the right wide character array in the comparison; at least count wide characters must be readable. |
| `count` | Input | The number of wide characters participating in the element-by-element comparison. |

## Return Value

| Return type | Description |
| --- | --- |
| `int` | Returns a comparison result less than, equal to, or greater than zero. |

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

decltype(auto) example(const wchar_t * left, const wchar_t * right, asc::std::size_t count)
{
    return asc::std::wmemcmp(left, right, count);
}

bool verify_example()
{
    return example(L"abc", L"abc", 3) == 0 && example(L"abc", L"abd", 3) < 0;
}
```

## Related APIs

- [API list for this header](asc_std_cwchar.md)
