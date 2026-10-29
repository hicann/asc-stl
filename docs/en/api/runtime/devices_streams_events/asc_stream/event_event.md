# asc::event::event

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

The default constructor creates an event that holds no handle; the move constructor takes the native handle from another object and leaves the source object empty.

## Function Prototype

Member of: [`asc::event`](event.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::event; template parameters and other members are provided by the owning class.
event() noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::event; template parameters and other members are provided by the owning class.
event(asc::event&& other) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | Source object for construction; this object is initialized from its corresponding members or underlying state, and the rvalue form may move that state. |

## Return Value

No return value.

## Constraints

- Usable only on the Host, and the object is not copyable.
- Move operations transfer resource ownership.
- close() performs synchronization and destroys its own resources; on failure it retains ownership.
- The destructor attempts to complete local cleanup.

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
    asc::stream stream;
    check(asc::make_stream(stream));
    asc::event original;
    check(!original && asc::make_event(original));
    void* handle = original.native_handle();
    asc::event moved(static_cast<asc::event&&>(original));
    check(!original && moved.native_handle() == handle);
    check(moved.record(stream));
    finish(stream);
    check(moved.close() && stream.close());
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

- [`asc::event`](event.md)
- [API list for this header](asc_stream.md)
