# asc::tensor_copy_descriptor::required_alignment

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

`asc::tensor_copy_descriptor::required_alignment` returns the padded row length of the descriptor's innermost dimension, in elements.

## Function Prototype

The following is an in-class declaration of `asc::tensor_copy_descriptor<Rank>`; Rank is provided by the enclosing class template.

```cpp
constexpr unsigned int required_alignment() const noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rank` | The tensor rank (number of dimensions) of the descriptor, a compile-time unsigned integer from 1 to 5. |

## Return Value

| Return type | Description |
| --- | --- |
| `unsigned int` | Returns the padded row length of the descriptor's innermost dimension, in elements. |

## Constraints

- Can be called in Host, AI Core SIMD programming, and AI Core SIMT programming; this operation processes the descriptor synchronously and does not start any data transfer.
- Returns the element count of the innermost dimension `extent + left_padding + right_padding`, computed as a 32-bit unsigned integer; values beyond the range of that type wrap around.
- This result describes the padded row length on the destination side, in elements; see [tensor_copy_required_alignment](tensor_copy_required_alignment.md) for the byte conversion based on the element type.
- This query does not check the descriptor or the actual addresses; the 32-byte address boundary requirements at both ends of the transfer and this row length are checked separately.

## Example

The following Host snippet demonstrates the call with a two-dimensional descriptor.

```cpp
#include <asc/tensor_copy>

decltype(auto) example(const asc::tensor_copy_descriptor<2>& descriptor)
{
    auto value = descriptor.required_alignment();
    return value;
}
```

## Related APIs

- [API list for this header](asc_tensor_copy.md)
