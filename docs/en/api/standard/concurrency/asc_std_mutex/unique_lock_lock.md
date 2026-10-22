# asc::std::unique_lock::lock

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

Header: `<asc/std/mutex>`.

`asc::std::unique_lock::lock` acquires ownership of the caller-provided Lockable object.

Standard semantics reference: [cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex).

## Function Prototype

Member of: [`asc::std::unique_lock`](unique_lock.md).

```cpp
// Excerpt of the declaration inside the asc::std::unique_lock class; template parameters and other members are provided by the owning class.
void lock();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- Device-side spin waiting must guarantee that the lock holder can make progress concurrently; a waiter must not continuously occupy the same scheduling group and thereby prevent the holder from executing. Custom Mutex types must satisfy the forward-progress guarantee of the corresponding execution model.

- The underlying Mutex object must be alive and associated with the wrapper. lock or try_lock requires that the wrapper does not currently hold the lock; an empty wrapper after default construction or release cannot be locked directly.

- unique_lock<Mutex>: mutex_type, default/plain/defer/try/adopt constructors, deleted copy, move construction/assignment, and destructor.
- lock/try_lock/unlock/swap/release/mutex/owns_lock/operator bool and the non-member swap on valid states.
- The explicit non-throwing Device Lockable domain.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host snippet demonstrates the call with standard lock objects; the caller must follow the lock ownership and lifetime constraints.

```cpp
#include <asc/std/mutex>

#include <mutex>

void example(::std::mutex& mutex)
{
    asc::std::unique_lock<::std::mutex> guard(mutex, asc::std::defer_lock);
    guard.lock();
}
```

## Related APIs

- [`asc::std::unique_lock`](unique_lock.md)
- [API list for this header](asc_std_mutex.md)
