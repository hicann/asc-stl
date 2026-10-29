# asc::set_current_device

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

Header: `<asc/devices>`.

`asc::set_current_device` asks the Runtime to set the specified `device_ref` as the device used by the current thread, and reports success with a boolean value.

## Function Prototype

```cpp
namespace asc {
bool set_current_device(asc::device_ref device) noexcept;
} // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `device` | Input | Target device_ref: asks the Runtime to set its ordinal as the device of the current thread; returns true on success. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- Devices can only be queried or selected on the Host.
- A reference stores only the device ordinal and does not own Runtime state.
- On a failed query, the output parameter keeps its original value; the properties are limited to the AI Core, Vector Core, Warp, UB, GM, L2, and architecture fields listed by the current interface.

## Example

This complete example uses the real CANN Runtime and selects device 0, which must be available before running. Asynchronous waits are limited to 10 seconds. Failure terminates the example process to avoid releasing resources still in use; the controller must stop subsequent tasks and recheck device health. On success, work completes before resources are closed, the device is reset, and the Runtime is finalized. Every successful device selection increments the Runtime reference count; the two additional selections below each have a matching reset, and main releases its initial selection.

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
#include <asc/devices>


void run_example()
{
    asc::device_ref previous(99);
    check(asc::current_device(previous));
    check(asc::set_current_device(asc::device_ref(0)));
    asc::device_ref selected(99);
    check(asc::current_device(selected) && selected == asc::device_ref(0));
    check(asc::set_current_device(previous));
    // Balance the two additional selections; main balances its initial selection.
    check(aclrtResetDevice(static_cast<int>(previous.ordinal())) == ACL_SUCCESS);
    check(aclrtResetDevice(0) == ACL_SUCCESS);
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

- [API list for this header](asc_devices.md)
