# asc::fill_bytes

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

Header: `<asc/algorithm>`.

`asc::fill_bytes` fills a block of device-accessible memory with the given one-byte value.

## Function Prototype

```cpp
namespace asc {
asc::execution_status fill_bytes(asc::stream_ref stream, void* destination, unsigned char value, asc::std::size_t bytes) noexcept;
} // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `stream` | Input | Stream used to submit asynchronous work in order. The related resources must remain valid until the work completes. |
| `destination` | Output | Start address of the destination memory to fill: must be writable, must cover bytes bytes, and must remain valid until the asynchronous operation completes. |
| `value` | Input | Fill value (unsigned char, 0-255): this byte is written repeatedly, byte by byte, into the destination region. |
| `bytes` | Input | Number of bytes to fill, in bytes; when it is 0, no task is submitted and success is returned directly. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::execution_status` | Returns the parameter validation or task submission status; a successful submission does not mean the asynchronous work has completed. |

## Constraints

- Can be called on the Host only.
- The stream must be valid.
- The destination address must be accessible by the device and remain valid until the asynchronous fill completes.

## Example

The following snippet demonstrates the basic call form of the interface on this page; the inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/algorithm>
#include <asc/std/cstddef>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

decltype(auto) example(asc::stream_ref stream, void* destination, unsigned char value, asc::std::size_t bytes)
{
    return asc::fill_bytes(stream, destination, value, bytes);
}
```

## Related APIs

- [`asc::execution_status`](../../../runtime/execution_policies_and_status/asc_execution/execution_status.md): Parameter validation and task submission status; a successful submission does not mean the asynchronous work has completed.
