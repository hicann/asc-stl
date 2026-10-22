# asc::std::default_accessor::offset

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

`asc::std::default_accessor::offset` moves the underlying data handle according to the mapping result.

Standard semantics reference: [cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan).

## Function Prototype

Member of: [`asc::std::default_accessor`](default_accessor.md).

```cpp
// Excerpt of the declaration inside the asc::std::default_accessor class; template parameters and other members are provided by the owning class.
constexpr data_handle_type offset(data_handle_type pointer, size_t index) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pointer` | Input | The element data handle to be advanced. |
| `index` | Input | The number of elements to advance, a non-negative value; the result is pointer + index. |

## Return Value

| Return type | Description |
| --- | --- |
| `data_handle_type` | Returns the underlying storage offset that the given multidimensional index maps to. |

## Constraints

- Host, AI Core SIMD programming, and AI Core SIMT programming are compatible with the plain pointer domain.

## Example

The following Host example uses concrete inputs and checks the observable result of the interface.

```cpp
#include <asc/std/mdspan>

bool example()
{
    int values[4] = {1, 2, 3, 4};
    asc::std::default_accessor<int> accessor;
    int* result = accessor.offset(values, 2);
    return result == values + 2 && *result == 3;
}
```

## Related APIs

- [`asc::std::default_accessor`](default_accessor.md)
- [API list for this header](asc_std_mdspan.md)
