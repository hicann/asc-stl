# asc::std::shared_lock::lock

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

`asc::std::shared_lock::lock` acquires ownership of the caller-provided Lockable object.

Standard semantics reference: [cppreference `shared_mutex`](https://en.cppreference.com/w/cpp/header/shared_mutex).

## Function Prototype

Member of: [`asc::std::shared_lock`](shared_lock.md).

```cpp
// Excerpt of the declaration inside the asc::std::shared_lock class; template parameters and other members are provided by the owning class.
void lock();
```

## Parameters

No parameters.

## Return Value

No return value.

## Constraints

- Device-side spin waiting must guarantee that the lock holder can make progress concurrently; a waiter must not continuously occupy the same scheduling group and thereby prevent the holder from executing. Custom Mutex types must satisfy the forward-progress guarantee of the corresponding execution model.

- The underlying Mutex object must be alive and associated with the wrapper. lock or try_lock requires that the wrapper does not currently hold the lock; an empty wrapper after default construction or release cannot be locked directly.

- shared_lock<Mutex>: mutex_type, default/plain/defer/try/adopt constructors, deleted copy, move construction/assignment, and destructor.
- lock/try_lock/unlock/swap/release/mutex/owns_lock/operator bool and the non-member swap on valid states.
- The explicit non-throwing Device SharedLockable domain.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host snippet demonstrates the call with standard lock objects; the caller must follow the lock ownership and lifetime constraints.

```cpp
#include <asc/std/shared_mutex>
#include <new>

// Instrumented single-thread BasicLockable used to observe adapter ownership.
struct example_mutex {
    bool locked = false;
    int unlocks = 0;
    void lock()
    {
        locked = true;
    }
    bool try_lock()
    {
        if (locked)
            return false;
        locked = true;
        return true;
    }
    void unlock()
    {
        locked = false;
        ++unlocks;
    }
    void lock_shared()
    {
        lock();
    }
    bool try_lock_shared()
    {
        return try_lock();
    }
    void unlock_shared()
    {
        unlock();
    }
};

bool example()
{
    using lock_type = asc::std::shared_lock<example_mutex>;
    example_mutex mutex;
    lock_type guard(mutex, asc::std::defer_lock);
    guard.lock();
    const bool held = guard.owns_lock() && mutex.locked;
    guard.unlock();
    return held && !mutex.locked && mutex.unlocks == 1;
}
```

## Related APIs

- [`asc::std::shared_lock`](shared_lock.md)
- [API list for this header](asc_std_shared_mutex.md)
