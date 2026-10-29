# asc::adopt_stream

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

`asc::adopt_stream` transfers ownership of a non-null Runtime stream native handle to an empty `stream` object without creating new Runtime resources.

This interface is available on the Host.

## Function Prototype

```cpp
namespace asc {
bool adopt_stream(asc::stream_ref::native_handle_type handle, asc::stream& output) noexcept;
}  // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `handle` | Input | Runtime native handle (native_handle_type, an opaque void pointer), not a wrapper object; adopt takes over ownership, while ref construction only borrows. |
| `output` | Output | Provides the object reference used to "transfer ownership of a non-null Runtime stream native handle to an empty `stream` object without creating new Runtime resources"; the referenced object must be valid for the duration of the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- The handle must not be null, and the output object must be empty before the call.
- On failure the output remains unchanged; on success the resource ownership is transferred.

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


void run_example()
{
    aclrtStream handle = nullptr;
    check(aclrtCreateStreamWithConfig(&handle, 0, 0) == ACL_SUCCESS);
    asc::stream owner;
    if (!asc::adopt_stream(handle, owner)) {
        check(aclrtDestroyStream(handle) == ACL_SUCCESS);
        check(false);
    }
    check(owner.native_handle() == handle);
    // Ownership now belongs to owner; do not destroy handle separately.
    finish(owner);
    check(owner.close() && !owner);
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
