# asc::tie_break::prefer_larger_index

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

头文件路径为：`<asc/execution.tie_break.h>`。

`asc::tie_break::prefer_larger_index`要求多个位置同时满足条件时优先选择较大索引。

该接口的可用位置为Host。

## 声明

所属类型：[`asc::tie_break`](tie_break.md)。

```cpp
// asc::tie_break 类内的声明节选；模板形参和其他成员由所属类提供。
prefer_larger_index;
```

## 约束说明

- 当前并行极值前端尚未应用非默认索引偏好；保存该属性不保证相等极值按较小或较大索引选择。需要此规则时，调用方须显式处理相等元素。

- 仅提供三个取值。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/execution.tie_break.h>

constexpr auto value = asc::tie_break::prefer_larger_index;
static_assert(value != asc::tie_break::unspecified, "documented states are distinct");
static_assert(value != asc::tie_break::prefer_smaller_index, "documented states are distinct");
```

## 关联API

- [`asc::tie_break`](tie_break.md)
- [本头文件的接口列表](asc_execution_tie_break_h.md)
