# asc::std::defer_lock_t

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

`asc::std::defer_lock_t` marks the acquisition strategy adopted when constructing a lock wrapper.

Standard semantics reference: [cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex).

## Declaration

```cpp
namespace asc::std {
using defer_lock_t = __lock_detail::__lock_tag<0>;
}
```

## Constraints

- defer_lock_t, try_to_lock_t, and adopt_lock_t, together with the corresponding three inline constexpr objects defer_lock, try_to_lock, and adopt_lock.
- Pure types and objects; they do not own or operate on locks.
- Host, AI Core SIMD programming, and AI Core SIMT programming.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/mutex>
#include <mutex>

bool example()
{
    ::std::mutex mutex;
    asc::std::unique_lock<::std::mutex> guard(mutex, asc::std::defer_lock);
    guard.lock();
    const bool owned = guard.owns_lock();
    guard.unlock();
    return owned && !guard.owns_lock();
}
```

## Related APIs

- [API list for this header](asc_std_mutex.md)
