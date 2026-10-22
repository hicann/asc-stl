# asc::std::atomic_flag_clear_explicit

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

`asc::std::atomic_flag_clear_explicit` atomically clears the flag bit with the specified memory order.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

```cpp
namespace asc::std {
void atomic_flag_clear_explicit(atomic_flag* object, memory_order order) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `object` | Input/Output | Pointer to the atomic flag object that is set or cleared. |
| `order` | Input | The memory order used to clear the flag, determining the visibility order of this write; it can only take relaxed, release, or seq_cst. |

## Return Value

No return value.

## Constraints

- It can be called in Host or AI Core SIMT programming; flag objects shared by SIMT threads must be located in GM and initialized before concurrent access.
- `object` must point to a valid non-volatile [atomic_flag](atomic_flag.md) object.
- The memory order must be `memory_order_relaxed`, `memory_order_release`, or `memory_order_seq_cst`; `memory_order_consume`, `memory_order_acquire`, and `memory_order_acq_rel` are not allowed.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/atomic>

void example(asc::std::atomic_flag * object, asc::std::memory_order order)
{
    asc::std::atomic_flag_clear_explicit(object, order);
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
