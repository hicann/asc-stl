# asc::output_ordering::unsorted

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

头文件路径为：`<asc/execution.output_ordering.h>`。

`asc::output_ordering::unsorted`表示不要求输出元素按排序关系排列。

该接口的可用位置为Host。

## 声明

所属类型：[`asc::output_ordering`](output_ordering.md)。

```cpp
// asc::output_ordering 类内的声明节选；模板形参和其他成员由所属类提供。
unsorted;
```

## 约束说明

- 仅提供三个取值。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/execution.output_ordering.h>

constexpr auto value = asc::output_ordering::unsorted;
static_assert(value != asc::output_ordering::sorted, "documented states are distinct");
static_assert(value != asc::output_ordering::stable_sorted, "documented states are distinct");
```

## 关联API

- [`asc::output_ordering`](output_ordering.md)
- [本头文件的接口列表](asc_execution_output_ordering_h.md)
