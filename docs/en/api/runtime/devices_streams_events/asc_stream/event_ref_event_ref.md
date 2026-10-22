# asc::event_ref::event_ref

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

The default constructor creates an empty event reference; the parameterized constructor wraps the given native handle without taking its ownership.

## Function Prototype

Member of: [`asc::event_ref`](event_ref.md).

### Prototype 1

```cpp
// Excerpt of the declaration inside asc::event_ref; template parameters and other members are provided by the owning class.
constexpr event_ref() noexcept;
```

### Prototype 2

```cpp
// Excerpt of the declaration inside asc::event_ref; template parameters and other members are provided by the owning class.
constexpr explicit event_ref(asc::event_ref::native_handle_type handle) noexcept;
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

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/stream>

template <class... Args>
asc::event_ref make_object(Args&&... args)
{
    return asc::event_ref(static_cast<Args&&>(args)...);
}
```

The corresponding complete project uses `C++17`; compile and run it on the target toolchain and device.

Complete example source: [stream_event.cpp](../../../../../zh/examples/stream_event.cpp).

## Related APIs

- [`asc::event_ref`](event_ref.md)
- [API list for this header](asc_stream.md)
