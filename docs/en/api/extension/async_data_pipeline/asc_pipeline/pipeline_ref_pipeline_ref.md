# asc::pipeline_ref::pipeline_ref

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

Header: `<asc/pipeline>`.

`asc::pipeline_ref::pipeline_ref` initializes an `asc::pipeline_ref` object with the arguments provided by the caller.

## Function Prototype

Member of: [`asc::pipeline_ref`](pipeline_ref.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside class asc::pipeline_ref; template parameters and other members are provided by the enclosing class.
pipeline_ref(asc::pipeline_event_id load_event0, asc::pipeline_event_id store_event0,
    asc::pipeline_event_id load_event1, asc::pipeline_event_id store_event1) noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside class asc::pipeline_ref; template parameters and other members are provided by the enclosing class.
pipeline_ref(const asc::pipeline_ref&) noexcept;
```

### Prototype 3

```cpp
// Excerpt of the declaration inside class asc::pipeline_ref; template parameters and other members are provided by the enclosing class.
explicit pipeline_ref(asc::pipeline_event_id load_event, asc::pipeline_event_id store_event) noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `load_event0` | Input | Load event ID (pipeline_event_id) of stage 0 of the two-stage pipeline: the number of the MTE2 GM→UB transfer-in completion event; provided by the caller and held exclusively for the lifetime of the pipeline. |
| `store_event0` | Input | Store event ID (pipeline_event_id) of stage 0 of the two-stage pipeline: the number of the S→MTE3 transfer-out permission event; provided by the caller and held exclusively for the lifetime of the pipeline. |
| `load_event1` | Input | Load event ID (pipeline_event_id) of stage 1 of the two-stage pipeline: the number of the MTE2 GM→UB transfer-in completion event; provided by the caller and held exclusively for the lifetime of the pipeline. |
| `store_event1` | Input | Store event ID (pipeline_event_id) of stage 1 of the two-stage pipeline: the number of the S→MTE3 transfer-out permission event; provided by the caller and held exclusively for the lifetime of the pipeline. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `Parameter 1` | Input | The other `pipeline_ref` to copy from: the copy constructor copies its stages and borrowed event-ID state; the two objects share the same set of events. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `load_event` | Input | Load event ID (pipeline_event_id) of the single-stage pipeline: the number of the MTE2 GM→UB transfer-in completion event; provided by the caller and held exclusively for the lifetime of the pipeline. |
| `store_event` | Input | Store event ID (pipeline_event_id) of the single-stage pipeline: the number of the S→MTE3 transfer-out permission event; provided by the caller and held exclusively for the lifetime of the pipeline. |

## Return Value

No return value.

## Constraints

- Event numbers must be within `[0, 3]` and held exclusively by the caller for the entire lifetime of the pipeline; the two-stage form uses four distinct numbers.
- Besides the per-stage MTE2→S load event and the S→MTE3 store permission event, the coordinator also uses an MTE3→S drain event and an S→MTE2 reuse event. The single-stage form selects them from the remaining numbers; the two-stage form, which exhausts the numbers, reuses load_event0 and load_event1 respectively, but in different directions. The same direction and number must not be occupied by another TPipe/TQue.

- Can only be called in AI Core SIMD programming.
- Parameter types, address spaces, value ranges, and object lifetimes must satisfy the declarations on this page.

## Example

Launched on 1 AI Core. input and output are GM buffers of at least 1024 bytes, 32-byte aligned; when the i-th input element is i, the i-th output element should be i+1 after completion.

```cpp
#include <asc/pipeline>

__global__ __vector__ void example(__gm__ unsigned int* output, __gm__ const unsigned int* input)
{
    __ubuf__ unsigned int buffer[256];
    // Events 2 and 3 are held exclusively by this kernel function and must not be handed to another TPipe or TQue at the same time.
    const asc::pipeline_event_id load_event = 2;
    const asc::pipeline_event_id store_event = 3;
    asc::pipeline_ref pipeline(load_event, store_event);
    pipeline.producer_acquire(0);
    asc::copy_async(pipeline, 0, asc::ub_span<unsigned int>(buffer, 256), asc::gm_span<const unsigned int>(input, 256));
    pipeline.producer_commit(0);
    pipeline.consumer_wait(0);
    for (unsigned int index = 0; index < 256; ++index)
        buffer[index] += pipeline.stages();
    pipeline.consumer_release(0);
    asc::copy_async(
        pipeline, 0, asc::gm_span<unsigned int>(output, 256), asc::ub_span<const unsigned int>(buffer, 256));
    pipeline.wait();
}
```

For the complete project and run steps, see the [pipeline_copy example](../../../../../../examples/extension/pipeline_copy/README_en.md).

## Related APIs

- [`asc::pipeline_ref`](pipeline_ref.md)
- [API list for this header](asc_pipeline.md)
