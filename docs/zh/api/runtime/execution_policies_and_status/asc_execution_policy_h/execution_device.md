# asc::execution::device

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

头文件路径为：`<asc/execution.policy.h>`。

`asc::execution::device`是默认构造的Device执行策略对象，可通过链式调用绑定Stream、临时存储和执行要求。

该接口的可用位置为Host。

## 声明

```cpp
namespace asc::execution {
inline constexpr asc::device_policy device;
}  // namespace asc::execution
```

## 约束说明

- 绑定不可变且不拥有资源。
- 默认构造绑定空Stream、空临时存储和默认执行要求。

## 调用示例

以下Host示例不提交Runtime任务；以具体值检查配置或资源引用的可观察结果。

```cpp
#include <asc/execution.policy.h>

bool example()
{
    const auto policy = asc::execution::device;
    return !policy.stream() && policy.temporary_storage().empty() &&
        policy.requirements().determinism_value() == asc::determinism::not_guaranteed &&
        policy.requirements().output_ordering_value() == asc::output_ordering::unsorted &&
        policy.requirements().tie_break_value() == asc::tie_break::unspecified;
}
```

## 关联API

- [`asc::device_policy`](device_policy.md)：指定Stream、临时存储和执行要求的Device执行策略。
