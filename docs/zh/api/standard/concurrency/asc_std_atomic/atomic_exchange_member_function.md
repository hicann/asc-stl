# asc::std::atomic::exchange

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

`asc::std::atomic::exchange` 原子地替换当前值并返回旧值。

该接口的可用位置为 Host、AI Core SIMT 编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

```cpp
T asc::std::atomic::exchange(T value, memory_order order) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `order` | 输入 | 参与本次原子读取、写入或读改写操作的值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回旧值。 |

## 约束说明

- 标准整数/字符owning atomic别名及列出自由函数
- bool/8/16位用32位内部存储
- 32/64位按有符号位模式分派
- Host 和 AI Core SIMT 编程 GM

## 调用示例

以下 Host 片段演示原子操作；设备端对象须放在本页规定的有效内存空间。

```cpp
#include <asc/std/atomic>

decltype(auto) example(asc::std::atomic<int>& value)
{
    return value.exchange(1, asc::std::memory_order_relaxed);
}
```
