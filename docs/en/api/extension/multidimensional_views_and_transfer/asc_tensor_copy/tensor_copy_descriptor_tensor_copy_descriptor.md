# asc::tensor_copy_descriptor::tensor_copy_descriptor

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

`asc::tensor_copy_descriptor::tensor_copy_descriptor` default-constructs an `asc::tensor_copy_descriptor` object, initializing the values describing each dimension to zero.

## Function Prototype

The following is an in-class declaration of `asc::tensor_copy_descriptor<Rank>`; Rank is provided by the enclosing class template.

```cpp
constexpr tensor_copy_descriptor() noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rank` | The tensor rank (number of dimensions) of the descriptor, a compile-time unsigned integer from 1 to 5. |

## Return Value

No return value.

## Constraints

- `Rank` must be a compile-time unsigned integer from 1 to 5; dimensions are numbered from outermost to innermost, with the innermost dimension being `Rank - 1`.
- Default construction initializes the valid lengths, source/destination strides, and both-side paddings of all dimensions to zero; in this state [validate](tensor_copy_descriptor_validate.md) returns `zero_extent`.
- Can be constructed in Host, AI Core SIMD programming, and AI Core SIMT programming; construction does not start any data transfer.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/tensor_copy>

bool example()
{
    asc::tensor_copy_descriptor<2> descriptor;
    return descriptor.rank() == 2;
}
```

## Related APIs

- [API list for this header](asc_tensor_copy.md)
