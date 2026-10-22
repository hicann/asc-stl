# asc::block_reduce_add

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

`asc::block_reduce_add` sums the values of the participating threads within the same thread block and returns the reduction result. The calling threads must participate simultaneously according to the rendezvous requirements of the collective operation, and the workspace must not be reused by other operations during the call.

## Function Prototype

### Prototype 1

```cpp
namespace asc {
asc::std::int32_t block_reduce_add(asc::block_collective_workspace<asc::std::int32_t> workspace, asc::std::int32_t value) noexcept;
} // namespace asc
```

### Prototype 2

```cpp
namespace asc {
asc::std::uint32_t block_reduce_add(asc::block_collective_workspace<asc::std::uint32_t> workspace, asc::std::uint32_t value) noexcept;
} // namespace asc
```

### Prototype 3

```cpp
namespace asc {
float block_reduce_add(asc::block_collective_workspace<float> workspace, float value) noexcept;
} // namespace asc
```

## Parameters

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `workspace` | Input/Output | Collective operation workspace of the current thread block; its capacity must accommodate the number of participating threads, and it must not be reused concurrently during the call. |
| `value` | Input | One value to be reduced, provided by the current thread. |

## Data Types

`int32_t`, `uint32_t`, and `float` are supported; the workspace element type, input value type, and return value type must be identical.

## Return Value

| Applicable prototype | Return type | Description |
| --- | --- | --- |
| Prototype 1 | `asc::std::int32_t` | Returns the signed integer sum of the input values of the participating threads. |
| Prototype 2 | `asc::std::uint32_t` | Returns the unsigned integer sum of the input values of the participating threads. |
| Prototype 3 | `float` | Returns the floating-point sum of the input values of the participating threads. |

## Constraints

- Can only be called in AI Core SIMT programming.
- All threads of the same block must rendezvous and call it in the same order; the total thread count must be a positive integer multiple of 32.
- The workspace comes from the dynamic shared UB of the block, holds at least thread_count()/32 elements of T, and must not be reused by other concurrent operations during the call.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/collectives>

__aicore__ unsigned int example(unsigned int* dynamic_shared_pointer, unsigned int value)
{
    // The pointer must point to dynamic shared UB of the current thread block with at least two elements.
    auto workspace = asc::make_block_collective_workspace(dynamic_shared_pointer, 2u);
    return asc::block_reduce_add(workspace, value);
}
```

## Related APIs

- [asc::make_block_collective_workspace](make_block_collective_workspace.md)
- [asc::block_reduce_max](block_reduce_max.md)
- [asc::block_reduce_min](block_reduce_min.md)
