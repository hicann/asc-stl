# asc::atomic::load

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

Header: `<asc/atomic>`.

`asc::atomic::load` atomically reads the current value with the specified memory order.

This interface is available in AI Core SIMT programming.

## Function Prototype

Member of: [`asc::atomic`](atomic.md).

```cpp
// Excerpt of the declaration inside the asc::atomic class; template parameters and other members are provided by the owning class.
T load(asc::std::memory_order order = asc::std::memory_order_seq_cst) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `order` | Input | The memory order used by the read. Can be `memory_order_relaxed`, `memory_order_consume`, `memory_order_acquire`, or `memory_order_seq_cst`; release or acq_rel must not be used. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the current atomic value read with the selected memory order. |

## Constraints

- The type, address space, scope, and memory order of the atomic object must match.
- All device atomic units must be located in GM; UB, the stack, or per-core private storage is not within the currently supported domain.

## Example

The following SIMT kernel initializes and accesses one GM atomic unit from a single thread; there is no other concurrent access, and output[0] is expected to be 1. The Host must read the result after the kernel completes.

```cpp
#include <asc/atomic>
#include <asc/std/new>

__global__ void example(int* storage, unsigned int* output)
{
    // Only 1 block and 1 thread are launched; storage and output are both Host-allocated GM.
    auto* object = new (storage) asc::atomic<int>(7);
    auto& cell = *object;
    cell.store(7, asc::std::memory_order_relaxed);

    output[0] = (cell.load(asc::std::memory_order_relaxed) == 7) ? 1U : 0U;
}
```

For the complete project and run steps, see the [atomic_operations example](../../../../../../examples/extension/atomic_operations/README_en.md).

## Related APIs

- [`asc::atomic`](atomic.md)
- [API list for this header](asc_atomic.md)
