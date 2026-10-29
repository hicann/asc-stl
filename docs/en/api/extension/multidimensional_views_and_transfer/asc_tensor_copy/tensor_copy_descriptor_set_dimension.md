# asc::tensor_copy_descriptor::set_dimension

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

`asc::tensor_copy_descriptor::set_dimension` sets the extent, source/destination strides, and both-side paddings of the specified dimension.

## Function Prototype

The following is an in-class declaration of `asc::tensor_copy_descriptor<Rank>`; Rank is provided by the enclosing class template.

```cpp
constexpr void set_dimension(unsigned int dimension, unsigned int extent, unsigned int source_stride,
    unsigned int destination_stride, unsigned int left_padding, unsigned int right_padding) noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rank` | The tensor rank (number of dimensions) of the descriptor, a compile-time unsigned integer from 1 to 5. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `dimension` | Input | The dimension index to set, counted from 0 (the innermost dimension is Rank-1); when it is not less than Rank, this call does not modify any field of the descriptor. |
| `extent` | Input | The number of valid elements of this dimension participating in the transfer, in elements (uint32_t); it must be non-zero for the descriptor to pass validation. |
| `source_stride` | Input | The distance between adjacent elements of this dimension on the source side (GM), in elements (uint32_t); it must be non-zero for the descriptor to pass validation. |
| `destination_stride` | Input | The distance between adjacent elements of this dimension on the destination side (UB), in elements (uint32_t); it must be non-zero for the descriptor to pass validation. |
| `left_padding` | Input | The number of padding elements on the left side of this dimension on the destination side (uint32_t); written with fill_value during the transfer. |
| `right_padding` | Input | The number of padding elements on the right side of this dimension on the destination side (uint32_t); written with fill_value during the transfer. |

## Return Value

No return value.

## Constraints

- Can be called in Host, AI Core SIMD programming, and AI Core SIMT programming; this operation processes the descriptor synchronously and does not start any data transfer.
- `dimension` should be less than `Rank`; the current implementation writes no field for an out-of-range index.
- Setting only copies the given values and does not automatically run [validate](tensor_copy_descriptor_validate.md); before an actual transfer, the valid lengths and strides must be non-zero, the padding on each side must not exceed 255, and the size and span checks must pass.

## Example

The following Host snippet demonstrates setting one valid dimension on a two-dimensional descriptor.

```cpp
#include <asc/tensor_copy>

bool example()
{
    asc::tensor_copy_descriptor<2> descriptor;
    descriptor.set_dimension(0, 2, 2, 2, 0, 0);
    descriptor.set_dimension(1, 2, 1, 1, 0, 0);
    return descriptor.extent(0) == 2 && descriptor.extent(1) == 2 &&
        descriptor.source_stride(0) == 2 && descriptor.destination_stride(1) == 1 &&
        descriptor.left_padding(0) == 0 && descriptor.right_padding(1) == 0 &&
        descriptor.validate() == asc::tensor_copy_status::success;
}
```

## Related APIs

- [API list for this header](asc_tensor_copy.md)
