# asc::event::~event

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

The `asc::event` destructor synchronizes and destroys the Runtime event handle still held by the object; when the handle has been released or the object is empty, no Runtime operation is performed.

## Function Prototype

Member of: [`asc::event`](event.md).

```cpp
// Excerpt of the declaration inside asc::event; template parameters and other members are provided by the owning class.
~event();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- Usable only on the Host, and the object is not copyable.
- Move operations transfer resource ownership.
- close() performs synchronization and destroys its own resources; on failure it retains ownership.
- The destructor attempts to complete local cleanup.

## Example

The following example manually destroys the object only in explicitly managed aligned raw storage. Ordinary automatic variables should be destroyed by scope exit; call close first when the resource cleanup status needs to be checked.

```cpp
#include <asc/stream>
#include <asc/std/new>
bool example()
{
    alignas(asc::event) unsigned char storage[sizeof(asc::event)];
    auto* object = ::new (static_cast<void*>(storage)) asc::event;
    const bool initially_empty = !static_cast<bool>(*object);
    object->~event();
    // storage is raw byte storage and will not implicitly destroy the same object again.
    return initially_empty;
}
```

## Related APIs

- [`asc::event`](event.md)
- [API list for this header](asc_stream.md)
