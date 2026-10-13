# asc::std::counting_semaphore::try_acquire

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

头文件路径为：`<asc/std/semaphore>`。

`asc::std::counting_semaphore::try_acquire`尝试消耗一个信号量许可并报告结果。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `semaphore`](https://en.cppreference.com/w/cpp/header/semaphore)。

## 函数原型

所属类型：[`asc::std::counting_semaphore`](counting_semaphore.md)。

```cpp
// asc::std::counting_semaphore 类内的声明节选；模板形参和其他成员由所属类提供。
bool try_acquire() noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- Host侧对象管理Ascend 950的GM状态。
- 所有参与者必须能够并发推进，带等待的操作还要求完成条件可被满足。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/semaphore>

bool example()
{
    asc::std::counting_semaphore<4> slots(1);
    slots.acquire();
    const bool empty = !slots.try_acquire();
    slots.release();
    return empty && slots.try_acquire() && slots.max() >= 1;
}
```

## 关联API

- [`asc::std::counting_semaphore`](counting_semaphore.md)
- [本头文件的接口列表](asc_std_semaphore.md)
