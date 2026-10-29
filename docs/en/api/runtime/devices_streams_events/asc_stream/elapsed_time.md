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

This complete example uses the real CANN Runtime and selects device 0, which must be available before running. Asynchronous waits are limited to 10 seconds. Failure terminates the example process to avoid releasing resources still in use; the controller must stop subsequent tasks and recheck device health. On success, work completes before resources are closed, the device is reset, and the Runtime is finalized.

```cpp
#include <acl/acl.h>
#include <asc/stream>
#include <cstdlib>

void check(bool condition)
{
    if (!condition) {
        std::_Exit(2);
    }
}

void finish(asc::stream_ref stream)
{
    check(aclrtSynchronizeStreamWithTimeout(stream.native_handle(), 10000) == ACL_SUCCESS);
}
#include <cmath>


void run_example()
{
    asc::stream stream;
    asc::event start;
    asc::event stop;
    check(asc::make_stream(stream));
    check(asc::make_event(start) && asc::make_event(stop));
    check(start.record(stream) && stop.record(stream));
    finish(stream);
    float milliseconds = -1.0F;
    check(asc::elapsed_time(start, stop, milliseconds));
    check(std::isfinite(milliseconds) && milliseconds >= 0.0F);
    check(start.close() && stop.close() && stream.close());
}

int main()
{
    if (aclInit(nullptr) != ACL_SUCCESS) {
        return 1;
    }
    if (!asc::set_current_device(asc::device_ref(0))) {
        check(aclFinalize() == ACL_SUCCESS);
        return 1;
    }
    run_example();
    const bool reset = aclrtResetDevice(0) == ACL_SUCCESS;
    const bool finalized = aclFinalize() == ACL_SUCCESS;
    return reset && finalized ? 0 : 1;
}
```

## Related APIs

- [API list for this header](asc_stream.md)
