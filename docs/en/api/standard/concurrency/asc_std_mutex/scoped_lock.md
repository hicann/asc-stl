# asc::std::scoped_lock

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

`asc::std::scoped_lock` manages a caller-provided lock over the object's lifetime.

Standard semantics reference: [cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex).

## Declaration

### Prototype 1

```cpp
namespace asc::std {
template<class ...MutexTypes> class scoped_lock;
} // namespace asc::std
```

### Prototype 2

```cpp
namespace asc::std {
template<class Mutex> class scoped_lock<Mutex>;
} // namespace asc::std
```

## Constraints

- Device-side spin waiting must guarantee that the lock holder can make progress concurrently; a waiter must not continuously occupy the same scheduling group and thereby prevent the holder from executing. Custom Mutex types must satisfy the forward-progress guarantee of the corresponding execution model.

- lock_guard<Mutex>: plain/adopt constructors, mutex_type, deleted copy, and destructor.
- scoped_lock<> and scoped_lock<Mutex>: plain/adopt constructors, deleted copy, and destructor.
- Only the domain in which lock/unlock of the explicit Mutex are valid in the current execution space and the call satisfies the adopt preconditions.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example shows concrete inputs, the interface call, and a checkable result.

```cpp
#include <asc/std/mutex>

struct Mutex {
    bool locked = false;
    void lock() { locked = true; }
    bool try_lock() { if (locked) return false; locked = true; return true; }
    void unlock() { locked = false; }
    void lock_shared() { lock(); }
    bool try_lock_shared() { return try_lock(); }
    void unlock_shared() { unlock(); }
};

bool example()
{
    Mutex mutex;
    {
        asc::std::scoped_lock<Mutex> lock(mutex);
        if (!mutex.locked) return false;
    }
    return !mutex.locked;
}
```

## Related APIs

- [API list for this header](asc_std_mutex.md)
