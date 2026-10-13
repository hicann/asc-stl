# asc::tie_break

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

`asc::tie_break`指定多个位置同时满足选择条件时采用的索引取舍规则。

该接口的可用位置为Host。

## 声明

```cpp
namespace asc {
enum class tie_break;
} // namespace asc
```

## 约束说明

- 仅提供三个取值。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/execution.require.h>

bool example()
{
    auto requirements = asc::require(asc::tie_break::unspecified);
    return requirements.tie_break_value() == asc::tie_break::unspecified;
}
```

## 关联API

- [本头文件的接口列表](asc_execution_tie_break_h.md)
