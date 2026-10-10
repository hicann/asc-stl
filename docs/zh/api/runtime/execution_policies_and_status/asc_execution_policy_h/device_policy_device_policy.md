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

`asc::device_policy` 默认构造函数创建未绑定 Stream 和临时存储、并采用默认执行要求的策略。

该接口的可用位置为 Host。

## 函数原型

```cpp
constexpr asc::device_policy::device_policy() noexcept;
```

## 参数说明

无参数。

## 约束说明

- 绑定不可变且不拥有资源
- 默认构造绑定空 Stream、空临时存储和默认执行要求

## 调用示例

以下 Host 片段使用具体对象演示调用；涉及资源操作时须遵守本页的初始化和生命周期约束。

```cpp
#include <asc/execution.policy.h>

void example()
{
    asc::device_policy policy{};
    (void)policy.requirements();
}
```
