# asc::block_broadcast

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

Header: `<asc/collectives>`.

`asc::block_broadcast` broadcasts the value of a specified source thread to all threads in the same block.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
asc::std::int32_t block_broadcast(asc::block_collective_workspace<asc::std::int32_t> workspace, asc::std::int32_t value,
    asc::std::uint32_t source_thread) noexcept;
}  // namespace asc
```

### Prototype 2

```cpp
namespace asc {
asc::std::uint32_t block_broadcast(asc::block_collective_workspace<asc::std::uint32_t> workspace,
    asc::std::uint32_t value, asc::std::uint32_t source_thread) noexcept;
}  // namespace asc
```

### Prototype 3

```cpp
namespace asc {
float block_broadcast(
    asc::block_collective_workspace<float> workspace, float value, asc::std::uint32_t source_thread) noexcept;
}  // namespace asc
```

## Parameters

### Parameters of Prototype 1

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `workspace` | Input/Output | Collective operation workspace of the current thread block; it must not be reused while the participating threads rendezvous. |
| `value` | Input | The value to broadcast: only the value provided by the source_thread thread is used, and the values passed by the other threads are ignored. |
| `source_thread` | Input | Thread index of the broadcast source thread within the current thread block; this parameter is a scalar index and does not involve storage lifetime. |

### Parameters of Prototype 2

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `workspace` | Input/Output | Collective operation workspace of the current thread block; it must not be reused while the participating threads rendezvous. |
| `value` | Input | The value to broadcast: only the value provided by the source_thread thread is used, and the values passed by the other threads are ignored. |
| `source_thread` | Input | Thread index of the broadcast source thread within the current thread block; this parameter is a scalar index and does not involve storage lifetime. |

### Parameters of Prototype 3

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `workspace` | Input/Output | Collective operation workspace of the current thread block; it must not be reused while the participating threads rendezvous. |
| `value` | Input | The value to broadcast: only the value provided by the source_thread thread is used, and the values passed by the other threads are ignored. |
| `source_thread` | Input | Thread index of the broadcast source thread within the current thread block; this parameter is a scalar index and does not involve storage lifetime. |

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::std::int32_t` | Returns the result corresponding to the current thread after the thread block broadcast or scan. |
| Prototype 2 | `asc::std::uint32_t` | Returns the result corresponding to the current thread after the thread block broadcast or scan. |
| Prototype 3 | `float` | Returns the result corresponding to the current thread after the thread block broadcast or scan. |

## Constraints

- Can only be called in AI Core SIMT programming.
- All threads of the same block must rendezvous and call it in the same order; the total thread count must be a positive integer multiple of 32.
- The workspace comes from the dynamic shared UB of the block, holds at least thread_count()/32 elements of T, and must not be reused by other concurrent operations during the call.
- source_thread is the flattened thread number within the block; it must be less than the total thread count, and all threads pass the same number.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/collectives>

__aicore__ unsigned int example(unsigned int* dynamic_shared_pointer, unsigned int value)
{
    // Broadcast the input value from thread 0 of the current thread block.
    auto workspace = asc::make_block_collective_workspace(dynamic_shared_pointer, 2u);
    return asc::block_broadcast(workspace, value, 0u);
}
```

## Related APIs

- [API list for this header](asc_collectives.md)
