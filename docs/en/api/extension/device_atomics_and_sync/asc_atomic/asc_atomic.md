# Header asc/atomic

Provides integer atomic operations on GM at the thread-block or device level, as well as GM references with a fixed relaxed memory order

## Usage

```cpp
#include <asc/atomic>
```

## API List

| API | Kind | C++ Mode | Availability | Product Support |
| --- | --- | --- | --- | --- |
| [asc::atomic](atomic.md) | Class template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::atomic](atomic_atomic.md) | Constructor | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::compare_exchange_strong](atomic_compare_exchange_strong.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::exchange](atomic_exchange.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_add](atomic_fetch_add.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_and](atomic_fetch_and.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_max](atomic_fetch_max.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_min](atomic_fetch_min.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_or](atomic_fetch_or.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_sub](atomic_fetch_sub.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::fetch_xor](atomic_fetch_xor.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::load](atomic_load.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic::store](atomic_store.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref](atomic_ref.md) | Class template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::atomic_ref](atomic_ref_atomic_ref.md) | Constructor | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::compare_exchange_strong](atomic_ref_compare_exchange_strong.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::exchange](atomic_ref_exchange.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_add](atomic_ref_fetch_add.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_and](atomic_ref_fetch_and.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_max](atomic_ref_fetch_max.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_min](atomic_ref_fetch_min.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_or](atomic_ref_fetch_or.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_sub](atomic_ref_fetch_sub.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::fetch_xor](atomic_ref_fetch_xor.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::load](atomic_ref_load.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_ref::store](atomic_ref_store.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::atomic_thread_fence](atomic_thread_fence.md) | Function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::memory_scope](memory_scope.md) | Enum | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::memory_scope::block](memory_scope_block.md) | Enumerator | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::memory_scope::device](memory_scope_device.md) | Enumerator | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref](relaxed_atomic_ref.md) | Class template | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::compare_exchange_strong](relaxed_atomic_ref_compare_exchange_strong.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::exchange](relaxed_atomic_ref_exchange.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::fetch_add](relaxed_atomic_ref_fetch_add.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::fetch_sub](relaxed_atomic_ref_fetch_sub.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::load](relaxed_atomic_ref_load.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::relaxed_atomic_ref](relaxed_atomic_ref_relaxed_atomic_ref.md) | Constructor | C++17+ | AI Core SIMT programming | Ascend 950 |
| [asc::relaxed_atomic_ref::store](relaxed_atomic_ref_store.md) | Member function | C++17+ | AI Core SIMT programming | Ascend 950 |
