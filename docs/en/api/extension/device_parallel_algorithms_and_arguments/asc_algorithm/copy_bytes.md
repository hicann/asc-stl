# asc::copy_bytes

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

Header: `<asc/algorithm>`.

`asc::copy_bytes` copies a block of device-accessible memory to the destination address byte by byte, which is suitable for scenarios where the element type is unknown or the number of bytes must be controlled explicitly.

## Function Prototype

```cpp
namespace asc {
asc::execution_status copy_bytes(asc::stream_ref stream, void* destination, const void* source, asc::std::size_t bytes) noexcept;
} // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `stream` | Input | Stream used to submit asynchronous work in order. The related resources must remain valid until the work completes. |
| `destination` | Output | Destination storage that receives the result. Its storage must remain valid until the asynchronous operation completes. |
| `source` | Input | Source data or source object. Its storage must remain valid until the asynchronous operation completes. |
| `bytes` | Input | Amount of data to process, in bytes. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::execution_status` | Returns the parameter validation or task submission status; a successful submission does not mean the asynchronous work has completed. |

## Constraints

- Can be called on the Host only.
- The stream must be valid.
- The source and destination must be accessible by the device in the specified direction, must not overlap, and must remain valid until the asynchronous copy completes.

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
    asc::stream stream;
    check(asc::make_stream(stream));
    asc::device_memory_resource device_resource(0);
    asc::pinned_memory_resource host_resource;
    const asc::device_memory_resource_ref device_ref(device_resource);
    const asc::pinned_memory_resource_ref host_ref(host_resource);
    asc::device_buffer<unsigned char> device;
    asc::pinned_buffer<unsigned char> input;
    asc::pinned_buffer<unsigned char> output;
    check(asc::make_device_buffer(device, device_ref, stream, 4).success());
    check(asc::make_pinned_buffer(input, host_ref, stream, 4).success());
    check(asc::make_pinned_buffer(output, host_ref, stream, 4).success());
    const unsigned char expected[4] = {2, 4, 6, 8};
    for (int i = 0; i < 4; ++i) {
        input.data()[i] = expected[i];
    }
    check(asc::copy_bytes(stream, device.data(), input.data(), 4).success());
    check(asc::copy_bytes(stream, output.data(), device.data(), 4).success());
    finish(stream);
    for (int i = 0; i < 4; ++i) {
        check(output.data()[i] == expected[i]);
    }
    check(output.close().success() && input.close().success() && device.close().success());
    check(stream.close());
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

- [`asc::execution_status`](../../../runtime/execution_policies_and_status/asc_execution/execution_status.md): Parameter validation and task submission status; a successful submission does not mean the asynchronous work has completed.
