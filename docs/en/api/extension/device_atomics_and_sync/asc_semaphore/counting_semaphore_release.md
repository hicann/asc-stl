# asc::counting_semaphore::release

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

Header: `<asc/semaphore>`.

`asc::counting_semaphore::release` atomically increases the semaphore permits by the specified amount and wakes up waiters.

## Function Prototype

Member of: [`asc::counting_semaphore`](counting_semaphore.md).

```cpp
// Excerpt of the declaration inside the asc::counting_semaphore class; template parameters and other members are provided by the owning class.
void release(asc::std::ptrdiff_t update = 1) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `update` | Input | The amount by which permits are increased, 1 by default: the internal count is atomically increased by this value and waiters are woken up. |

## Return Value

No return value.

## Constraints

- The initial desired must be within `[0, max()]`; the update of release must be non-negative, and after the increase the permit count must not exceed max(). The construction stores the count, and the caller must satisfy these bounds beforehand.

- Uses C++17.
- Operates on caller-managed GM state in AI Core SIMT programming.
- Scope must be asc::memory_scope::block or asc::memory_scope::device.
- All blocking participants must be able to make progress concurrently.
- Copy construction and copy assignment are deleted.

## Example

The following AI Core SIMT snippet uses a caller-managed GM synchronization object; the participant count and progress conditions must satisfy the constraints on this page.

```cpp
#include <asc/semaphore>

__aicore__ void example(asc::counting_semaphore<asc::memory_scope::block, 4>* gm_counting_semaphore)
{
    // The object is located in GM; blocking operations are called only when all participants can make progress concurrently.
    gm_counting_semaphore->release();
}
```

## Related APIs

- [`asc::counting_semaphore`](counting_semaphore.md)
- [API list for this header](asc_semaphore.md)
