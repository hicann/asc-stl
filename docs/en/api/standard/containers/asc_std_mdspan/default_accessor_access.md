# asc::std::default_accessor::access

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

Header: `<asc/std/mdspan>`.

`asc::std::default_accessor::access` obtains, through the accessor, a reference to the element at the given index.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

Member of: [`asc::std::default_accessor`](default_accessor.md).

```cpp
// Excerpt of the declaration inside the asc::std::default_accessor class; template parameters and other members are provided by the owning class.
constexpr reference access(data_handle_type pointer, size_t index) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | Data handle (element pointer) pointing to the storage of the element to be accessed; the index-th element from it onward must be accessible. |
| `index` | Input | Element subscript relative to pointer, starting from 0; returns a reference to the element at *(pointer + index). |

## Return Value

| Return type | Description |
| --- | --- |
| `reference` | Returns the element reference or access result corresponding to the given multidimensional index. |

## Constraints

- Host, AI Core SIMD programming, and AI Core SIMT programming are compatible with the plain pointer domain.

## Example

The following Host snippet completes the access within the lifetime of the underlying storage, returns a copy of the element value, and does not pass a reference to a local array element out of the function.

```cpp
#include <asc/std/mdspan>

int read_first_element()
{
    alignas(16) int values[4] = {1, 2, 3, 4};
    asc::std::default_accessor<int> accessor{};
    // Precondition: index 0 < 4; access performs no bounds checking
    return accessor.access(values, 0);
}
```

## Related APIs

- [`asc::std::default_accessor`](default_accessor.md)
- [API list for this header](asc_std_mdspan.md)
