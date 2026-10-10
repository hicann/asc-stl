# 头文件 asc/atomic

提供作用于GM的线程块级或设备级整数原子操作，以及作用于UB的线程块级宽松整数原子操作

## 使用方式

```cpp
#include <asc/atomic>
```

## API 列表

| API | 类型 | C++ 模式 | 可用位置 | 产品支持 |
| --- | --- | --- | --- | --- |
| [asc::atomic](atomic.md) | 类模板 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic::atomic](atomic_atomic.md) | 构造函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic::compare_exchange_strong](atomic_compare_exchange_strong.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic::exchange](atomic_exchange.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic::fetch_add](atomic_fetch_add.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic::fetch_and](atomic_fetch_and.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic::fetch_max](atomic_fetch_max.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic::fetch_min](atomic_fetch_min.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic::fetch_or](atomic_fetch_or.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic::fetch_sub](atomic_fetch_sub.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic::fetch_xor](atomic_fetch_xor.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic::load](atomic_load.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic::store](atomic_store.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_ref](atomic_ref.md) | 类模板 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_ref::atomic_ref](atomic_ref_atomic_ref.md) | 构造函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_ref::compare_exchange_strong](atomic_ref_compare_exchange_strong.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_ref::exchange](atomic_ref_exchange.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_ref::fetch_add](atomic_ref_fetch_add.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_ref::fetch_and](atomic_ref_fetch_and.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_ref::fetch_max](atomic_ref_fetch_max.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_ref::fetch_min](atomic_ref_fetch_min.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_ref::fetch_or](atomic_ref_fetch_or.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_ref::fetch_sub](atomic_ref_fetch_sub.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_ref::fetch_xor](atomic_ref_fetch_xor.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_ref::load](atomic_ref_load.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_ref::store](atomic_ref_store.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::atomic_thread_fence](atomic_thread_fence.md) | 函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::memory_scope](memory_scope.md) | 枚举 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::memory_scope::block](memory_scope_block.md) | 枚举值 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::memory_scope::device](memory_scope_device.md) | 枚举值 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::relaxed_atomic_ref](relaxed_atomic_ref.md) | 类模板 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::relaxed_atomic_ref::compare_exchange_strong](relaxed_atomic_ref_compare_exchange_strong.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::relaxed_atomic_ref::exchange](relaxed_atomic_ref_exchange.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::relaxed_atomic_ref::fetch_add](relaxed_atomic_ref_fetch_add.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::relaxed_atomic_ref::fetch_sub](relaxed_atomic_ref_fetch_sub.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::relaxed_atomic_ref::load](relaxed_atomic_ref_load.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::relaxed_atomic_ref::relaxed_atomic_ref](relaxed_atomic_ref_relaxed_atomic_ref.md) | 构造函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
| [asc::relaxed_atomic_ref::store](relaxed_atomic_ref_store.md) | 成员函数 | C++17+ | AI Core SIMT 编程 | Ascend 950 |
