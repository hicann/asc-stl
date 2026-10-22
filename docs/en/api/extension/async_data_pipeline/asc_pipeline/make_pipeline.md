# asc::make_pipeline

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

`asc::make_pipeline` creates a pipeline_ref from one or two sets of Load/Store events.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
asc::pipeline_ref make_pipeline(asc::pipeline_event_id load_event, asc::pipeline_event_id store_event) noexcept;
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
asc::pipeline_ref make_pipeline(asc::pipeline_event_id load_event0, asc::pipeline_event_id store_event0,
    asc::pipeline_event_id load_event1, asc::pipeline_event_id store_event1) noexcept;
}  // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `load_event` | Input | Load event ID (pipeline_event_id) of the single-stage pipeline: the number of the MTE2 GM→UB transfer-in completion event; provided by the caller and held exclusively for the lifetime of the pipeline. |
| `store_event` | Input | Store event ID (pipeline_event_id) of the single-stage pipeline: the number of the S→MTE3 transfer-out permission event; provided by the caller and held exclusively for the lifetime of the pipeline. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `load_event0` | Input | Load event ID (pipeline_event_id) of stage 0 of the two-stage pipeline: the number of the MTE2 GM→UB transfer-in completion event; different from the other stage and held exclusively for the lifetime of the pipeline. |
| `store_event0` | Input | Store event ID (pipeline_event_id) of stage 0 of the two-stage pipeline: the number of the S→MTE3 transfer-out permission event; different from the other stage and held exclusively for the lifetime of the pipeline. |
| `load_event1` | Input | Load event ID (pipeline_event_id) of stage 1 of the two-stage pipeline: the number of the MTE2 GM→UB transfer-in completion event; different from the other stage and held exclusively for the lifetime of the pipeline. |
| `store_event1` | Input | Store event ID (pipeline_event_id) of stage 1 of the two-stage pipeline: the number of the S→MTE3 transfer-out permission event; different from the other stage and held exclusively for the lifetime of the pipeline. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::pipeline_ref` | Returns a non-owning pipeline reference bound to the events provided by the caller. |
| Prototype 2 | `asc::pipeline_ref` | Returns a non-owning pipeline reference bound to the events provided by the caller. |

## Constraints

- Event numbers must be within `[0, 3]` and held exclusively by the caller for the entire lifetime of the pipeline; the two-stage form uses four distinct numbers.
- Besides the per-stage MTE2→S load event and the S→MTE3 store permission event, the coordinator also uses an MTE3→S drain event and an S→MTE2 reuse event. The single-stage form selects them from the remaining numbers; the two-stage form, which exhausts the numbers, reuses load_event0 and load_event1 respectively, but in different directions. The same direction and number must not be occupied by another TPipe/TQue.

- Can only be called in AI Core SIMD programming.
- Parameter types, address spaces, value ranges, and object lifetimes must satisfy the declarations on this page.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/pipeline>

__aicore__ decltype(auto) example(asc::pipeline_event_id load_event, asc::pipeline_event_id store_event)
{
    return asc::make_pipeline(load_event, store_event);
}
```

## Related APIs

- [API list for this header](asc_pipeline.md)
