# asc::barrier::arrive

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

`asc::barrier::arrive` decrements the not-yet-arrived count of the current phase and returns the arrival token of that phase.

## Function Prototype

Member of: [`asc::barrier`](barrier.md).

```cpp
// Excerpt of the declaration inside the asc::barrier class; template parameters and other members are provided by the owning class.
asc::barrier_arrival_token arrive(asc::std::ptrdiff_t update = 1) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `update` | Input | The number of participants counted by this arrival, 1 by default: the not-yet-arrived count is decremented by this value, and when it reaches 0 the completion function is triggered and the next phase starts. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::barrier_arrival_token` | Returns the arrival token of that phase. |

## Constraints

- The initial expected must be within `[0, max()]`; the update of arrive must be non-negative and must not exceed the remaining count of the current phase. When expected is 0, arrival with a positive update is not allowed; arrive_and_drop additionally requires the subsequent expected count to be currently positive.

- Uses C++17.
- Operates on caller-managed GM state in AI Core SIMT programming.
- Scope must be asc::memory_scope::block or asc::memory_scope::device.
- All blocking participants must be able to make progress concurrently.
- Copy construction and copy assignment are deleted.

## Example

The following AI Core SIMT snippet uses a caller-managed GM synchronization object; the participant count and progress conditions must satisfy the constraints on this page.

```cpp
#include <asc/barrier>

__aicore__ decltype(auto) example(asc::barrier<asc::memory_scope::block>* gm_barrier)
{
    // The object is located in GM; blocking operations are called only when all participants can make progress concurrently.
    return gm_barrier->arrive();
}
```

## Related APIs

- [`asc::barrier`](barrier.md)
- [API list for this header](asc_barrier.md)
