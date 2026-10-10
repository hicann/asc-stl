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

`asc::std::scoped_lock` 按对象生命周期管理调用方提供的锁。

标准语义参考：[cppreference `mutex`](https://en.cppreference.com/w/cpp/header/mutex)。

## 声明

### 原型 1

```cpp
template<class ...MutexTypes> class asc::std::scoped_lock
```

### 原型 2

```cpp
template<class Mutex> class asc::std::scoped_lock
```

## 约束说明

- lock_guard<Mutex>的普通/adopt构造、mutex_type、删除copy及析构
- scoped_lock<>和scoped_lock<Mutex>的普通/adopt构造、删除copy及析构
- 仅显式Mutex的lock/unlock在当前执行空间有效且调用满足adopt前置条件的域
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下片段用具体模板实参实例化类型；实际对象仍须满足本页构造与生命周期约束。

```cpp
#include <asc/std/mutex>

struct example_mutex { void lock() {} bool try_lock() { return true; } void unlock() {} void lock_shared() {} bool try_lock_shared() { return true; } void unlock_shared() {} };
void use_type()
{
    using selected = asc::std::scoped_lock<example_mutex>;
    (void)sizeof(selected);
}
```
