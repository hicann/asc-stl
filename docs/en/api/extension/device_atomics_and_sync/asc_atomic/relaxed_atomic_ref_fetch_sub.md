# asc::relaxed_atomic_ref::fetch_sub

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

`asc::relaxed_atomic_ref::fetch_sub` atomically subtracts the operand and returns the value before the modification.

## Function Prototype

Member of: [`asc::relaxed_atomic_ref`](relaxed_atomic_ref.md).

```cpp
// Excerpt of the declaration inside the asc::relaxed_atomic_ref class; template parameters and other members are provided by the owning class.
T fetch_sub(T operand) const noexcept;
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `operand` | Input | The value that participates in this atomic read, write, or read-modify-write operation. |

## Return Value

| Return type | Description |
| --- | --- |
| `T` | Returns the value before the modification. |

## Constraints

- The underlying unit must be located in GM; atomic operations on UB or thread-private storage are not provided; the fixed relaxed memory order carries no cross-object synchronization.

- Can only be called in AI Core SIMT programming.
- T must be an exact 32-bit or 64-bit signed or unsigned integer type; the underlying object must be initialized and satisfy its natural alignment.
- The reference does not own the object; the underlying storage must remain valid until all concurrent accesses have finished, and participants must not mix in non-atomic accesses.
- This interface uses the relaxed memory order and carries no release or acquire synchronization for reads and writes of other objects.

## Example

The following SIMT kernel initializes and accesses one GM atomic unit from a single thread; there is no other concurrent access, and output[0] is expected to be 1. The Host must read the result after the kernel completes.

```cpp
#include <asc/atomic>
#include <asc/std/new>

__global__ void example(int* storage, unsigned int* output)
{
    // Only 1 block and 1 thread are launched; storage and output are both Host-allocated GM.
    *storage = 7;
    asc::relaxed_atomic_ref<int> cell(*storage);
    cell.store(7);
    const int previous = cell.fetch_sub(3);
    output[0] = (previous == 7 && cell.load() == 4) ? 1U : 0U;
}
```

For the complete project and run steps, see the [atomic_operations example](../../../../../../examples/extension/atomic_operations/README_en.md).

## Related APIs

- [`asc::relaxed_atomic_ref`](relaxed_atomic_ref.md)
- [API list for this header](asc_atomic.md)
