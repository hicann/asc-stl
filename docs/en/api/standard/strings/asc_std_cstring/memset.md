# asc::std::memset

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

`asc::std::memset` writes the specified number of bytes with the same byte value; AI Core SIMD programming accepts only compatible plain-pointer address spaces.

Standard semantics reference: [cppreference `cstring`](https://en.cppreference.com/w/cpp/header/cstring).

## Function Prototype

```cpp
namespace asc::std {
void* memset(void* destination, int value, size_t count) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `destination` | Output | Destination storage that receives the result. This call executes synchronously and the write is complete when it returns; the destination storage only needs to remain valid for the duration of the call, and sufficient space must be reserved for the content to be written. |
| `value` | Input | Byte value written to each byte; converted to unsigned char before being written. |
| `count` | Input | Number of bytes to operate on; not automatically converted according to the type size of the source or destination object. |

## Return Value

| Return type | Description |
| --- | --- |
| `void *` | Returns the starting pointer of the destination buffer. |

## Constraints

- Use plain pointers on the Host side and in AI Core SIMT programming.
- In AI Core SIMD programming, use plain pointers in the local or generic address space.
- The destination range must be writable and accommodate count bytes; value is first converted to unsigned char and then written byte by byte.

## Example

The following Host example provides concrete inputs and checks the result; the underlying objects and storage remain valid during the check.

```cpp
#include <asc/std/cstring>

bool example()
{
    unsigned char bytes[4]{};
    void* result = asc::std::memset(bytes, 0x41, 4);
    return result == bytes && bytes[0] == 0x41 && bytes[3] == 0x41;
}
```

## Related APIs

- [API list for this header](asc_std_cstring.md)
