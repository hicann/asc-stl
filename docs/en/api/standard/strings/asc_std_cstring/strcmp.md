# asc::std::strcmp

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

`asc::std::strcmp` compares two narrow strings character by character; AI Core SIMD programming accepts only compatible plain-pointer address spaces.

Standard semantics reference: [cppreference `cstring`](https://en.cppreference.com/w/cpp/header/cstring).

## Function Prototype

```cpp
namespace asc::std {
[[nodiscard]] constexpr int strcmp(const char* left, const char* right);
}
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input | Address of the first byte of the left narrow string to compare, null-terminated. |
| `right` | Input | Address of the first byte of the right narrow string to compare, null-terminated. |

## Return Value

| Return type | Description |
| --- | --- |
| `int` | Returns a comparison result less than, equal to, or greater than zero, indicating that the left sequence is less than, equal to, or greater than the right sequence, respectively. |

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
    return asc::std::strcmp("abc", "abd") < 0 && asc::std::strcmp("abc", "abc") == 0;
}
```

## Related APIs

- [API list for this header](asc_std_cstring.md)
