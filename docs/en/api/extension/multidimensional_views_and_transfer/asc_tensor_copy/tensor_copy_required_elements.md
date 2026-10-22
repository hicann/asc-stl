# asc::tensor_copy_required_elements

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

`asc::tensor_copy_required_elements` computes the product of the padded lengths of all dimensions of the descriptor, not counting stride gaps.

## Function Prototype

```cpp
namespace asc {
template <unsigned Rank>
[[nodiscard]] constexpr unsigned long long tensor_copy_required_elements(
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
| `descriptor` | Input | The object describing the tensor shape, strides, and transfer direction; it must pass validation before submission. |

## Return Value

| Return type | Description |
| --- | --- |
| `unsigned long long` | Returns the product of the padded lengths of all dimensions; if any padded length is zero or the product overflows, 0 is returned. |

## Constraints

- Can be called in Host, AI Core SIMD programming, and AI Core SIMT programming; this operation processes the descriptor synchronously and does not start any data transfer.
- `Rank` must be a compile-time unsigned integer from 1 to 5; dimensions are numbered from outermost to innermost, with the innermost dimension being `Rank - 1`.
- `descriptor` must be valid during the call; the result of its [required_elements](tensor_copy_descriptor_required_elements.md) member is returned.
- Returns the product of `extent + left_padding + right_padding` over all dimensions; if any padded length is zero or the product exceeds the range of `unsigned long long`, `0` is returned.
- This query does not count storage gaps caused by strides, and it does not check zero strides, padding limits, or the actual source/destination capacity; see [validate](tensor_copy_descriptor_validate.md) for the parameter checks needed before a call.
- The view capacity of an actual transfer is checked against the stride span in each direction; this product must not be treated as the storage span of an arbitrary strided layout.

## Example

The following snippet shows the query or validation with a two-dimensional unpadded descriptor; the actual storage must satisfy the descriptor extents.

```cpp
#include <asc/tensor_copy>

decltype(auto) example()
{
    unsigned int extents[2] = {2, 2};
    unsigned int strides[2] = {2, 1};
    unsigned int padding[2] = {0, 0};
    auto descriptor = asc::make_tensor_copy_descriptor(extents, strides, strides, padding, padding);
    return asc::tensor_copy_required_elements(descriptor);
}
```

## Related APIs

- [API list for this header](asc_tensor_copy.md)
