# asc::std::atomic_load

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

`asc::std::atomic_load` reads the current atomic value with the specified or default memory order; the memory order and address space must satisfy the restrictions on this page.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

```cpp
namespace asc::std {
template<class T> T atomic_load(const atomic<T>* object) noexcept;
} // namespace asc::std
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | The value type held by the atomic object; it must be a trivially copyable type supported by the interface. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `object` | Input | Points to a live atomic object that satisfies the type alignment; reads its atomic state or implementation properties without acquiring ownership of the object. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the current atomic value read with the selected memory order. |

## Constraints

- Atomic operations can be called in Host and AI Core SIMT programming; atomic objects shared by SIMT threads must be located in GM and initialized before concurrent access.
- `object` must point to a valid [atomic](atomic.md) object whose value type must match the template parameter `T`.
- The form without a memory order parameter uses `memory_order_seq_cst`.

## Example

The following Host snippet uses a concrete integer atomic object; device-side objects must be located in accessible global memory.

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> value{7};
    return asc::std::atomic_load(&value) == 7;
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
