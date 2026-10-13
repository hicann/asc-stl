# asc::execution_requirements

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

头文件路径为：`<asc/execution.require.h>`。

`asc::execution_requirements`保存确定性、输出顺序和相同键值处理规则三个执行要求。默认值分别为`not_guaranteed`、`unsorted`和`unspecified`。

该接口的可用位置为Host。

## 声明

```cpp
namespace asc {
class execution_requirements;
} // namespace asc
```

## 约束说明

- 对象为不可变值。
- 默认采用determinism::not_guaranteed、output_ordering::unsorted和tie_break::unspecified。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/execution.require.h>

bool example()
{
    asc::execution_requirements requirements;
    return requirements.determinism_value() == asc::determinism::not_guaranteed
        && requirements.output_ordering_value() == asc::output_ordering::unsorted
        && requirements.tie_break_value() == asc::tie_break::unspecified;
}
```

## 关联API

- [本头文件的接口列表](asc_execution_require_h.md)
