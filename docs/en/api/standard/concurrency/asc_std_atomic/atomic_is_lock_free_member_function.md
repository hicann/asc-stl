# asc::std::atomic::is_lock_free

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

Header: `<asc/std/atomic>`.

`asc::std::atomic::is_lock_free` reports whether operations on the current atomic object need no lock-based fallback implementation.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

Member of: [`asc::std::atomic`](atomic.md).

```cpp
// Excerpt of the declaration inside the asc::std::atomic class; template parameters and other members are provided by the enclosing class.
bool is_lock_free() const noexcept;
```

## Parameters

No parameters.

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` if the condition holds, otherwise `false`. |

## Constraints

- Atomic operations can be called in Host and AI Core SIMT programming; atomic objects shared by SIMT threads must be located in GM and initialized before concurrent access.
- Returns `true` for the currently supported atomic types; querying the lock-free property establishes no synchronization with other threads.

## Example

The following Host example provides concrete inputs and checks the result of the call.

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> cell{3};
    const bool lock_free = cell.is_lock_free();
    // A type that is always lock-free must also report lock-free at run time.
    return (!asc::std::atomic<int>::is_always_lock_free || lock_free) && cell.load() == 3;
}
```

## Related APIs

- [`asc::std::atomic`](atomic.md)
- [API list for this header](asc_std_atomic.md)
