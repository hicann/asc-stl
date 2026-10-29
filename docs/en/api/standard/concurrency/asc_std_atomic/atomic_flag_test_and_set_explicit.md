# asc::std::atomic_flag_test_and_set_explicit

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

`asc::std::atomic_flag_test_and_set_explicit` sets the atomic flag with the specified memory order and returns the previous state.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

```cpp
namespace asc::std {
bool atomic_flag_test_and_set_explicit(atomic_flag* object, memory_order order) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `object` | Input/Output | Pointer to the atomic flag object that is set or cleared. |
| `order` | Input | The memory order used to set the flag and read the previous value, determining the visibility order of this operation; it can take any enumerator of memory_order. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` if the condition holds, otherwise `false`. |

## Constraints

- It can be called in Host or AI Core SIMT programming; flag objects shared by SIMT threads must be located in GM and initialized before concurrent access.
- `object` must point to a valid non-volatile [atomic_flag](atomic_flag.md) object.
- This operation atomically sets the flag to `true` and returns the old value; the form without a memory order parameter uses `memory_order_seq_cst`.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic_flag flag{};
    const bool before = asc::std::atomic_flag_test_and_set_explicit(&flag, asc::std::memory_order_relaxed);
    const bool after = asc::std::atomic_flag_test_and_set_explicit(&flag, asc::std::memory_order_relaxed);
    return !before && after;
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
