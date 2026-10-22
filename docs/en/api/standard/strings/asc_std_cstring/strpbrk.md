# asc::std::strpbrk

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

Header: `<asc/std/cstring>`.

`asc::std::strpbrk` finds the first character that belongs to the given character set; AI Core SIMD programming accepts only compatible plain-pointer address spaces.

Standard semantics reference: [cppreference `cstring`](https://en.cppreference.com/w/cpp/header/cstring).

## Function Prototype

```cpp
namespace asc::std {
[[nodiscard]] constexpr const char* strpbrk(const char* value, const char* accepted) noexcept;
}
```

```cpp
namespace asc::std {
[[nodiscard]] constexpr char* strpbrk(char* value, const char* accepted) noexcept;
}
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Address of the first byte of the narrow string to search, null-terminated. |
| `accepted` | Input | Accepted character set, given as a null-terminated narrow string; a hit on any character in it counts as a successful find. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Address of the first byte of the narrow string to search, null-terminated. |
| `accepted` | Input | Accepted character set, given as a null-terminated narrow string; a hit on any character in it counts as a successful find. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `char *` | Returns a pointer to the matching position; returns a null pointer when there is no match. |
| Prototype 2 | `const char *` | Returns a pointer to the matching position; returns a null pointer when there is no match. |

## Constraints

- Use plain pointers on the Host side and in AI Core SIMT programming.
- In AI Core SIMD programming, use plain pointers in the local or generic address space.
- This interface accesses inputs read-only and does not restrict read-only inputs from being identical to or overlapping each other; the returned borrowed pointer must be used while the original character storage is still valid.

## Example

The following Host example provides concrete inputs and checks the result; the underlying objects and storage remain valid during the check.

```cpp
#include <asc/std/cstring>

bool example()
{
    char text[] = "abc123";
    return asc::std::strpbrk(text, "0123456789") == text + 3;
}
```

## Related APIs

- [API list for this header](asc_std_cstring.md)
