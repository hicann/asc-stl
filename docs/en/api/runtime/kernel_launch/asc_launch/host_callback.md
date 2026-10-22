# asc::host_callback

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

Header: `<asc/launch>`.

`asc::host_callback` submits a Host callback in the task order of the specified Stream. It returns invalid argument when the Stream or the callback function is null, and retains the native status code when the underlying runtime fails.

## Function Prototype

```cpp
namespace asc {
asc::execution_status host_callback(asc::stream_ref stream, host_callback_t callback, void* data) noexcept;
} // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `stream` | Input | The Stream used to submit asynchronous work in order. The related resources must remain valid until the work completes. |
| `callback` | Input | The callback function pointer (host_callback_t = void(*)(void*)): executed on the Host when this Stream queue entry's turn comes; a null value returns invalid argument. |
| `data` | Input | The user data pointer passed through when the callback executes: its lifetime must extend until the callback has actually finished executing on the Stream. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::execution_status` | Returns the argument validation or task submission status; a successful submission does not mean the asynchronous work has completed. |

## Constraints

- Can only be called on the Host.
- The Stream and the callback function must be valid.
- The callback and the user data must remain valid until execution, and the callback must not throw exceptions across the C interface boundary.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/launch>

decltype(auto) example(asc::stream_ref stream, asc::host_callback_t callback, void* data)
{
    return asc::host_callback(stream, callback, data);
}
```

## Related APIs

- [`asc::execution_status`](../../execution_policies_and_status/asc_execution/execution_status.md): Argument validation and task submission status; a successful submission does not mean the asynchronous work has completed.
