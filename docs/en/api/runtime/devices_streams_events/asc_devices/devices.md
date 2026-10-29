# asc::devices

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

`asc::devices` writes at most `capacity` device references, ordered by ordinal, into the caller's array, and returns the full device count reported by the Runtime through `count`.

## Function Prototype

```cpp
namespace asc {
bool devices(asc::device_ref* output, asc::std::uint32_t capacity, asc::std::uint32_t& count) noexcept;
}  // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Address of the caller's array that receives the device_ref values: min(capacity, total number of devices) references are written in increasing ordinal order; must not be null when capacity is non-zero. |
| `capacity` | Input | Number of device_ref values the array can hold: only limits the number actually written and does not affect the total reported by count. |
| `count` | Output | The total number of devices reported by the Runtime is written through this reference: it may be greater than capacity (in that case only the first capacity references are written). |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- Devices can only be queried or selected on the Host.
- A reference stores only the device ordinal and does not own Runtime state.
- On a failed query, the output parameter keeps its original value; the properties are limited to the AI Core, Vector Core, Warp, UB, GM, L2, and architecture fields listed by the current interface.

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
#include <asc/devices>
#include <vector>


void run_example()
{
    asc::std::uint32_t available = 0;
    check(asc::devices(nullptr, 0, available));
    check(available > 0);
    std::vector<asc::device_ref> output(available, asc::device_ref(99));
    asc::std::uint32_t total = 0;
    check(asc::devices(output.data(), available, total));
    check(total == available);
    for (asc::std::uint32_t i = 0; i < total; ++i) {
        check(output[i].ordinal() == i);
    }
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
