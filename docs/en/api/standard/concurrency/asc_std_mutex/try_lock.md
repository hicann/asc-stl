# asc::std::try_lock

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

`asc::std::try_lock` tries to acquire multiple caller-provided locks in order and returns the position of the failure.

Standard semantics reference: [cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex).

## Function Prototype

```cpp
namespace asc::std {
template<class... Mutexes> int try_lock(Mutexes&... mutexes);
}
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `Mutexes...` | Two or more mutex types that satisfy the Lockable requirements at the current execution location and whose operations do not throw. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `mutexes...` | Input/Output | Valid mutex objects given in the order they are tried; on failure, the locks acquired by this call are rolled back, and locks originally held by other participants are not affected. |

## Return Value

Returns int. -1 when all acquisitions succeed; on failure, returns the zero-based index of the first mutex whose acquisition failed, and releases all locks previously acquired by this call.

## Constraints

- The parameter pack contains at least two Mutex objects; each object must support try_lock() and unlock() at the applicable execution location, and these operations must not throw; on failure, the locks acquired by this call are released.

- asc::std::try_lock on two or more explicit non-throwing Device Lockable objects: tries in parameter order, returns -1 on success, and on failure returns the zero-based index and rolls back all locks previously acquired.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

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
    simple_mutex first, second;
    second.lock();
    const int failed = asc::std::try_lock(first, second);
    if (failed != 1 || first.locked || !second.locked) return false;
    second.unlock();
    const int acquired = asc::std::try_lock(first, second);
    const bool both = acquired == -1 && first.locked && second.locked;
    if (first.locked) first.unlock();
    if (second.locked) second.unlock();
    return both;
}
```

## Related APIs

- [API list for this header](asc_std_mutex.md)
