# asc::stream_ref::wait

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

`asc::stream_ref::wait` submits a wait for the specified event to this Stream, so that subsequent tasks execute after the event is done.

## Function Prototype

Member of: [`asc::stream_ref`](stream_ref.md).

```cpp
// Excerpt of the declaration inside asc::stream_ref; template parameters and other members are provided by the owning class.
bool wait(asc::event_ref event) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `event` | Input | Event reference used to record or wait for execution progress. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- Provides a nullable non-owning Host reference.
- The native handle is an opaque void pointer.
- Query results and output parameters are updated only when the CANN Runtime call succeeds.

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
#include <asc/algorithm>
#include <asc/buffer>


void run_example()
{
    asc::stream producer;
    asc::stream consumer;
    asc::event ready;
    check(asc::make_stream(producer) && asc::make_stream(consumer));
    check(asc::make_event(ready));
    asc::device_memory_resource device_resource(0);
    asc::pinned_memory_resource host_resource;
    asc::device_buffer<unsigned char> device;
    asc::pinned_buffer<unsigned char> output;
    check(asc::make_device_buffer(device, asc::device_memory_resource_ref(device_resource), producer, 4).success());
    check(asc::make_pinned_buffer(output, asc::pinned_memory_resource_ref(host_resource), consumer, 4).success());
    check(asc::fill_bytes(producer, device.data(), 0x2A, 4).success());
    check(ready.record(producer));
    check(asc::stream_ref(consumer.native_handle()).wait(ready));
    check(asc::copy_bytes(consumer, output.data(), device.data(), 4).success());
    finish(consumer);
    finish(producer);
    for (int i = 0; i < 4; ++i) {
        check(output.data()[i] == 0x2A);
    }
    check(output.close().success() && device.close().success());
    check(ready.close() && consumer.close() && producer.close());
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

- [`asc::stream_ref`](stream_ref.md)
- [API list for this header](asc_stream.md)
