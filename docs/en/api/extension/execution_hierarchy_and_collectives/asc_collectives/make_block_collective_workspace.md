# asc::make_block_collective_workspace

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

`asc::make_block_collective_workspace` creates a block collective operation workspace from the dynamic shared UB provided by the caller.

## Function Prototype

```cpp
namespace asc {
template<class T> asc::block_collective_workspace<T> make_block_collective_workspace(T* dynamic_shared_pointer, asc::std::uint32_t element_count) noexcept;
} // namespace asc
```

## Parameters

**Template Parameters**

| Parameter | Description |
| --- | --- |
| `T` | Element type read and written by each participating thread; it determines the size and alignment of the workspace. |

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `dynamic_shared_pointer` | Input | Start address of the dynamic shared UB of the current block, aligned to T; it must hold element_count elements, all participating threads use the same region, and it must not be reused before the collective operation completes. |
| `element_count` | Input | Number of elements participating in the operation. |

## Return Value

| Return type | Description |
| --- | --- |
| `asc::block_collective_workspace<T>` | Returns a thread block collective operation workspace referencing the dynamic shared storage provided by the caller. |

## Constraints

- Can only be called in AI Core SIMT programming.
- The threads of the same block must rendezvous for the call.
- The thread count, dynamic shared UB workspace, and synchronization order must satisfy the declaration requirements, and the workspace must not be reused concurrently during the call.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/collectives>

__aicore__ asc::block_collective_workspace<unsigned int> example(unsigned int* dynamic_shared_pointer)
{
    // The workspace borrows the dynamic shared UB of the current thread block and does not own that storage.
    return asc::make_block_collective_workspace(dynamic_shared_pointer, 2u);
}
```

## Related APIs

- [API list for this header](asc_collectives.md)
