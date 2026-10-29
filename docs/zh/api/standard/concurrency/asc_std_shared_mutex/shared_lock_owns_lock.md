# asc::std::shared_lock::owns_lock

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

头文件路径为：`<asc/std/shared_mutex>`。

`asc::std::shared_lock::owns_lock`判断包装器是否持有底层Lockable对象。

标准语义参考：[cppreference `shared_mutex`](https://en.cppreference.com/w/cpp/header/shared_mutex)。

## 函数原型

所属类型：[`asc::std::shared_lock`](shared_lock.md)。

```cpp
// asc::std::shared_lock 类内的声明节选；模板形参和其他成员由所属类提供。
bool owns_lock() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- shared_lock<Mutex>的mutex_type，default/普通/defer/try/adopt构造、删除copy、move构造/赋值和析构。
- 有效状态上的lock/try_lock/unlock/swap/release/mutex/owns_lock/operator bool及非成员swap。
- 显式非抛Device SharedLockable域。
- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host片段使用标准锁对象演示调用；调用方须遵守锁的所有权和生命周期约束。

```cpp
#include <asc/std/shared_mutex>
#include <new>

// Instrumented single-thread BasicLockable used to observe adapter ownership.
struct example_mutex {
    bool locked = false;
    int unlocks = 0;
    void lock()
    {
        locked = true;
    }
    bool try_lock()
    {
        if (locked)
            return false;
        locked = true;
        return true;
    }
    void unlock()
    {
        locked = false;
        ++unlocks;
    }
    void lock_shared()
    {
        lock();
    }
    bool try_lock_shared()
    {
        return try_lock();
    }
    void unlock_shared()
    {
        unlock();
    }
};

bool example()
{
    using lock_type = asc::std::shared_lock<example_mutex>;
    example_mutex mutex;
    lock_type guard(mutex, asc::std::defer_lock);
    const bool deferred = !guard.owns_lock();
    guard.lock();
    return deferred && guard.owns_lock();
}
```

## 关联API

- [`asc::std::shared_lock`](shared_lock.md)
- [本头文件的接口列表](asc_std_shared_mutex.md)
