# asc::make_tensor_copy_descriptor

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

`asc::make_tensor_copy_descriptor` constructs a tensor copy descriptor from per-dimension extents, source/destination strides, and padding arrays.

## Function Prototype

```cpp
namespace asc {
template <unsigned Rank>
constexpr asc::tensor_copy_descriptor<Rank> [[nodiscard]] make_tensor_copy_descriptor(
    const unsigned int (&extents)[Rank], const unsigned int (&source_strides)[Rank],
    const unsigned int (&destination_strides)[Rank], const unsigned int (&left_padding)[Rank],
    const unsigned int (&right_padding)[Rank]) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rank` | The number of dimensions of the tensor, ranging from 1 to 5; each input array contains `Rank` elements. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `extents` | Input | The valid length of each dimension; the number of dimensions and the value ranges must satisfy the constraints on this page. |
| `source_strides` | Input | The stride of each dimension in the source layout, in elements; the values in the array are copied into the descriptor in this call. |
| `destination_strides` | Input | The stride of each dimension in the destination layout, in elements; the values in the array are copied into the descriptor in this call. |
| `left_padding` | Input | The number of padding elements on the front side of each dimension; 0 means no padding on that side. The array must be valid during this call. |
| `right_padding` | Input | The number of padding elements on the back side of each dimension; 0 means no padding on that side. The array must be valid during this call. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::tensor_copy_descriptor<Rank>` | Returns a tensor copy descriptor describing the source and destination shapes and strides. |

## Constraints

- `Rank` ranges from 1 to 5, and the innermost dimension has index `Rank - 1`.
- The five input arrays must be valid during the call; the function copies the array values and does not keep references to the arrays.
- This function synchronously constructs the descriptor; it does not submit any data transfer and does not automatically call `validate()`. Before an actual transfer, the descriptor and its data ranges must be checked against the requirements of the corresponding interface.
- The descriptor can be constructed in Host, AI Core SIMD programming, and AI Core SIMT programming.

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
