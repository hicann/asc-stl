# asc::tensor_copy_status::invalid_stage

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

`asc::tensor_copy_status::invalid_stage` indicates that the specified pipeline stage does not exist.

## Declaration

Member of: [`asc::tensor_copy_status`](tensor_copy_status.md).

```cpp
// Excerpt of the declaration inside asc::tensor_copy_status; template parameters and other members are provided by the enclosing class.
invalid_stage = 6;
```

## Constraints

- This is an enumerator of [tensor_copy_status](tensor_copy_status.md); it can be stored and compared in Host, AI Core SIMD programming, and AI Core SIMT programming, and reading the constant performs no validation or transfer.
- Indicates that `stage >= pipeline.stages()` was passed to a transfer interface; a valid pipeline stage must be selected before submission.
- This status is produced by the transfer interfaces; standalone descriptor validation does not read the pipeline state.

## Example

The following snippet shows the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/tensor_copy>

auto value = asc::tensor_copy_status::invalid_stage;
```

## Related APIs

- [`asc::tensor_copy_status`](tensor_copy_status.md)
- [API list for this header](asc_tensor_copy.md)
