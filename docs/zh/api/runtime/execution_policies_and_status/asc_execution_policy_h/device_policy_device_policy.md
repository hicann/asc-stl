# asc::device_policy::device_policy

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

`asc::device_policy`默认构造函数创建未绑定Stream和临时存储、并采用默认执行要求的策略。

该接口的可用位置为Host。

## 函数原型

所属类型：[`asc::device_policy`](device_policy.md)。

```cpp
// asc::device_policy 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr device_policy() noexcept;
```

## 参数说明

无参数。

## 返回值说明

无返回值。

## 约束说明

- 绑定不可变且不拥有资源。
- 默认构造绑定空Stream、空临时存储和默认执行要求。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/execution.policy.h>

bool example()
{
    asc::device_policy policy;
    return !policy.stream() && policy.temporary_storage().data() == nullptr
        && policy.temporary_storage().size_bytes() == 0
        && policy.requirements().determinism_value() == asc::determinism::not_guaranteed;
}
```

## 关联API

- [`asc::device_policy`](device_policy.md)：指定Stream、临时存储和执行要求的Device执行策略。
