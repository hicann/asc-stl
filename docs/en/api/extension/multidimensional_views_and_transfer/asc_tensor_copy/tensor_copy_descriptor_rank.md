# asc::tensor_copy_descriptor::rank

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

`asc::tensor_copy_descriptor::rank` returns the compile-time number of dimensions of the tensor copy descriptor.

## Function Prototype

The following is an in-class declaration of `asc::tensor_copy_descriptor<Rank>`; Rank is provided by the enclosing class template.

```cpp
constexpr unsigned int rank() const noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Rank` | The tensor rank (number of dimensions) of the descriptor, a compile-time unsigned integer from 1 to 5. |

## Return Value

| Return type | Description |
| --- | --- |
| `unsigned int` | Returns the compile-time number of dimensions of the tensor copy descriptor. |

## Constraints

- Can be called in Host, AI Core SIMD programming, and AI Core SIMT programming; this operation processes the descriptor synchronously and does not start any data transfer.
- Returns the compile-time template parameter `Rank`, whose value ranges from 1 to 5; the descriptor is not required to have passed validation.

## Example

The following Host snippet demonstrates the call with a two-dimensional descriptor.

```cpp
#include <asc/tensor_copy>

decltype(auto) example(const asc::tensor_copy_descriptor<2>& descriptor)
{
    auto value = descriptor.rank();
    return value;
}
```

## Related APIs

- [API list for this header](asc_tensor_copy.md)
