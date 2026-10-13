# asc::atomic::atomic

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

头文件路径为：`<asc/atomic>`。

`asc::atomic::atomic` 使用调用方提供的参数初始化 `asc::atomic` 对象。

该接口的可用位置为 AI Core SIMT 编程。

## 函数原型

### 原型 1

```cpp
asc::atomic::atomic() noexcept;
```

### 原型 2

```cpp
explicit asc::atomic::atomic(T desired) noexcept;
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `desired` | 输入 | 对象初值：以该值初始化原子对象的内部存储。 |

## 约束说明

- 原子对象的类型、地址空间、作用域和内存序必须匹配
- Device 作用域的 64 位对象位于 GM，UB 原子操作仅使用 memory_order_relaxed

## 调用示例

以下 AI Core SIMT 片段在调用方提供的 GM 存储中构造对象；存储生命周期须覆盖所有并发访问。

```cpp
#include <asc/atomic>

#include <asc/std/new>

__aicore__ void example(asc::atomic<int>* gm_storage)
{
    // gm_storage 指向调用方提供、对齐且尚未构造对象的 GM 存储。
    ::new (static_cast<void*>(gm_storage)) asc::atomic<int>(0);
}
```
