# asc::pipeline_ref::`operator=`

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

`asc::pipeline_ref::operator=` copies the pipeline-stage event configuration stored in another reference.

## Function Prototype

Member of: [`asc::pipeline_ref`](pipeline_ref.md).

```cpp
// Excerpt of the declaration inside class asc::pipeline_ref; template parameters and other members are provided by the enclosing class.
asc::pipeline_ref& operator=(const asc::pipeline_ref&) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `Parameter 1` | Input | Pipeline reference that manages the current asynchronous transfer stage; it must remain valid until the wait completes. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::pipeline_ref&` | Returns a reference to the updated current object, which can continue to be used for assignment or compound operations. |

## Constraints

- Can only be called in AI Core SIMD programming.
- Parameter types, address spaces, value ranges, and object lifetimes must satisfy the declarations on this page.

## Example

The following AI Core SIMD snippet demonstrates stage operations; event IDs and the call order must satisfy the constraints on this page.

```cpp
#include <asc/pipeline>

__aicore__ void example(asc::pipeline_ref& target, const asc::pipeline_ref& source)
{
    target = source;
}
```

## Related APIs

- [`asc::pipeline_ref`](pipeline_ref.md)
- [API list for this header](asc_pipeline.md)
