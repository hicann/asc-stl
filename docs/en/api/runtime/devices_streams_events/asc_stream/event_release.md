# asc::event::release

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

`asc::event::release` releases the object's ownership of the native event handle and returns that handle, without synchronizing or destroying it.

## Function Prototype

Member of: [`asc::event`](event.md).

```cpp
// Excerpt of the declaration inside asc::event; template parameters and other members are provided by the owning class.
asc::event_ref::native_handle_type release() noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `asc::event_ref::native_handle_type` | Returns the handle without synchronizing or destroying it. |

## Constraints

- Usable only on the Host, and the object is not copyable.
- Move operations transfer resource ownership.
- close() performs synchronization and destroys its own resources; on failure it retains ownership.
- The destructor attempts to complete local cleanup.

## Example

The following Host example initializes the Runtime on device 0, checks the resource status, and closes the Runtime after the resource is released; running it requires CANN to be installed and the device to be available.

```cpp
#include <acl/acl.h>
#include <asc/stream>

bool resource_example()
{
    asc::event owner;
    if (!asc::make_event(owner)) return false;
    void* handle = owner.release();
    const bool transferred = handle != nullptr && !owner;
    asc::event receiver;
    if (!asc::adopt_event(handle, receiver)) {
        const bool cleaned = aclrtDestroyEvent(static_cast<aclrtEvent>(handle)) == ACL_SUCCESS;
        return cleaned && false;
    }
    const bool closed = receiver.close();
    return transferred && closed;
}

bool example()
{
    if (aclInit(nullptr) != ACL_SUCCESS) return false;
    if (aclrtSetDevice(0) != ACL_SUCCESS) {
        const bool finalized = aclFinalize() == ACL_SUCCESS;
        return finalized && false;
    }
    const bool passed = resource_example();
    const bool reset = aclrtResetDevice(0) == ACL_SUCCESS;
    const bool finalized = aclFinalize() == ACL_SUCCESS;
    return passed && reset && finalized;
}
```

## Related APIs

- [`asc::event`](event.md)
- [API list for this header](asc_stream.md)
