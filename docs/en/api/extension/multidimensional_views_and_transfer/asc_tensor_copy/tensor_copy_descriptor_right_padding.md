# asc::tensor_copy_descriptor::right_padding

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

`asc::tensor_copy_descriptor::right_padding` returns the number of right padding elements of the specified dimension.

## Function Prototype

The following is an in-class declaration of `asc::tensor_copy_descriptor<Rank>`; Rank is provided by the enclosing class template.

```cpp
constexpr unsigned int right_padding(unsigned int dimension) const noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rank` | The tensor rank (number of dimensions) of the descriptor, a compile-time unsigned integer from 1 to 5. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `dimension` | Input | The dimension index to query, counted from 0 (the innermost dimension is Rank-1); when it is less than Rank, the number of right padding elements of that dimension on the destination side is returned, and an out-of-range index returns 0. |

## Return Value

| Return type | Description |
| --- | --- |
| `unsigned int` | Returns the number of right padding elements of the specified dimension. |

## Constraints

- Can be called in Host, AI Core SIMD programming, and AI Core SIMT programming; this operation processes the descriptor synchronously and does not start any data transfer.
- When `dimension < Rank`, the number of right padding elements of that dimension on the destination side is returned; an out-of-range index returns `0`.
- It only reads the stored values and does not check whether the descriptor satisfies the transfer conditions; unset fields are `0`.

## Example

The following Host snippet demonstrates the call with a two-dimensional descriptor; the caller must ensure the dimension and the descriptor are valid.

```cpp
#include <asc/tensor_copy>

bool example()
{
    const unsigned int extents[2] = {2, 2};
    const unsigned int strides[2] = {2, 1};
    const unsigned int padding[2] = {0, 0};
    auto descriptor = asc::make_tensor_copy_descriptor(extents, strides, strides, padding, padding);
    return descriptor.right_padding(0) == 0;
}
```

## Related APIs

- [API list for this header](asc_tensor_copy.md)
