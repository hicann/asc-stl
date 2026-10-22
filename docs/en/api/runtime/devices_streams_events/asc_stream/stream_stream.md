# asc::stream::stream

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

The default constructor creates a stream that holds no handle; the move constructor takes the native handle from another object and leaves the source object empty.

## Function Prototype

Member of: [`asc::stream`](stream.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::stream; template parameters and other members are provided by the owning class.
stream() noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::stream; template parameters and other members are provided by the owning class.
stream(asc::stream&& other) noexcept;
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

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/stream>

template <class... Args>
asc::stream make_object(Args&&... args)
{
    return asc::stream(static_cast<Args&&>(args)...);
}
```

The corresponding complete project uses `C++17`; compile and run it on the target toolchain and device.

Complete example source: [stream_event.cpp](../../../../../zh/examples/stream_event.cpp).

## Related APIs

- [`asc::stream`](stream.md)
- [API list for this header](asc_stream.md)
