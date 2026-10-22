# asc::barrier_arrival_token

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

Header: `<asc/barrier>`.

`asc::barrier_arrival_token` denotes the phase that a barrier arrival operation belongs to, for use by a subsequent wait.

## Declaration

```cpp
namespace asc {
class barrier_arrival_token;
}  // namespace asc
```

## Constraints

- The token must come from one arrival at the same barrier and be waited on in the corresponding phase; it holds only phase information and does not own the shared GM state.
- The token is copyable by value, and wait accepts an rvalue reference; for the shared barrier object and the participants' progress requirements, see the owning barrier page.

## Example

This snippet shows that an arrival token is used only for its corresponding barrier phase. After the single participating thread completes that phase, the Host, after synchronizing, should read output[0] as 1; multiple participants must jointly honor the barrier count.

```cpp
#include <asc/barrier>
#include <asc/std/new>

__global__ void example(void* storage, unsigned int* output)
{
    // Launched with a single thread; the Host provides aligned GM storage for the barrier.
    using Barrier = asc::barrier<asc::memory_scope::device>;
    auto* barrier = new (storage) Barrier(1);
    asc::barrier_arrival_token token = barrier->arrive();
    barrier->wait(static_cast<asc::barrier_arrival_token&&>(token));
    output[0] = 1;
}
```

For the complete project and run steps, see the [atomic_operations example](../../../../../zh/examples/atomic_operations/README.md).

## Related APIs

- [API list for this header](asc_barrier.md)
