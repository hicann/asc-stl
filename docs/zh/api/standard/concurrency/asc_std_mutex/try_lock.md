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

### 原型1

```cpp
namespace asc::std {
template<class FirstMutex, class SecondMutex, class ThirdMutex, class ...RestMutexes> int try_lock(FirstMutex& mutexes, SecondMutex& mutex, ThirdMutex& mutex, RestMutexes&... mutex);
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class FirstMutex, class SecondMutex> int try_lock(FirstMutex& mutexes, SecondMutex& mutex);
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `FirstMutex` | 第一把待尝试锁定的Lockable类型。 |
| `SecondMutex` | 第二把待尝试锁定的Lockable类型。 |
| `ThirdMutex` | 第三把待尝试锁定的Lockable类型。 |
| `RestMutexes` | 其余待尝试锁定的Lockable类型列表。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mutexes` | 输入/输出 | 提供“依次尝试获取多把调用方提供的锁，并返回失败位置”使用的对象引用；被引用对象须在调用期间有效。 |
| `mutex` | 输入/输出 | 提供“依次尝试获取多把调用方提供的锁，并返回失败位置”使用的对象引用；被引用对象须在调用期间有效。 |
| `mutex` | 输入/输出 | 提供“依次尝试获取多把调用方提供的锁，并返回失败位置”使用的对象引用；被引用对象须在调用期间有效。 |
| `mutex` | 输入/输出 | 提供“依次尝试获取多把调用方提供的锁，并返回失败位置”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `FirstMutex` | 第一把待尝试锁定的Lockable类型。 |
| `SecondMutex` | 第二把待尝试锁定的Lockable类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mutexes` | 输入/输出 | 提供“依次尝试获取多把调用方提供的锁，并返回失败位置”使用的对象引用；被引用对象须在调用期间有效。 |
| `mutex` | 输入/输出 | 提供“依次尝试获取多把调用方提供的锁，并返回失败位置”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `int` | 返回失败位置。 |
| 原型2 | `int` | 返回失败位置。 |

## 约束说明

- 两个及以上显式非抛Device Lockable的asc::std::try_lock：按参数顺序尝试，成功返回-1，失败返回零基索引并回滚此前已获得的全部锁。
- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host片段用满足Lockable操作的示例对象展示调用。

```cpp
#include <asc/std/mutex>

void example()
{
    struct simple_mutex { void lock() {} bool try_lock() { return true; } void unlock() {} };
    simple_mutex first;
    simple_mutex second;
    if (asc::std::try_lock(first, second) == -1) {
        first.unlock();
        second.unlock();
    }
}
```

## 关联API

- [本头文件的接口列表](asc_std_mutex.md)
