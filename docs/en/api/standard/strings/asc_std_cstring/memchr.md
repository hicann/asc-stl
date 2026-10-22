# asc::std::memchr

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

`asc::std::memchr` finds a target byte within the specified byte range; AI Core SIMD programming accepts only compatible plain-pointer address spaces.

Standard semantics reference: [cppreference `cstring`](https://en.cppreference.com/w/cpp/header/cstring).

## Function Prototype

```cpp
namespace asc::std {
[[nodiscard]] const void* memchr(const void* value, int character, size_t count) noexcept;
}
```

```cpp
namespace asc::std {
[[nodiscard]] void* memchr(void* value, int character, size_t count) noexcept;
}
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Address of the first byte of the byte buffer to search; the readable range contains at least count bytes. |
| `character` | Input | Target byte value to find; compared byte by byte after interpretation as unsigned char. |
| `count` | Input | Number of bytes to search, that is, the buffer length, in bytes. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | Address of the first byte of the byte buffer to search; the readable range contains at least count bytes. |
| `character` | Input | Target byte value to find; compared byte by byte after interpretation as unsigned char. |
| `count` | Input | Number of bytes to search, that is, the buffer length, in bytes. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `const void *` | Returns a pointer to the matching position; returns a null pointer when there is no match. |
| Prototype 2 | `void *` | Returns a pointer to the matching position; returns a null pointer when there is no match. |

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
    const char text[] = "abca";
    const void* found = asc::std::memchr(text, 'b', 4);
    return found == text + 1;
}
```

## Related APIs

- [API list for this header](asc_std_cstring.md)
