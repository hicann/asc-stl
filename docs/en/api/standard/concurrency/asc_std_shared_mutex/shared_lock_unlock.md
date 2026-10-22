# asc::std::shared_lock::unlock

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

Header: `<asc/std/shared_mutex>`.

`asc::std::shared_lock::unlock` releases the currently held ownership of the Lockable.

Standard semantics reference: [cppreference `shared_mutex`](https://en.cppreference.com/w/cpp/header/shared_mutex).

## Function Prototype

Member of: [`asc::std::shared_lock`](shared_lock.md).

```cpp
// Excerpt of the declaration inside the asc::std::shared_lock class; template parameters and other members are provided by the owning class.
void unlock();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- The underlying Mutex object must be alive and associated with the wrapper. unlock requires that the wrapper actually owns the lock; after returning it no longer owns the lock.

- shared_lock<Mutex>: mutex_type, default/plain/defer/try/adopt constructors, deleted copy, move construction/assignment, and destructor.
- lock/try_lock/unlock/swap/release/mutex/owns_lock/operator bool and the non-member swap on valid states.
- The explicit non-throwing Device SharedLockable domain.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host snippet demonstrates the call with standard lock objects; the caller must follow the lock ownership and lifetime constraints.

```cpp
#include <asc/std/shared_mutex>

#include <shared_mutex>

void example(::std::shared_mutex& mutex)
{
    asc::std::shared_lock<::std::shared_mutex> guard(mutex);
    guard.unlock();
}
```

## Related APIs

- [`asc::std::shared_lock`](shared_lock.md)
- [API list for this header](asc_std_shared_mutex.md)
