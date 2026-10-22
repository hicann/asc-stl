# asc::tensor_load_async

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

`asc::tensor_load_async` asynchronously loads a multidimensional tensor from GM to UB according to the descriptor and fill value.

## Function Prototype

```cpp
namespace asc {
template <class T, unsigned Rank>
asc::tensor_copy_status tensor_load_async(const asc::pipeline_ref& pipeline, unsigned int stage,
    asc::ub_span<T> destination, asc::gm_span<const T> source, const asc::tensor_copy_descriptor<Rank>& descriptor,
    T fill_value) noexcept;
}  // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The element type of the transfer; only int8_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, or float is supported, and the element types of the two views must match. |
| `Rank` | The tensor rank (number of dimensions) of the descriptor, a compile-time unsigned integer from 1 to 5. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `pipeline` | Input | The GM-UB pipeline reference that carries this asynchronous transfer (it holds no resources itself); it must remain valid until the transfer completes. |
| `stage` | Input | The pipeline stage index (from 0) to which this load is submitted; it must be less than the number of stages of the pipeline, otherwise invalid_stage is returned and no transfer is initiated. |
| `destination` | Output | The UB destination storage view (ub_span<T>) that receives the loaded data; its element capacity must be no less than the number of required elements computed from the destination strides and both-side paddings (otherwise insufficient_destination is returned), and the storage must remain valid until the transfer completes. |
| `source` | Input | The GM source storage view (gm_span<const T>) being loaded; its element capacity must be no less than the number of required elements computed from the source strides, excluding padding (otherwise insufficient_source is returned), and the storage must remain valid until the transfer completes. |
| `descriptor` | Input | The transfer descriptor describing the per-dimension extents, source/destination strides, and both-side paddings; it must pass its validate check (success), otherwise the corresponding failure status is returned directly and no transfer is initiated. |
| `fill_value` | Input | The element value written to the padding areas on both sides of the destination, of the same type as T. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::tensor_copy_status` | Returns the submission status of the asynchronous load task; a successful submission does not mean the transfer has completed. |

## Constraints

- Before reusing a pipeline stage, the caller must run producer_acquire(stage); after a successful submission, run consumer_wait(stage). A failure status must not continue to wait on a load event that was not submitted.
- After completing the computation of that stage, use tensor_store_async, or consumer_release and submit the store according to the plain pipeline protocol; finally wait for completion before observing results or releasing storage.

- Can be called only in AI Core SIMD programming.
- The source and destination addresses must fall on the transfer engine's 32-byte data block boundaries; if either end is unaligned, insufficient_source/insufficient_destination is returned respectively (this hardware boundary check is independent of the row pitch result of tensor_copy_required_alignment).
- Parameter types, address spaces, value ranges, and object lifetimes must satisfy the declarations on this page.

## Example

The following device-side function snippet shows an asynchronous load from GM to UB; the pipeline stage and the source and destination storage must remain valid until completion.

```cpp
#include <asc/tensor_copy>

__aicore__ decltype(auto) example(const asc::pipeline_ref& pipeline, asc::ub_span<int> destination,
    asc::gm_span<const int> source, const asc::tensor_copy_descriptor<2>& descriptor)
{
    return asc::tensor_load_async<int, 2>(pipeline, 0, destination, source, descriptor, 0);
}
```

## Related APIs

- [API list for this header](asc_tensor_copy.md)
