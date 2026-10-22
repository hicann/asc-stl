# asc::barrier::wait

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

Header: `<asc/barrier>`.

`asc::barrier::wait` uses an arrival token to wait for the corresponding barrier phase to complete.

## Function Prototype

Member of: [`asc::barrier`](barrier.md).

```cpp
// Excerpt of the declaration inside the asc::barrier class; template parameters and other members are provided by the owning class.
void wait(asc::barrier_arrival_token&& token) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `token` | Input/Output | Provides the object reference used to "use an arrival token to wait for the corresponding barrier phase to complete"; the referenced object must be valid for the duration of the call. |

## Return Value

No return value.

## Constraints

- Uses C++17.
- Operates on caller-managed GM state in AI Core SIMT programming.
- Scope must be asc::memory_scope::block or asc::memory_scope::device.
- All blocking participants must be able to make progress concurrently.
- Copy construction and copy assignment are deleted.

## Example

The following AI Core SIMT snippet uses a caller-managed GM synchronization object; the participant count and progress conditions must satisfy the constraints on this page.

```cpp
#include <asc/barrier>

__aicore__ void example(asc::barrier<asc::memory_scope::block>* gm_barrier)
{
    // All participants must be able to make progress concurrently, and gm_barrier must point to a valid GM object.
    auto token = gm_barrier->arrive();
    gm_barrier->wait(static_cast<asc::barrier_arrival_token&&>(token));
}
```

## Related APIs

- [`asc::barrier`](barrier.md)
- [API list for this header](asc_barrier.md)
