# asc::std::try_lock

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

`asc::std::try_lock`依次尝试获取多把调用方提供的锁，并返回失败位置。

标准语义参考：[cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex)。

## 函数原型

```cpp
namespace asc::std {
template<class... Mutexes> int try_lock(Mutexes&... mutexes);
}
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Mutexes...` | 两个或更多满足当前执行位置Lockable要求且操作不抛出的互斥体类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mutexes...` | 输入/输出 | 按尝试顺序给出的有效互斥体对象；失败时回滚本次调用已取得的锁，原先由其他参与者持有的锁不受影响。 |

## 返回值说明

返回int。全部获取成功时为-1；失败时返回首个获取失败互斥体的零基索引，并释放本次调用此前已取得的全部锁。

## 约束说明

- 参数包至少包含两个Mutex对象，每个对象须支持适用执行位置上的try_lock()和unlock()，且这些操作不抛出异常；失败时释放本次调用已取得的锁。

- 两个及以上显式非抛Device Lockable的asc::std::try_lock：按参数顺序尝试，成功返回-1，失败返回零基索引并回滚此前已获得的全部锁。
- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例给出具体锁状态，并检查操作结果。

```cpp
#include <asc/std/mutex>

struct simple_mutex {
    bool locked = false;
    void lock() { locked = true; }
    bool try_lock() { if (locked) return false; locked = true; return true; }
    void unlock() { locked = false; }
};

bool example()
{
    simple_mutex first, second;
    second.lock();
    const int failed = asc::std::try_lock(first, second);
    if (failed != 1 || first.locked || !second.locked) return false;
    second.unlock();
    const int acquired = asc::std::try_lock(first, second);
    const bool both = acquired == -1 && first.locked && second.locked;
    if (first.locked) first.unlock();
    if (second.locked) second.unlock();
    return both;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mutex.md)
