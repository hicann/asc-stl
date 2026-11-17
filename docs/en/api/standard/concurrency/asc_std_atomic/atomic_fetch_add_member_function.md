# asc::std::atomic::fetch_add

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

`asc::std::atomic::fetch_add` atomically adds the operand and returns the value before the modification.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

Member of: [`asc::std::atomic`](atomic.md).

```cpp
// Excerpt of the declaration inside the asc::std::atomic class; template parameters and other members are provided by the enclosing class.
T fetch_add(T value, memory_order order = memory_order_seq_cst) noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The operand added to the current value of the atomic object; the value before the modification is returned. |
| `order` | Input | The memory order used by the read-modify-write, determining the visibility order of this operation; it can take any enumerator of memory_order. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the value before the modification. |

## Constraints

- Atomic operations can be called in Host and AI Core SIMT programming; atomic objects shared by SIMT threads must be located in GM and initialized before concurrent access.
- The read-modify-write returns the value held before the operation; the form without a memory order parameter uses `memory_order_seq_cst`.

## Example

For a parallel bucket scatter, initialize each bucket counter to zero before
workers start. Each valid item reserves a distinct slot using
`slot = counters[bucket].fetch_add(1, memory_order_relaxed)` and writes its index
to that bucket's preallocated output window. Ensure enough capacity and avoid
counter overflow. The returned slot does not publish the later payload write:
consume the output only after thread joins or kernel/stream completion, or use a
separate correctly synchronized publication protocol. Arrival order within a
bucket is unspecified. An independent check should compare each bucket's count
and item multiset rather than require stable input order.

The following Host snippet demonstrates the atomic operation; device-side objects must be placed in a valid memory space as specified on this page.

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> value{5};
    const auto before = value.fetch_add(3, asc::std::memory_order_relaxed);
    return before == 5 && value.load() == 8;
}
```

## Related APIs

- [`asc::std::atomic`](atomic.md)
- [API list for this header](asc_std_atomic.md)
