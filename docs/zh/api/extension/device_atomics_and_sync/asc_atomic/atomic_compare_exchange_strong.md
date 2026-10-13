# asc::atomic::compare_exchange_strong

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

`asc::atomic::compare_exchange_strong` 比较当前值与 expected，相等时写入 desired，否则回写实际值。

该接口的可用位置为 AI Core SIMT 编程。

## 函数原型

```cpp
bool asc::atomic::compare_exchange_strong(T& expected, T desired, asc::std::memory_order success, asc::std::memory_order failure) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `expected` | 输入/输出 | 提供预期值或目标值；比较失败时函数把观察到的当前原子值写入 `expected`；strong 形式不允许伪失败，仅在实际比较失败时返回 `false`。 |
| `desired` | 输入 | 比较相等时写入原子对象的目标值。 |
| `success` | 输入 | 比较交换成功分支使用的内存序，约束交换写入的可见性顺序。 |
| `failure` | 输入 | 比较交换失败分支（仅读取）使用的内存序；不得为 release 或 acq_rel。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

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

__aicore__ decltype(auto) example(asc::atomic<int>* cell)
{
    // cell 指向调用方已构造的 GM 原子对象。
    int expected = 1;
    return cell->compare_exchange_strong(expected, 2, asc::std::memory_order_relaxed, asc::std::memory_order_relaxed);
}
```
