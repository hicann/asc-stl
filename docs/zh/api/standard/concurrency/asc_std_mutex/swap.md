# asc::std::swap

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

头文件路径为：`<asc/std/mutex>`、`<asc/std/shared_mutex>`。

`asc::std::swap`交换两个锁包装器保存的锁与所有权状态。

标准语义参考：[cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex)。

## 函数原型

```cpp
namespace asc::std {
template<class Mutex>
void swap(unique_lock<Mutex>& left, unique_lock<Mutex>& right) noexcept;
}
```

以上由`<asc/std/mutex>`提供。

```cpp
namespace asc::std {
template<class Mutex>
void swap(shared_lock<Mutex>& left, shared_lock<Mutex>& right) noexcept;
}
```

以上由`<asc/std/shared_mutex>`提供。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Mutex` | 两个锁包装器关联的同一种底层互斥体类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入/输出 | 左侧锁包装器，其互斥体指针及所有权状态与right交换。 |
| `right` | 输入/输出 | 右侧锁包装器；两个对象及各自关联的底层互斥体在调用期间有效。 |

## 返回值说明

无返回值。只交换包装器的指针及所有权状态，不对底层互斥体执行加锁或解锁。

## 约束说明

- 可以交换空锁包装器或未持锁包装器；操作仅交换指针和所有权状态，不改变互斥体本身的锁定状态。
- 底层Mutex对象须在相应包装器持有期间存活，并支持该包装器对应执行位置上的Lockable或SharedLockable操作。

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
    simple_mutex a, b;
    asc::std::unique_lock<simple_mutex> left(a);
    asc::std::unique_lock<simple_mutex> right(b, asc::std::defer_lock);
    asc::std::swap(left, right);
    const bool transferred = !left.owns_lock() && left.mutex() == &b &&
        right.owns_lock() && right.mutex() == &a && a.locked && !b.locked;
    right.unlock();
    return transferred && !a.locked;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mutex.md)
