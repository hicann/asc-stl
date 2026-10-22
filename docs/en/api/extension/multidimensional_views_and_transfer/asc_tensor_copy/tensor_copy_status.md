# asc::tensor_copy_status

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

`asc::tensor_copy_status` defines the validation and execution statuses of a tensor copy.

## Declaration

```cpp
namespace asc {
enum class tensor_copy_status : int;
} // namespace asc
```

## Constraints

- This enum and its constants can be stored and compared in Host, AI Core SIMD programming, and AI Core SIMT programming; reading a status value itself performs no validation or transfer.
- The status must be interpreted according to the interface that returned it: descriptor validation covers only value conditions, asynchronous transfers also involve view capacity, addresses, and pipeline stages, and `success` does not mean the asynchronous data is already readable.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/tensor_copy>

bool example()
{
    const asc::tensor_copy_status status = asc::tensor_copy_status::insufficient_destination;
    return status != asc::tensor_copy_status::success;
}
```

## Related APIs

- [API list for this header](asc_tensor_copy.md)
