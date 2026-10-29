# asc::tensor_store_async

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

`asc::tensor_store_async` asynchronously stores a multidimensional tensor from UB to GM according to the descriptor, and is the UB→GM direction mirror of `asc::tensor_load_async`.

The descriptor is reused in a round-trip manner: `source_stride` still describes the GM layout, and `destination_stride` describes the padded UB layout written by load; store reads the valid data row by row, skipping over the left padding, and the padding areas are skipped rather than transferred. No padding exists on the GM side, so this interface has no fill value parameter.

After the checks pass, it first issues consumer_release, waits for the corresponding S→MTE3 event, and then performs the UB→GM store; this matches the plain pipeline order of consumer_release followed by copy_async. Before the call, all scalar reads and writes on the buffer of that stage must be completed.

## Function Prototype

```cpp
template <class T, unsigned Rank>
asc::tensor_copy_status asc::tensor_store_async(const asc::pipeline_ref& pipeline, unsigned int stage,
    asc::gm_span<T> destination, asc::ub_span<const T> source,
    const asc::tensor_copy_descriptor<Rank>& descriptor) noexcept;
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the transfer; only int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, or float is supported, and the element types of the two views must match. |
| `Rank` | A type or compile-time value representing the element count, dimension, bit width, or index, as determined by the declaration. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pipeline` | Input | The pipeline reference managing the current asynchronous transfer stage; it must remain valid until completion is waited on. |
| `stage` | Input | The pipeline stage number; it must be less than pipeline.stages(). |
| `destination` | Output | The GM destination storage that receives the results. Its storage must remain valid until the asynchronous operation completes. |
| `source` | Input | The UB storage view where the source data is located. Its storage must remain valid until the asynchronous operation completes. |
| `descriptor` | Input | The object describing the tensor shape, strides, and transfer direction; it must pass validation before submission. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::tensor_copy_status` | Returns the submission status of the asynchronous store task; a successful submission does not mean the transfer has completed. |

## Constraints

- Can be called only in AI Core SIMD programming
- Before submission it validates, in order, descriptor validity, the stage range (out of range returns `invalid_stage`), the transferred byte length of the innermost dimension, and the required element counts at both ends (overflow returns `size_overflow`; insufficient views return `insufficient_destination`/`insufficient_source` respectively)
- Alignment of both endpoint addresses of the aligned transfer path is a caller precondition, consistent with the load-direction description in `asc::tensor_copy_required_alignment`
- All scalar reads from the UB buffer of that pipeline stage must be completed before the call (the interface embeds consumer_release and its S→MTE3 wait)
- Parameter types, address spaces, value ranges, and object lifetimes must satisfy the declarations on this page

## Example

The following device-side function snippet shows an asynchronous store from UB to GM; the pipeline stage and the source and destination storage must remain valid until completion, and all scalar reads and writes on the buffer of that stage must be completed before the call.

```cpp
#include <asc/tensor_copy>

// Endpoints contain 16 integers and each row starts on a 32-byte boundary.
// The caller owns a valid stage zero and the matching pipeline event protocol.
__aicore__ asc::tensor_copy_status example(const asc::pipeline_ref& pipeline,
    __gm__ int* destination, __ubuf__ const int* source)
{
    const unsigned int extents[2] = {2, 8};
    const unsigned int strides[2] = {8, 1};
    const unsigned int padding[2] = {0, 0};
    const auto descriptor = asc::make_tensor_copy_descriptor(extents, strides, strides, padding, padding);
    return asc::tensor_store_async<int, 2>(pipeline, 0, asc::gm_span<int>(destination, 16),
        asc::ub_span<const int>(source, 16), descriptor);
}
```

## Related APIs

- [API list for this header](asc_tensor_copy.md)
