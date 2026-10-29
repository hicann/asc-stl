# asc::std::unique_lock::lock

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

`asc::std::unique_lock::lock`获取调用方提供的Lockable对象所有权。

标准语义参考：[cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex)。

## 函数原型

所属类型：[`asc::std::unique_lock`](unique_lock.md)。

```cpp
// asc::std::unique_lock 类内的声明节选；模板形参和其他成员由所属类提供。
void lock();
```

## 参数说明

无参数。

## 返回值说明

无返回值。

## 约束说明

- Device自旋等待须保证锁持有者能并发推进；不能由等待者持续占用同一调度组而阻止持有者执行。自定义Mutex须满足相应执行模型的前进保证。

- 底层Mutex对象必须存活且已与包装器关联。lock或try_lock要求当前包装器尚未持有锁；默认构造或release后的空包装器不能直接加锁。

- unique_lock<Mutex>的mutex_type，default/普通/defer/try/adopt构造、删除copy、move构造/赋值和析构。
- 有效状态上的lock/try_lock/unlock/swap/release/mutex/owns_lock/operator bool及非成员swap。
- 显式非抛Device Lockable域。
- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host片段使用标准锁对象演示调用；调用方须遵守锁的所有权和生命周期约束。

```cpp
#include <asc/std/mutex>
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
    using lock_type = asc::std::unique_lock<example_mutex>;
    example_mutex mutex;
    lock_type guard(mutex, asc::std::defer_lock);
    guard.lock();
    const bool held = guard.owns_lock() && mutex.locked;
    guard.unlock();
    return held && !mutex.locked && mutex.unlocks == 1;
}
```

## 关联API

- [`asc::std::unique_lock`](unique_lock.md)
- [本头文件的接口列表](asc_std_mutex.md)
