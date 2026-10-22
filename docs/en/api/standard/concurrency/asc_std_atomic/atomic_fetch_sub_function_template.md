# asc::std::atomic_fetch_sub

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

`asc::std::atomic_fetch_sub` atomically subtracts the operand and returns the value before the modification; the memory order and address space must satisfy the restrictions on this page.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

```cpp
namespace asc::std {
template<class T> T atomic_fetch_sub(atomic<T>* object, T value) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The value type stored by the atomic object. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `object` | Input/Output | Pointer to the atomic object that is read and modified. |
| `value` | Input | The operand subtracted from the current value of the atomic object; the value before the modification is returned. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the value before the modification. |

## Constraints

- Atomic operations can be called in Host and AI Core SIMT programming; atomic objects shared by SIMT threads must be located in GM and initialized before concurrent access.
- `object` must point to a valid [atomic](atomic.md) object whose value type must match the template parameter `T`.
- The read-modify-write returns the value held before the operation; the form without a memory order parameter uses `memory_order_seq_cst`.

## Example

The following Host snippet uses a concrete integer atomic object; device-side objects must be located in accessible global memory.

```cpp
#include <asc/std/atomic>

decltype(auto) example()
{
    asc::std::atomic<int> value{1};
    return asc::std::atomic_fetch_sub(&value, 2);
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
