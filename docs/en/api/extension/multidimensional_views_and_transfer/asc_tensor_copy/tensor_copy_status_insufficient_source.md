# asc::tensor_copy_status::insufficient_source

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

`asc::tensor_copy_status::insufficient_source` indicates that the source view is not large enough to cover the elements required by the descriptor; in the GM→UB load direction, this status is also returned when the source-side address does not satisfy the 32-byte alignment requirement of the transfer engine.

## Declaration

Member of: [`asc::tensor_copy_status`](tensor_copy_status.md).

```cpp
// Excerpt of the declaration inside asc::tensor_copy_status; template parameters and other members are provided by the enclosing class.
insufficient_source = 4;
```

## Constraints

- This is an enumerator of [tensor_copy_status](tensor_copy_status.md); it can be stored and compared in Host, AI Core SIMD programming, and AI Core SIMT programming, and reading the constant performs no validation or transfer.
- Indicates that the source element span required by the transfer exceeds the source view capacity.
- [tensor_load_async](tensor_load_async.md) also returns this value when the source-side address does not satisfy the 32-byte boundary; this status is not produced by standalone descriptor validation.

## Example

The following snippet shows the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/tensor_copy>

bool example()
{
    using status = asc::tensor_copy_status;
    const status selected = status::insufficient_source;
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
    // These transfer-only results are distinct status tags; no transfer runs on Host.
    return selected != status::success &&
        selected != status::zero_extent &&
        selected != status::zero_stride &&
        selected != status::size_overflow &&
        selected != status::insufficient_destination &&
        selected != status::invalid_stage;
}
```

## Related APIs

- [`asc::tensor_copy_status`](tensor_copy_status.md)
- [API list for this header](asc_tensor_copy.md)
