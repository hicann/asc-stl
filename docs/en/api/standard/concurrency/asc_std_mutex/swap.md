# asc::std::swap

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

Header: `<asc/std/mutex>`, `<asc/std/shared_mutex>`.

`asc::std::swap` swaps the locks and ownership states held by two lock wrappers.

Standard semantics reference: [cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex).

## Function Prototype

```cpp
namespace asc::std {
template<class Mutex>
void swap(unique_lock<Mutex>& left, unique_lock<Mutex>& right) noexcept;
}
```

The above is provided by `<asc/std/mutex>`.

```cpp
namespace asc::std {
template<class Mutex>
void swap(shared_lock<Mutex>& left, shared_lock<Mutex>& right) noexcept;
}
```

The above is provided by `<asc/std/shared_mutex>`.

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Mutex` | The same underlying mutex type associated with the two lock wrappers. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `left` | Input/Output | The left lock wrapper; its mutex pointer and ownership state are swapped with right. |
| `right` | Input/Output | The right lock wrapper; the two objects and their associated underlying mutexes remain valid during the call. |

## Return Value

No return value. Only the wrappers' pointers and ownership states are swapped; no locking or unlocking is performed on the underlying mutexes.

## Constraints

- Empty lock wrappers or wrappers not holding a lock can be swapped; the operation only swaps the pointers and ownership states and does not change the lock state of the mutex itself.
- The underlying Mutex object must remain alive while the corresponding wrapper holds it, and must support the Lockable or SharedLockable operations at the execution location corresponding to the wrapper.

## Example

The following Host example provides concrete lock states and checks the result of the operation.

```cpp
#include <asc/std/mutex>

struct simple_mutex {
    bool locked = false;
    void lock() { locked = true; }
    bool try_lock() { if (locked) return false; locked = true; return true; }
    void unlock() { locked = false; }
};

bool example()
{
    simple_mutex a, b;
    asc::std::unique_lock<simple_mutex> left(a);
    asc::std::unique_lock<simple_mutex> right(b, asc::std::defer_lock);
    asc::std::swap(left, right);
    const bool transferred = !left.owns_lock() && left.mutex() == &b &&
        right.owns_lock() && right.mutex() == &a && a.locked && !b.locked;
    right.unlock();
    return transferred && !a.locked;
}
```

## Related APIs

- [API list for this header](asc_std_mutex.md)
