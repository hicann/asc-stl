# asc::std::scoped_lock

## 产品支持情况

<!-- npu="950" id1 -->
- Ascend 950PR&950DT系列产品：支持
<!-- end id1 -->
<!-- npu="A3" id2 -->
- Atlas A3系列产品：不支持
<!-- end id2 -->
<!-- npu="910b" id3 -->
- Atlas A2系列产品：不支持
<!-- end id3 -->
<!-- npu="310b" id4 -->
- Atlas 200I/500 A2推理产品：不支持
<!-- end id4 -->
<!-- npu="310p" id5 -->
- Atlas推理系列产品AI Core：不支持
<!-- end id5 -->
<!-- npu="310p" id6 -->
- Atlas推理系列产品Vector Core：不支持
<!-- end id6 -->
<!-- npu="910" id7 -->
- Atlas训练系列产品：不支持
<!-- end id7 -->

## 功能说明

头文件路径为：`<asc/std/mutex>`。

`asc::std::scoped_lock`按对象生命周期管理调用方提供的锁。

标准语义参考：[cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex)。

## 声明

### 原型1

```cpp
namespace asc::std {
template<class ...MutexTypes> class scoped_lock;
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class Mutex> class scoped_lock;
} // namespace asc::std
```

## 约束说明

- lock_guard<Mutex>的普通/adopt构造、mutex_type、删除copy及析构。
- scoped_lock<>和scoped_lock<Mutex>的普通/adopt构造、删除copy及析构。
- 仅显式Mutex的lock/unlock在当前执行空间有效且调用满足adopt前置条件的域。
- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/mutex>

struct Mutex {
    bool locked = false;
    void lock() { locked = true; }
    bool try_lock() { if (locked) return false; locked = true; return true; }
    void unlock() { locked = false; }
    void lock_shared() { lock(); }
    bool try_lock_shared() { return try_lock(); }
    void unlock_shared() { unlock(); }
};

bool example()
{
    Mutex mutex;
    {
        asc::std::scoped_lock<Mutex> lock(mutex);
        if (!mutex.locked) return false;
    }
    return !mutex.locked;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mutex.md)
