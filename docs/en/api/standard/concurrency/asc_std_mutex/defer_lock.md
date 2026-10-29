# asc::std::defer_lock

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

`asc::std::defer_lock` marks the form that does not acquire the lock at construction time.

Standard semantics reference: [cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex).

## Declaration

```cpp
namespace asc::std {
inline constexpr const defer_lock_t defer_lock;
} // namespace asc::std
```

## Constraints

- defer_lock_t, try_to_lock_t, and adopt_lock_t, together with the corresponding three inline constexpr objects defer_lock, try_to_lock, and adopt_lock.
- Pure types and objects; they do not own or operate on locks.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/mutex>
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
    using lock_type = asc::std::unique_lock<example_mutex>;
    example_mutex mutex;
    lock_type guard(mutex, asc::std::defer_lock);
    return !guard.owns_lock() && !mutex.locked;
}
```

## Related APIs

- [API list for this header](asc_std_mutex.md)
