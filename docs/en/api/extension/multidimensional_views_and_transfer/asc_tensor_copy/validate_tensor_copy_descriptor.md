# asc::validate_tensor_copy_descriptor

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

`asc::validate_tensor_copy_descriptor` checks whether the extents, strides, and size computations of a tensor copy descriptor are valid.

## Function Prototype

```cpp
namespace asc {
template <unsigned Rank>
[[nodiscard]] constexpr asc::tensor_copy_status validate_tensor_copy_descriptor(
    const asc::tensor_copy_descriptor<Rank>& descriptor) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rank` | The tensor rank (number of dimensions) of the descriptor, a compile-time unsigned integer from 1 to 5. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `descriptor` | Input | The descriptor to check; it must be valid during the call and may contain values that have not passed validation yet. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::tensor_copy_status` | Returns the value validation status of the descriptor; this call does not modify the descriptor and does not submit any transfer. |

## Constraints

- Can be called in Host, AI Core SIMD programming, and AI Core SIMT programming; this operation processes the descriptor synchronously and does not start any data transfer.
- `Rank` must be a compile-time unsigned integer from 1 to 5; dimensions are numbered from outermost to innermost, with the innermost dimension being `Rank - 1`.
- `descriptor` must be valid during the call; this function returns the validation result of its [validate](tensor_copy_descriptor_validate.md) member.
- It checks non-zero valid lengths and non-zero source/destination strides dimension by dimension; when a problem is found, it returns `zero_extent` or `zero_stride` respectively.
- When the padding on any side exceeds 255, the total number of padded elements overflows, or the accumulated source/destination stride spans overflow, it returns `size_overflow`; otherwise it returns `success`.
- Validation does not access the source/destination storage and does not check the actual view capacity, pipeline stages, or endpoint addresses; the transfer interfaces still perform their own checks.

## Example

The following snippet shows the query or validation with a two-dimensional unpadded descriptor; the actual storage must satisfy the descriptor extents.

```cpp
#include <asc/tensor_copy>

bool example()
{
    const unsigned int extents[2] = {2, 2};
    const unsigned int strides[2] = {2, 1};
    const unsigned int padding[2] = {0, 0};
    auto descriptor = asc::make_tensor_copy_descriptor(extents, strides, strides, padding, padding);
    return asc::validate_tensor_copy_descriptor(descriptor) == asc::tensor_copy_status::success;
}
```

## Related APIs

- [API list for this header](asc_tensor_copy.md)
