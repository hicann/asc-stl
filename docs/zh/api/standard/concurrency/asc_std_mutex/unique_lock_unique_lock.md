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

`asc::std::unique_lock::unique_lock` 按本页所列构造形态初始化 `unique_lock` 对象。

标准语义参考：[cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex)。

## 函数原型

### 原型 1

```cpp
unique_lock(Mutex& mutex);
```

### 原型 2

```cpp
unique_lock(Mutex& mutex, adopt_lock_t tag) noexcept;
```

### 原型 3

```cpp
unique_lock(Mutex& mutex, defer_lock_t tag) noexcept;
```

### 原型 4

```cpp
unique_lock(Mutex& mutex, try_to_lock_t tag);
```

### 原型 5

```cpp
unique_lock(unique_lock<Mutex>&& mutex) noexcept;
```

### 原型 6

```cpp
constexpr unique_lock() noexcept;
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mutex` | 输入/输出 | 提供“按本页所列构造形态初始化 `unique_lock` 对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mutex` | 输入/输出 | 提供“按本页所列构造形态初始化 `unique_lock` 对象”使用的对象引用；被引用对象须在调用期间有效。 |
| `tag` | 输入 | 提供“按本页所列构造形态初始化 `unique_lock` 对象”所需的输入对象；类型须满足所选原型约束。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mutex` | 输入/输出 | 提供“按本页所列构造形态初始化 `unique_lock` 对象”使用的对象引用；被引用对象须在调用期间有效。 |
| `tag` | 输入 | 提供“按本页所列构造形态初始化 `unique_lock` 对象”所需的输入对象；类型须满足所选原型约束。 |

### 原型 4 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mutex` | 输入/输出 | 提供“按本页所列构造形态初始化 `unique_lock` 对象”使用的对象引用；被引用对象须在调用期间有效。 |
| `tag` | 输入 | 提供“按本页所列构造形态初始化 `unique_lock` 对象”所需的输入对象；类型须满足所选原型约束。 |

### 原型 5 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mutex` | 输入/输出 | 提供“按本页所列构造形态初始化 `unique_lock` 对象”使用的对象引用；被引用对象须在调用期间有效。 |

### 原型 6 的参数

无参数。

## 约束说明

- unique_lock<Mutex>的mutex_type，default/普通/defer/try/adopt构造、删除copy、move构造/赋值和析构
- 有效状态上的lock/try_lock/unlock/swap/release/mutex/owns_lock/operator bool及非成员swap
- 显式非抛Device Lockable域
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下 Host 片段使用标准锁对象演示调用；调用方须遵守锁的所有权和生命周期约束。

```cpp
#include <asc/std/mutex>

#include <mutex>

void example()
{
    asc::std::unique_lock<::std::mutex> guard{};
    (void)guard.owns_lock();
}
```
