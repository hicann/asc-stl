# asc::atomic_ref::fetch_add

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

`asc::atomic_ref::fetch_add` atomically adds the operand and returns the value before the modification.

This interface is available in AI Core SIMT programming.

## Function Prototype

Member of: [`asc::atomic_ref`](atomic_ref.md).

```cpp
// Excerpt of the declaration inside the asc::atomic_ref class; template parameters and other members are provided by the owning class.
T fetch_add(T operand, asc::std::memory_order order = asc::std::memory_order_seq_cst) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `operand` | Input | The value that participates in this atomic read, write, or read-modify-write operation. |
| `order` | Input | The memory order used by this atomic read-modify-write; can take the six standard values of `asc::std::memory_order`. The unit must be located in GM; relaxed does not establish a release/acquire relationship with other objects. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the value before the modification. |

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
    *storage = 7;
    asc::atomic_ref<int> cell(*storage);
    cell.store(7, asc::std::memory_order_relaxed);
    const int previous = cell.fetch_add(3, asc::std::memory_order_relaxed);
    output[0] = (previous == 7 && cell.load(asc::std::memory_order_relaxed) == 10) ? 1U : 0U;
}
```

For the complete project and run steps, see the [atomic_operations example](../../../../../../examples/extension/atomic_operations/README_en.md).

## Related APIs

- [`asc::atomic_ref`](atomic_ref.md)
- [API list for this header](asc_atomic.md)
