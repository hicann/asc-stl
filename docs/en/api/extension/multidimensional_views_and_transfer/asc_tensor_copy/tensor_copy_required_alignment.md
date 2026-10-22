# asc::tensor_copy_required_alignment

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

`asc::tensor_copy_required_alignment` converts the padded row length of the descriptor's innermost dimension into a byte count based on the specified element type.

## Function Prototype

```cpp
namespace asc {
template <class T, unsigned Rank>
[[nodiscard]] constexpr unsigned int tensor_copy_required_alignment(
    const asc::tensor_copy_descriptor<Rank>& descriptor) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type participating in the tensor transfer; it determines the element size and the transfer alignment requirements. |
| `Rank` | The tensor rank (number of dimensions) of the descriptor, a compile-time unsigned integer from 1 to 5. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `descriptor` | Input | The object describing the tensor shape, strides, and transfer direction; it must pass validation before submission. |

## Return Value

| Return type | Description |
| --- | --- |
| `unsigned int` | Returns the byte count of the padded row length of the innermost dimension; if the conversion product exceeds the range of the return type, 0 is returned. |

## Constraints

- Can be called in Host, AI Core SIMD programming, and AI Core SIMT programming; this operation processes the descriptor synchronously and does not start any data transfer.
- `Rank` must be a compile-time unsigned integer from 1 to 5; dimensions are numbered from outermost to innermost, with the innermost dimension being `Rank - 1`.
- `T` must be a complete type to which `sizeof(T)` can be applied; `descriptor` must be valid during the call.
- Returns the byte count of the [required_alignment](tensor_copy_descriptor_required_alignment.md) member result multiplied by `sizeof(T)`; if the product exceeds the range of `unsigned int`, `0` is returned.
- This query does not validate the descriptor or the actual endpoint addresses; the 32-byte boundary requirements at both ends of the transfer cannot be replaced by this return value.

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
    return asc::tensor_copy_required_alignment<int>(descriptor);
}
```

## Related APIs

- [API list for this header](asc_tensor_copy.md)
