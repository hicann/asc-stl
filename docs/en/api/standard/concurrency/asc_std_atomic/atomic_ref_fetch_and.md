# asc::std::atomic_ref::fetch_and

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

`asc::std::atomic_ref::fetch_and` atomically performs a bitwise AND and returns the value before the modification.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

```cpp
T asc::std::atomic_ref::fetch_and(T value, asc::std::memory_order order = asc::std::memory_order_seq_cst) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `value` | Input | The integer value bitwise-ANDed with the current value of the target object. |
| `order` | Input | The memory order of this operation; the default is memory_order_seq_cst. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the value before the modification. |

## Constraints

- The type, address space, scope, and memory order of the atomic object must match
- 64-bit objects in the device scope are located in GM, and UB atomic operations only use memory_order_relaxed

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/atomic>

bool example()
{
    alignas(int) int storage = 5;
    int before = 0;
    {
        asc::std::atomic_ref<int> value(storage);
        before = value.fetch_and(3, asc::std::memory_order_relaxed);
    }
    return before == 5 && storage == 1;
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
