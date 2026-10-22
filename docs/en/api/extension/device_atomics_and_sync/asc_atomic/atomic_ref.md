# asc::atomic_ref

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

`asc::atomic_ref` references an existing object in a non-owning way and provides atomic operations at the specified scope.

This interface is available in AI Core SIMT programming.

## Declaration

```cpp
namespace asc {
template <class T, asc::memory_scope Scope = asc::memory_scope::device>
class atomic_ref;
}  // namespace asc
```

## Constraints

- `T` must be exactly one of `asc::std::int32_t`, `uint32_t`, `int64_t`, or `uint64_t`; having the same width alone does not mean the type is accepted.
- The atomic unit must be initialized, naturally aligned, and located in GM visible to all participants; when accessed concurrently, it must not be mixed with ordinary reads and writes.
- atomic_ref does not own the unit; its underlying object must cover all uses of the reference and the concurrent operations, not only the construction call.

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

    output[0] = (cell.load(asc::std::memory_order_relaxed) == 7) ? 1U : 0U;
}
```

For the complete project and run steps, see the [atomic_operations example](../../../../../zh/examples/atomic_operations/README.md).

## Related APIs

- [API list for this header](asc_atomic.md)
