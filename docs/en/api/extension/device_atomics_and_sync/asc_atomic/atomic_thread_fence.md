# asc::atomic_thread_fence

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

`asc::atomic_thread_fence` establishes a thread fence with the specified memory order and scope in AI Core SIMT programming; `relaxed` performs no fence, and `release` establishes release ordering.

## Function Prototype

```cpp
namespace asc {
void atomic_thread_fence(asc::std::memory_order order, asc::memory_scope scope) noexcept;
} // namespace asc
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `order` | Input | Accepts only `memory_order_relaxed` (no operation) or `memory_order_release` (release fence); other values are not supported. |
| `scope` | Input | Selects `asc::memory_scope::block` or `asc::memory_scope::device`, denoting the thread-block or device scope respectively. |

## Return Value

No return value.

## Constraints

- Can only be called in AI Core SIMT programming.
- order is relaxed or release only, and scope is block or device only.

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
    asc::atomic_thread_fence(asc::std::memory_order_release, asc::memory_scope::device);
    output[0] = (cell.load(asc::std::memory_order_relaxed) == 7) ? 1U : 0U;
}
```

For the complete project and run steps, see the [atomic_operations example](../../../../../zh/examples/atomic_operations/README.md).

## Related APIs

- [API list for this header](asc_atomic.md)
