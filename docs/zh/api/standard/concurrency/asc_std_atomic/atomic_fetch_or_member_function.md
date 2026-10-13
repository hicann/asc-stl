# asc::std::atomic::fetch_or

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

`asc::std::atomic::fetch_or`原子执行按位或并返回修改前的值。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `atomic`](https://en.cppreference.com/w/cpp/header/atomic)。

## 函数原型

所属类型：[`asc::std::atomic`](atomic.md)。

```cpp
// asc::std::atomic 类内的声明节选；模板形参和其他成员由所属类提供。
T fetch_or(T value, memory_order order) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 与原子对象当前值做按位或的操作数；返回修改前的值。 |
| `order` | 输入 | 读改写所用内存序，决定本次操作的可见性顺序；可取memory_order各枚举值。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回修改前的值。 |

## 约束说明

- 标准整数/字符owning atomic别名及列出自由函数。
- bool/8/16位用32位内部存储。
- 32/64位按有符号位模式分派。
- Host和AI Core SIMT编程GM。

## 调用示例

以下Host片段演示原子操作；设备端对象须放在本页规定的有效内存空间。

```cpp
#include <asc/std/atomic>

decltype(auto) example(asc::std::atomic<int>& value)
{
    return value.fetch_or(1, asc::std::memory_order_relaxed);
}
```

## 关联API

- [`asc::std::atomic`](atomic.md)
- [本头文件的接口列表](asc_std_atomic.md)
