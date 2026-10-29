# asc::std::try_to_lock

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

`asc::std::try_to_lock`标记构造时尝试获取锁但不阻塞的形式。

标准语义参考：[cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex)。

## 声明

```cpp
namespace asc::std {
inline constexpr const try_to_lock_t try_to_lock;
} // namespace asc::std
```

## 约束说明

- defer_lock_t、try_to_lock_t、adopt_lock_t及对应defer_lock、try_to_lock、adopt_lock三个inline constexpr对象。
- 纯类型与对象，不拥有或操作锁。
- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

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
    lock_type guard(mutex, asc::std::try_to_lock);
    return guard.owns_lock() && mutex.locked;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mutex.md)
