# asc::event::`operator=`

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

`asc::event::operator=` exchanges the Runtime event handles held by the current object and the source object, completing the ownership move.

## Function Prototype

Member of: [`asc::event`](event.md).

```cpp
// Excerpt of the declaration inside asc::event; template parameters and other members are provided by the owning class.
asc::event& operator=(asc::event&& other) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `other` | Input/Output | The owner to be moved; an rvalue must be passed (for example static_cast<owning type&&>(other)); the assignment swaps the two handles, the original target handle remains held by other, and copy assignment is not available. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::event&` | Returns a reference to the updated current object, which can be used for further assignment or compound operations. |

## Constraints

- Usable only on the Host, and the object is not copyable.
- Move operations transfer resource ownership.
- close() performs synchronization and destroys its own resources; on failure it retains ownership.
- The destructor attempts to complete local cleanup.

## Example

The following snippet focuses on calling this interface; inputs, resources, and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/stream>

template <class Object, class... Args>
decltype(auto) example(Object& object, Args&&... args)
{
    return object.operator=(static_cast<Args&&>(args)...);
}
```

The corresponding complete project uses `C++17`; compile and run it on the target toolchain and device.

Complete example source: [stream_event.cpp](../../../../../zh/examples/stream_event.cpp).

## Related APIs

- [`asc::event`](event.md)
- [API list for this header](asc_stream.md)
