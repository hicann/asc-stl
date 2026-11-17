# asc::std::atomic::fetch_add

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

头文件路径为：`<asc/std/atomic>`。

`asc::std::atomic::fetch_add`原子加上操作数并返回修改前的值。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

所属类型：[`asc::std::atomic`](atomic.md)。

```cpp
// asc::std::atomic 类内的声明节选；模板形参和其他成员由所属类提供。
T fetch_add(T value, memory_order order = memory_order_seq_cst) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 加到原子对象当前值上的操作数；返回修改前的值。 |
| `order` | 输入 | 读改写所用内存序，决定本次操作的可见性顺序；可取memory_order各枚举值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回修改前的值。 |

## 约束说明

- 原子操作可在Host和AI Core SIMT编程中调用；SIMT线程共享的原子对象须位于GM，并在并发访问前完成初始化。
- 读改写返回操作前的值；不带内存序参数的形式使用`memory_order_seq_cst`。

## 调用示例

并行分桶scatter可在工作线程启动前将每个桶的计数器初始化为0。每个有效元素通过`slot = counters[bucket].fetch_add(1, memory_order_relaxed)`预留唯一位置，再将自身索引写入该桶预分配的输出窗口。须保证容量足够且计数器不溢出。返回的位置不构成对随后payload写入的发布：应在线程join或kernel/stream完成后消费输出，或另建正确的发布同步协议。桶内到达顺序不确定，独立校验应比较每桶计数及元素多重集，而不要求保持输入顺序。

以下Host片段演示原子操作；设备端对象须放在本页规定的有效内存空间。

```cpp
#include <asc/std/atomic>

bool example()
{
    asc::std::atomic<int> value{5};
    const auto before = value.fetch_add(3, asc::std::memory_order_relaxed);
    return before == 5 && value.load() == 8;
}
```

## 关联API

- [`asc::std::atomic`](atomic.md)
- [本头文件的接口列表](asc_std_atomic.md)
