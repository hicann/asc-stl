# asc::block_any

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

`asc::block_any` determines whether at least one thread in the same block has a predicate of true.

## Function Prototype

```cpp
namespace asc {
bool block_any(asc::block_collective_workspace<asc::std::uint32_t> workspace, bool predicate) noexcept;
}  // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `workspace` | Input/Output | Collective operation workspace of the current thread block; it must not be reused while the participating threads rendezvous. |
| `predicate` | Input | The bool vote value already computed by this lane or thread; the interface processes this value collectively and does not invoke a predicate function. |

## Return Value

| Return type | Description |
| --- | --- |
| `bool` | Returns `true` when the condition holds, otherwise `false`. |

## Constraints

- Can only be called in AI Core SIMT programming.
- All threads of the same block must rendezvous and call it in the same order; the total thread count must be a positive integer multiple of 32.
- The workspace comes from the dynamic shared UB of the block, holds at least thread_count()/32 elements of T, and must not be reused by other concurrent operations during the call.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/collectives>

__aicore__ bool example(unsigned int* dynamic_shared_pointer, bool predicate)
{
    // Participating threads of the same thread block use a common dynamic shared workspace.
    auto workspace = asc::make_block_collective_workspace(dynamic_shared_pointer, 2u);
    return asc::block_any(workspace, predicate);
}
```

## Related APIs

- [API list for this header](asc_collectives.md)
