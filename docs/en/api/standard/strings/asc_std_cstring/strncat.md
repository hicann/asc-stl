# asc::std::strncat

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

`asc::std::strncat` appends at most the specified number of narrow characters; AI Core SIMD programming accepts only compatible plain-pointer address spaces.

Standard semantics reference: [cppreference `cstring`](https://en.cppreference.com/w/cpp/header/cstring).

## Function Prototype

```cpp
namespace asc::std {
constexpr char* strncat(char* destination, const char* source, size_t count) noexcept;
}
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `destination` | Input/Output | destination must be a zero-terminated string on entry; the capacity must be at least the original length + min(count, strlen(source)) + 1, and a terminating null character is additionally written at the end. |
| `source` | Input | Source data or source object. This call executes synchronously and the read is complete when it returns; the source storage only needs to remain valid for the duration of the call. |
| `count` | Input | Number of elements to operate on. |

## Return Value

| Return type | Description |
| --- | --- |
| `char *` | Returns the starting pointer of the destination buffer. |

## Constraints

- Use plain pointers on the Host side and in AI Core SIMT programming.
- In AI Core SIMD programming, use plain pointers in the local or generic address space.
- The source and destination ranges must not overlap; the caller provides readable input, writable capacity, and any necessary terminating null character as described in Parameters.

## Example

The following Host example provides concrete inputs and checks the result; the underlying objects and storage remain valid during the check.

```cpp
#include <asc/std/cstring>

bool example()
{
    char target[8] = "ab";
    char* result = asc::std::strncat(target, "cdef", 2);
    return result == target && target[2] == 'c' && target[3] == 'd' && target[4] == '\0';
}
```

## Related APIs

- [API list for this header](asc_std_cstring.md)
