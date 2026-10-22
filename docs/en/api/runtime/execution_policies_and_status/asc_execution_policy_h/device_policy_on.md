# asc::device_policy::on

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

Header: `<asc/execution.policy.h>`.

`asc::device_policy::on` returns a new policy bound to the specified Stream, keeping the temporary storage and execution requirements of the original policy.

This interface is available on Host.

## Function Prototype

Member of: [`asc::device_policy`](device_policy.md).

```cpp
// Excerpt of the declaration inside asc::device_policy; template parameters and other members are provided by the enclosing class.
constexpr asc::device_policy on(asc::stream_ref stream) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `stream` | Input | The Stream used to submit asynchronous work in order. The related resources must remain valid until the work completes. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::device_policy` | Returns a new policy bound to the specified Stream, keeping the temporary storage and execution requirements of the original policy. |

## Constraints

- Only the execution requirement, Stream, or temporary storage binding named by the function is replaced; the other policy attributes remain unchanged.

## Example

The following Host snippet demonstrates the call with concrete objects; resource operations must follow the initialization and lifetime constraints on this page.

```cpp
#include <asc/execution.policy.h>

decltype(auto) example(asc::device_policy policy, asc::stream_ref stream)
{
    auto configured = policy.on(stream);
    return configured;
}
```

## Related APIs

- [`asc::device_policy`](device_policy.md): The device execution policy that specifies the Stream, temporary storage, and execution requirements.
