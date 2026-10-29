# asc::std::atomic::store

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

`asc::std::atomic::store` stores the atomic value with the specified or default memory order.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

Member of: [`asc::std::atomic`](atomic.md).

```cpp
// Excerpt of the declaration inside the asc::std::atomic class; template parameters and other members are provided by the enclosing class.
void store(T value, memory_order order = memory_order_seq_cst) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The new value written to the atomic object. |
| `order` | Input | The memory order used for the write, determining the visibility order of this write to other threads; it can only take relaxed, release, or seq_cst. |

## Return Value

No return value.

## Constraints

- Atomic operations can be called in Host and AI Core SIMT programming; atomic objects shared by SIMT threads must be located in GM and initialized before concurrent access.
- The memory order must be `memory_order_relaxed`, `memory_order_release`, or `memory_order_seq_cst`; `memory_order_consume`, `memory_order_acquire`, and `memory_order_acq_rel` are not allowed.

## Example

The following Host snippet demonstrates the atomic operation; device-side objects must be placed in a valid memory space as specified on this page.

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> value{1};
    value.store(7, asc::std::memory_order_release);
    return value.load() == 7;
}
```

## Related APIs

- [`asc::std::atomic`](atomic.md)
- [API list for this header](asc_std_atomic.md)
