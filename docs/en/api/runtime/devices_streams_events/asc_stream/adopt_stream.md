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

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/stream>

decltype(auto) example(asc::stream_ref::native_handle_type handle, asc::stream& output)
{
    return asc::adopt_stream(handle, output);
}
```

The corresponding complete project uses `C++17`; compile and run it on the target toolchain and device.

Complete example source: [stream_event.cpp](../../../../../zh/examples/stream_event.cpp).

## Related APIs

- [API list for this header](asc_stream.md)
