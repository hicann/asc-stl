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

头文件路径为：`<asc/std/mutex>`、`<asc/std/shared_mutex>`、`<asc/std/utility>`。

`asc::std::swap` 交换两个锁包装器保存的锁与所有权状态。

标准语义参考：[cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex)。

## 函数原型

### 原型 1

```cpp
template<class Mutex> constexpr void asc::std::swap(shared_lock<Mutex>& left, shared_lock<Mutex>& right) noexcept;
```

此原型对应头文件：`<asc/std/shared_mutex>`。

### 原型 2

```cpp
template<class Mutex> constexpr void asc::std::swap(unique_lock<Mutex>& left, unique_lock<Mutex>& right) noexcept;
```

此原型对应头文件：`<asc/std/mutex>`、`<asc/std/shared_mutex>`。

### 原型 3

```cpp
template<class T, size_t N> constexpr enable_if_t<Detectadlswa::Hasnoadlswaparray<T, N>::value&& Isswappable<T>::value> asc::std::swap(T (&left)[N], T (&right)[N]) noexcept(Isnothrowswappable<T>::value);
```

此原型对应头文件：`<asc/std/utility>`。

### 原型 4

```cpp
template<class T> constexpr Swapresultt<T> asc::std::swap(T& left, type_identity_t<T>& right) noexcept(is_nothrow_move_constructible_v<T>&& is_nothrow_move_assignable_v<T>);
```

此原型对应头文件：`<asc/std/utility>`。

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Mutex` | 被交换锁包装器所管理的互斥体类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入/输出 | 参与交换的左侧 shared_lock 对象；交换后接管对方原持有的锁所有权。 |
| `right` | 输入/输出 | 参与交换的右侧 shared_lock 对象；交换后接管对方原持有的锁所有权。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Mutex` | 被交换锁包装器所管理的互斥体类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入/输出 | 参与交换的左侧 unique_lock 对象；交换后接管对方原持有的锁所有权。 |
| `right` | 输入/输出 | 参与交换的右侧 unique_lock 对象；交换后接管对方原持有的锁所有权。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 数组元素类型，须可交换（is_swappable_v<T> 为 true）。 |
| `N` | 数组长度，编译期常量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入/输出 | 参与交换的左侧等长数组；按元素逐个交换。 |
| `right` | 输入/输出 | 参与交换的右侧等长数组；按元素逐个交换。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 参与交换的值类型，须可移动构造与移动赋值。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入/输出 | 参与交换的左侧对象；交换后取 right 的原值。 |
| `right` | 输入/输出 | 参与交换的右侧对象；交换后取 left 的原值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `void` | 无返回值。 |
| 原型 2 | `void` | 无返回值。 |
| 原型 3 | `enable_if_t<Detectadlswa::Hasnoadlswaparray<T, N>::value && Isswappable<T>::value>` | 返回交换或复制构造规则选定的结果对象。 |
| 原型 4 | `Swapresultt<T>` | 返回交换或复制构造规则选定的结果对象。 |

## 约束说明

- shared_lock<Mutex>的mutex_type，default/普通/defer/try/adopt构造、删除copy、move构造/赋值和析构
- 有效状态上的lock/try_lock/unlock/swap/release/mutex/owns_lock/operator bool及非成员swap
- 显式非抛Device SharedLockable域
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程
- unique_lock<Mutex>的mutex_type，default/普通/defer/try/adopt构造、删除copy、move构造/赋值和析构
- 显式非抛Device Lockable域
- 遵循标准约束
- forward_like 保留 const/volatile 限定和值类别

## 调用示例

以下 Host 片段用满足 Lockable 操作的示例对象展示调用。

```cpp
#include <asc/std/mutex>

void example()
{
    struct simple_mutex { void lock() {} bool try_lock() { return true; } void unlock() {} };
    simple_mutex first_mutex;
    simple_mutex second_mutex;
    asc::std::unique_lock<simple_mutex> first(first_mutex, asc::std::defer_lock);
    asc::std::unique_lock<simple_mutex> second(second_mutex, asc::std::defer_lock);
    asc::std::swap(first, second);
}
```
