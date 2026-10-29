# asc::make_stream

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

`asc::make_stream` creates a Runtime stream with the specified priority and writes the ownership to an empty `stream` object; it returns false when the output object already holds a handle or when creation fails.

This interface is available on the Host.

## Function Prototype

```cpp
namespace asc {
bool make_stream(asc::stream& output, asc::std::uint32_t priority = 0) noexcept;
} // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Reference to the empty stream object that receives the newly created Stream: it must not hold a handle yet, and on success it gains ownership of the new Runtime Stream; if it already holds a handle, failure is returned directly. |
| `priority` | Input | Priority of the newly created Stream (uint32_t, passed to the underlying Runtime; 0 is the normal priority). |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- If `output` is non-empty (already holds a handle), this interface refuses to execute, returns `false` directly, creates no new Runtime Stream, and does not modify `output`.
- output remains unchanged on failure.

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
    check(!stream);
    check(asc::make_stream(stream, 0));
    check(static_cast<bool>(stream));
    check(!asc::make_stream(stream));
    asc::std::uint32_t priority = 99;
    check(stream.priority(priority) && priority == 0);
    finish(stream);
    check(stream.close() && !stream);
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
