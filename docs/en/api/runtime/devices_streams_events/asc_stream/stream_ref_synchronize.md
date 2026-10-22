# asc::stream_ref::synchronize

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

`asc::stream_ref::synchronize` blocks the Host until the tasks previously submitted to this Stream are complete; it returns false when the handle is empty or the Runtime call fails.

## Function Prototype

Member of: [`asc::stream_ref`](stream_ref.md).

```cpp
// Excerpt of the declaration inside asc::stream_ref; template parameters and other members are provided by the owning class.
bool synchronize() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- Provides a nullable non-owning Host reference.
- The native handle is an opaque void pointer.
- Query results and output parameters are updated only when the CANN Runtime call succeeds.

## Example

The following Host example initializes the Runtime on device 0, checks the resource status, and closes the Runtime after the resource is released; running it requires CANN to be installed and the device to be available.

```cpp
#include <acl/acl.h>
#include <asc/stream>

bool resource_example()
{
    asc::stream owner;
    if (!asc::make_stream(owner)) return false;
    asc::stream_ref view(owner.native_handle());
    const bool observed = view.synchronize();
    const bool closed = owner.close();
    return observed && closed;
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

- [`asc::stream_ref`](stream_ref.md)
- [API list for this header](asc_stream.md)
