# asc::elapsed_time

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

Header: `<asc/stream>`.

`asc::elapsed_time` queries the Runtime time interval between two recorded events and, on success, writes it to the output parameter in milliseconds.

This interface is available on the Host.

## Function Prototype

```cpp
namespace asc {
bool elapsed_time(asc::event_ref start, asc::event_ref end, float& milliseconds) noexcept;
}  // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `start` | Input | Event reference used to record or wait for execution progress. |
| `end` | Input | Event reference used to record or wait for execution progress. |
| `milliseconds` | Output | Receives the elapsed time between the two events, in milliseconds. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- If `start` or `end` is empty (an event reference not holding a handle), this interface refuses to execute, returns `false` directly, and does not modify `milliseconds`.
- milliseconds remains unchanged on failure.

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/stream>

decltype(auto) example(asc::event_ref start, asc::event_ref end, float& milliseconds)
{
    return asc::elapsed_time(start, end, milliseconds);
}
```

The corresponding complete project uses `C++17`; compile and run it on the target toolchain and device.

Complete example source: [stream_event.cpp](../../../../../zh/examples/stream_event.cpp).

## Related APIs

- [API list for this header](asc_stream.md)
