# asc::stream_ref::stream_ref

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

The default constructor creates an empty stream reference; the parameterized constructor wraps the given native handle without taking its ownership.

## Function Prototype

Member of: [`asc::stream_ref`](stream_ref.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::stream_ref; template parameters and other members are provided by the owning class.
constexpr stream_ref() noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::stream_ref; template parameters and other members are provided by the owning class.
constexpr explicit stream_ref(asc::stream_ref::native_handle_type handle) noexcept;
```

## Parameters

### Parameters of Prototype 1

No parameters.

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `handle` | Input | Runtime native handle (native_handle_type, an opaque void pointer), not a wrapper object; adopt takes over ownership, while ref construction only borrows. |

## Return Value

No return value.

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
    asc::stream_ref empty;
    check(!empty);
    asc::stream owner;
    check(asc::make_stream(owner));
    asc::stream_ref view(owner.native_handle());
    check(view && view.native_handle() == owner.native_handle());
    finish(view);
    check(owner.close());
    // view does not own the handle and must not be used after owner.close().
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
