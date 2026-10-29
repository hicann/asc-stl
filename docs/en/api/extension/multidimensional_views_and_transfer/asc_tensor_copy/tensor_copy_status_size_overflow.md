# asc::tensor_copy_status::size_overflow

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

`asc::tensor_copy_status::size_overflow` indicates that a tensor storage size computation exceeded the representable range, including total element count overflow, padding exceeding 255, and accumulated source/destination stride span overflow.

## Declaration

Member of: [`asc::tensor_copy_status`](tensor_copy_status.md).

```cpp
// Excerpt of the declaration inside asc::tensor_copy_status; template parameters and other members are provided by the enclosing class.
size_overflow = 3;
```

## Constraints

- This is an enumerator of [tensor_copy_status](tensor_copy_status.md); it can be stored and compared in Host, AI Core SIMD programming, and AI Core SIMT programming, and reading the constant performs no validation or transfer.
- Indicates that a size computation cannot satisfy the interface requirements, for example padding exceeding 255, or the total padded element count or a stride span overflowing; [tensor_store_async](tensor_store_async.md) additionally checks the transferred byte length of the innermost dimension.

## Example

The following snippet shows the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/tensor_copy>

bool example()
{
    using status = asc::tensor_copy_status;
    const status selected = status::size_overflow;
    const status all[] = {
        status::success,
        status::zero_extent,
        status::zero_stride,
        status::size_overflow,
        status::insufficient_source,
        status::insufficient_destination,
        status::invalid_stage
    };
    for (unsigned left = 0; left < 7; ++left) {
        for (unsigned right = left + 1; right < 7; ++right) {
            if (all[left] == all[right]) return false;
        }
    }
    const unsigned int extents[2] = {2, 2};
    const unsigned int strides[2] = {2, 1};
    const unsigned int padding[2] = {0, 0};
    auto descriptor = asc::make_tensor_copy_descriptor(extents, strides, strides, padding, padding);
    descriptor.set_dimension(0, 2, 2, 2, 256, 0);
    return descriptor.validate() == selected;
}
```

## Related APIs

- [`asc::tensor_copy_status`](tensor_copy_status.md)
- [API list for this header](asc_tensor_copy.md)
