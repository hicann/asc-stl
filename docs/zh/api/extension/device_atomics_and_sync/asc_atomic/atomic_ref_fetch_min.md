# asc::atomic_ref::fetch_min

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

`asc::atomic_ref::fetch_min` 原子更新为当前值与操作数中的较小值并返回旧值。

该接口的可用位置为 AI Core SIMT 编程。

## 函数原型

```cpp
T asc::atomic_ref::fetch_min(T operand, asc::std::memory_order order = asc::std::memory_order_seq_cst) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `operand` | 输入 | 提供“原子更新为当前值与操作数中的较小值并返回旧值”所需的输入对象；类型须满足所选原型约束。 |
| `order` | 输入 | 提供“原子更新为当前值与操作数中的较小值并返回旧值”所需的输入对象；类型须满足所选原型约束。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回旧值。 |

## 约束说明

- 原子对象的类型、地址空间、作用域和内存序必须匹配
- Device 作用域的 64 位对象位于 GM，UB 原子操作仅使用 memory_order_relaxed

## 调用示例

以下 AI Core SIMT 片段使用调用方管理的 GM 原子单元；初始化与并发访问须满足本页约束。

```cpp
#include <asc/atomic>
#include <asc/std/array>
#include <asc/std/cstddef>
#include <asc/std/cstdint>
#include <asc/std/iterator>
#include <asc/std/type_traits>
#include <asc/std/utility>

__aicore__ decltype(auto) example(int* gm_cell)
{
    // gm_cell 指向调用方管理的 GM 整数单元。
    asc::atomic_ref<int> value(*gm_cell);
    return value.fetch_min(1, asc::std::memory_order_relaxed);
}
```
