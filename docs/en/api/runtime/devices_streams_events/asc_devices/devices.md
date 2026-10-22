# asc::devices

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

Header: `<asc/devices>`.

`asc::devices` writes at most `capacity` device references, ordered by ordinal, into the caller's array, and returns the full device count reported by the Runtime through `count`.

## Function Prototype

```cpp
namespace asc {
bool devices(asc::device_ref* output, asc::std::uint32_t capacity, asc::std::uint32_t& count) noexcept;
}  // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `output` | Output | Address of the caller's array that receives the device_ref values: min(capacity, total number of devices) references are written in increasing ordinal order; must not be null when capacity is non-zero. |
| `capacity` | Input | Number of device_ref values the array can hold: only limits the number actually written and does not affect the total reported by count. |
| `count` | Output | The total number of devices reported by the Runtime is written through this reference: it may be greater than capacity (in that case only the first capacity references are written). |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- Devices can only be queried or selected on the Host.
- A reference stores only the device ordinal and does not own Runtime state.
- On a failed query, the output parameter keeps its original value; the properties are limited to the AI Core, Vector Core, Warp, UB, GM, L2, and architecture fields listed by the current interface.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/devices>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

decltype(auto) example(asc::device_ref* output, asc::std::uint32_t capacity, asc::std::uint32_t& count)
{
    return asc::devices(output, capacity, count);
}
```

## Related APIs

- [API list for this header](asc_devices.md)
