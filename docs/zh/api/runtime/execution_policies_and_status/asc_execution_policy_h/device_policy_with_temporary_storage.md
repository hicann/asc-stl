# asc::device_policy::with_temporary_storage

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

`asc::device_policy::with_temporary_storage`返回绑定指定临时存储的新策略，并保留原策略的Stream和执行要求。

该接口的可用位置为Host。

## 函数原型

所属类型：[`asc::device_policy`](device_policy.md)。

```cpp
// asc::device_policy 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr asc::device_policy with_temporary_storage(asc::temporary_storage_ref storage) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `storage` | 输入 | 调用方提供的临时存储；其容量和生命周期须满足本页约束。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::device_policy` | 返回绑定指定临时存储的新策略，并保留原策略的Stream和执行要求。 |

## 约束说明

- 仅替换函数名称所指明的执行要求、Stream或临时存储绑定，其余策略属性保持不变。

## 调用示例

以下Host片段使用具体对象演示调用；涉及资源操作时须遵守本页的初始化和生命周期约束。

```cpp
#include <asc/execution.policy.h>

decltype(auto) example(asc::device_policy policy, asc::temporary_storage_ref storage)
{
    // storage 所指内存在异步工作完成前必须保持有效。
    auto configured = policy.with_temporary_storage(storage);
    return configured;
}
```

## 关联API

- [`asc::device_policy`](device_policy.md)：指定Stream、临时存储和执行要求的Device执行策略。
