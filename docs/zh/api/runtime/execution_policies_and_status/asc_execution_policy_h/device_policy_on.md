# asc::device_policy::on

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

`asc::device_policy::on` 返回绑定指定 Stream 的新策略，并保留原策略的临时存储和执行要求。

该接口的可用位置为 Host。

## 函数原型

```cpp
constexpr asc::device_policy asc::device_policy::on(asc::stream_ref stream) const noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `stream` | 输入 | 用于按序提交异步工作的 Stream。相关资源须保持有效，直至工作完成。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::device_policy` | 返回绑定指定 Stream 的新策略，并保留原策略的临时存储和执行要求。 |

## 约束说明

- 仅替换函数名称所指明的执行要求、Stream 或临时存储绑定，其余策略属性保持不变

## 调用示例

以下 Host 片段使用具体对象演示调用；涉及资源操作时须遵守本页的初始化和生命周期约束。

```cpp
#include <asc/execution.policy.h>

decltype(auto) example(asc::device_policy policy, asc::stream_ref stream)
{
    auto configured = policy.on(stream);
    return configured;
}
```
