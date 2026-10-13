# asc::std::unique_lock::unique_lock

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

`asc::std::unique_lock::unique_lock`按本页所列构造形态初始化`unique_lock`对象。

标准语义参考：[cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex)。

## 函数原型

### 原型1

```cpp
unique_lock(Mutex& mutex);
```

### 原型2

```cpp
unique_lock(Mutex& mutex, adopt_lock_t tag) noexcept;
```

### 原型3

```cpp
unique_lock(Mutex& mutex, defer_lock_t tag) noexcept;
```

### 原型4

```cpp
unique_lock(Mutex& mutex, try_to_lock_t tag);
```

### 原型5

```cpp
unique_lock(unique_lock<Mutex>&& mutex) noexcept;
```

### 原型6

```cpp
constexpr unique_lock() noexcept;
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mutex` | 输入/输出 | 被关联的互斥体对象；构造时对其加锁，锁所有权由本对象持有。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mutex` | 输入/输出 | 当前线程已持有锁的互斥体对象；构造后由本对象接管该锁所有权。 |
| `tag` | 输入 | adopt_lock_t标记，写作asc::std::adopt_lock；表示接管调用线程已持有的锁。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mutex` | 输入/输出 | 被关联但不在构造时加锁的互斥体对象；构造后尚未持有锁。 |
| `tag` | 输入 | defer_lock_t标记，写作asc::std::defer_lock；表示暂不加锁。 |

### 原型4的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mutex` | 输入/输出 | 尝试加锁的互斥体对象；构造时以try_lock非阻塞地尝试取得锁。 |
| `tag` | 输入 | try_to_lock_t标记，写作asc::std::try_to_lock；表示尝试加锁而不阻塞。 |

### 原型5的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mutex` | 输入/输出 | 被移动构造的另一unique_lock对象；移动后其不再关联互斥体、不持有锁。 |

### 原型6的参数

无参数。

## 返回值说明

无返回值。

## 约束说明

- unique_lock<Mutex>的mutex_type，default/普通/defer/try/adopt构造、删除copy、move构造/赋值和析构。
- 有效状态上的lock/try_lock/unlock/swap/release/mutex/owns_lock/operator bool及非成员swap。
- 显式非抛Device Lockable域。
- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/mutex>
#include <mutex>

bool example()
{
    ::std::mutex mutex;
    asc::std::unique_lock<::std::mutex> guard(mutex, asc::std::defer_lock);
    guard.lock();
    const bool owned = guard.owns_lock();
    guard.unlock();
    return owned && !guard.owns_lock();
}
```

## 关联API

- [本头文件的接口列表](asc_std_mutex.md)
