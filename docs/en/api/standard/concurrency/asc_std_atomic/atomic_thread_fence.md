# asc::std::atomic_thread_fence

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

Header: `<asc/std/atomic>`.

`asc::std::atomic_thread_fence` establishes inter-thread ordering constraints on atomic memory operations at the specified scope.

This interface is available in Host and AI Core SIMT programming.

Standard semantics reference: [cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic).

## Function Prototype

```cpp
namespace asc::std {
void atomic_thread_fence(memory_order order) noexcept;
} // namespace asc::std
```

## Parameters

**Function Parameters**

| Parameter | Input/Output | Description |
| --- | --- | --- |
| `order` | Input | The memory order of the fence; it establishes ordering constraints between atomic accesses for the current thread, such as acquire, release, or seq_cst. |

## Return Value

No return value.

## Constraints

- atomic_thread_fence: Host supports all standard memory_order values.
- On the device, pure SIMT supports relaxed/release, where release is a compiler barrier + asc_threadfence.

## Example

The following snippet demonstrates the basic call form of the interface on this page; inputs and the execution context must satisfy the constraints on this page.

```cpp
#include <asc/std/atomic>
#include <thread>

bool example()
{
    int payload = 0;
    asc::std::atomic<bool> ready{false};
    ::std::thread producer([&] {
        payload = 42;
        asc::std::atomic_thread_fence(asc::std::memory_order_release);
        ready.store(true, asc::std::memory_order_relaxed);
    });
    while (!ready.load(asc::std::memory_order_relaxed))
        ::std::this_thread::yield();
    asc::std::atomic_thread_fence(asc::std::memory_order_acquire);
    const bool observed = payload == 42;
    producer.join();
    return observed;
}
```

## Related APIs

- [API list for this header](asc_std_atomic.md)
