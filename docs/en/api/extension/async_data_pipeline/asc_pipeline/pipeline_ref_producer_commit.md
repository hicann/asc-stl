# asc::pipeline_ref::producer_commit

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

`asc::pipeline_ref::producer_commit` notifies that production on the specified pipeline stage has been committed and can be read by the consumer.

## Function Prototype

Member of: [`asc::pipeline_ref`](pipeline_ref.md).

```cpp
// Excerpt of the declaration inside class asc::pipeline_ref; template parameters and other members are provided by the enclosing class.
void producer_commit(unsigned int stage) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `stage` | Input | Pipeline stage number, starting from 0, and must be less than the number of pipeline stages (1 or 2) determined at construction; this call notifies the Load event of that stage, indicating that the data of that stage has been produced and can be read by the consumer. |

## Return Value

No return value.

## Constraints

- Can only be called in AI Core SIMD programming.
- Parameter types, address spaces, value ranges, and object lifetimes must satisfy the declarations on this page.

## Example

The following AI Core SIMD snippet demonstrates stage operations; event IDs and the call order must satisfy the constraints on this page.

```cpp
#include <asc/pipeline>

__aicore__ void example(const asc::pipeline_ref& pipeline, unsigned int stage)
{
    // stage must belong to the current pipeline; the caller is responsible for the complete stage pairing protocol.
    pipeline.producer_commit(stage);
}
```

## Related APIs

- [`asc::pipeline_ref`](pipeline_ref.md)
- [API list for this header](asc_pipeline.md)
