# asc::make_event

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

`asc::make_event` creates a Runtime event and writes the ownership to an empty `event` object; it returns false when the output object already holds a handle or when creation fails.

This interface is available on the Host.

## Function Prototype

```cpp
namespace asc {
bool make_event(asc::event& output) noexcept;
} // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Provides the object reference used to "create a Runtime event and write the ownership to an empty `event` object"; the referenced object must be valid for the duration of the call. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- If `output` is non-empty (already holds a handle), this interface refuses to execute, returns `false` directly, creates no new Runtime event, and does not modify `output`.
- output remains unchanged on failure.

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/stream>

decltype(auto) example(asc::event& output)
{
    return asc::make_event(output);
}
```

The corresponding complete project uses `C++17`; compile and run it on the target toolchain and device.

Complete example source: [stream_event.cpp](../../../../../zh/examples/stream_event.cpp).

## Related APIs

- [API list for this header](asc_stream.md)
