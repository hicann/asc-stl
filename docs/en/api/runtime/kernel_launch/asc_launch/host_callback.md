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
#include <asc/launch>
#include <atomic>

void set_result(void* data)
{
    static_cast<std::atomic<int>*>(data)->store(7, std::memory_order_release);
}

void run_example()
{
    asc::stream stream;
    check(asc::make_stream(stream));
    std::atomic<int> result{0};
    check(asc::host_callback(stream, set_result, &result).success());
    finish(stream);
    check(result.load(std::memory_order_acquire) == 7);
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

- [`asc::execution_status`](../../execution_policies_and_status/asc_execution/execution_status.md): Argument validation and task submission status; a successful submission does not mean the asynchronous work has completed.
