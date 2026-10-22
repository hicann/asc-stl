# asc::tensor_copy_descriptor::extent

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

Header: `<asc/tensor_copy>`.

`asc::tensor_copy_descriptor::extent` returns the valid tensor extent of the specified dimension.

## Function Prototype

The following is an in-class declaration of `asc::tensor_copy_descriptor<Rank>`; Rank is provided by the enclosing class template.

```cpp
constexpr unsigned int extent(unsigned int dimension) const noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rank` | The tensor rank (number of dimensions) of the descriptor, a compile-time unsigned integer from 1 to 5. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `dimension` | Input | The dimension index to query, counted from 0 (the innermost dimension is Rank-1); when it is less than Rank, the number of valid elements of that dimension is returned, and an out-of-range index returns 0. |

## Return Value

| Return type | Description |
| --- | --- |
| `unsigned int` | Returns the valid tensor extent of the specified dimension. |

## Constraints

- Can be called in Host, AI Core SIMD programming, and AI Core SIMT programming; this operation processes the descriptor synchronously and does not start any data transfer.
- When `dimension < Rank`, the number of valid elements of that dimension is returned; an out-of-range index returns `0`.
- It only reads the stored values and does not check whether the descriptor satisfies the transfer conditions; unset fields are `0`.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/tensor_copy>

bool example()
{
    const unsigned extents[2] = {2, 3};
    const unsigned strides[2] = {3, 1};
    const unsigned padding[2] = {0, 0};
    const auto descriptor = asc::make_tensor_copy_descriptor(extents, strides, strides, padding, padding);
    return descriptor.extent(0) == 2 && descriptor.extent(1) == 3;
}
```

## Related APIs

- [API list for this header](asc_tensor_copy.md)
