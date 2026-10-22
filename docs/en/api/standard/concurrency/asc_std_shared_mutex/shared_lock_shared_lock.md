# asc::std::shared_lock::shared_lock

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

`asc::std::shared_lock::shared_lock` initializes a `shared_lock` object with the constructor form listed on this page.

Standard semantics reference: [cppreference `shared_mutex`](https://en.cppreference.com/w/cpp/header/shared_mutex).

## Function Prototype

### Prototype 1

```cpp
explicit shared_lock(Mutex& mutex);
```

### Prototype 2

```cpp
shared_lock(Mutex& mutex, adopt_lock_t tag) noexcept;
```

### Prototype 3

```cpp
shared_lock(Mutex& mutex, defer_lock_t tag) noexcept;
```

### Prototype 4

```cpp
shared_lock(Mutex& mutex, try_to_lock_t tag);
```

### Prototype 5

```cpp
shared_lock(shared_lock<Mutex>&& mutex) noexcept;
```

### Prototype 6

```cpp
constexpr shared_lock() noexcept;
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `mutex` | Input/Output | The shared mutex object to be associated; a shared lock is acquired on it at construction, and the lock ownership is held by this object. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `mutex` | Input/Output | The shared mutex object whose shared lock is already held by the current thread; after construction, this object takes over the lock ownership. |
| `tag` | Input | The adopt_lock_t tag, written as asc::std::adopt_lock; indicates taking over the shared lock already held by the calling thread. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `mutex` | Input/Output | The shared mutex object to be associated but not locked at construction; after construction, no lock is held yet. |
| `tag` | Input | The defer_lock_t tag, written as asc::std::defer_lock; indicates deferring the lock. |

### Parameters of Prototype 4

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `mutex` | Input/Output | The shared mutex object on which a shared lock is attempted; at construction, try_lock_shared is used to attempt to acquire the lock without blocking. |
| `tag` | Input | The try_to_lock_t tag, written as asc::std::try_to_lock; indicates trying to lock without blocking. |

### Parameters of Prototype 5

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `mutex` | Input/Output | Another shared_lock object move-constructed from; after the move, it is no longer associated with a mutex and holds no lock. |

### Parameters of Prototype 6

No parameters.

## Return Value

No return value.

## Constraints

- shared_lock<Mutex>: mutex_type, default/plain/defer/try/adopt constructors, deleted copy, move construction/assignment, and destructor.
- lock/try_lock/unlock/swap/release/mutex/owns_lock/operator bool and the non-member swap on valid states.
- The explicit non-throwing Device SharedLockable domain.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/shared_mutex>
#include <shared_mutex>

bool example()
{
    ::std::shared_mutex mutex;
    asc::std::shared_lock<::std::shared_mutex> guard(mutex);
    const bool owned = guard.owns_lock();
    guard.unlock();
    return owned && !guard.owns_lock();
}
```

## Related APIs

- [API list for this header](asc_std_shared_mutex.md)
