# asc::event_ref::is_done

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

`asc::event_ref::is_done` performs a non-blocking query of whether this event is done; the output boolean is updated when the query succeeds.

## Function Prototype

Member of: [`asc::event_ref`](event_ref.md).

```cpp
// Excerpt of the declaration inside asc::event_ref; template parameters and other members are provided by the owning class.
bool is_done(bool& output) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Provides the object reference used to "perform a non-blocking query of whether this event is done"; the referenced object must be valid for the duration of the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returning true means the Runtime query succeeded, and output then indicates whether the operation is done (it may be false); returning false means the query failed, and output keeps its original value. |

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


void run_example()
{
    asc::stream stream;
    asc::event event;
    check(asc::make_stream(stream) && asc::make_event(event));
    asc::event_ref view(event.native_handle());
    check(view.record(stream));
    finish(stream);
    bool done = false;
    check(view.is_done(done) && done);
    check(event.close() && stream.close());
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

- [`asc::event_ref`](event_ref.md)
- [API list for this header](asc_stream.md)
