# asc::std::execution::sequenced_policy

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

头文件路径为：`<asc/std/execution>`。

`asc::std::execution::sequenced_policy`标记标准执行策略形式；具体执行路径以本页约束为准。

标准语义参考：[cppreference `execution`](https://en.cppreference.com/w/cpp/header/execution)。

## 声明

```cpp
// asc::std::execution 类内的声明节选；模板形参和其他成员由所属类提供。
class sequenced_policy;
```

## 约束说明

- 提供四种执行策略类型、对象和特征。
- 已提供的算法重载采用符合标准的顺序执行语义。

## 调用示例

以下示例检查执行策略标记类型。该类型本身不启动任务；算法是否接受某个策略，以对应算法的重载为准。

```cpp
#include <asc/std/execution>

bool example()
{
    static_assert(asc::std::is_execution_policy_v<asc::std::execution::sequenced_policy>);
    static_assert(!asc::std::is_execution_policy_v<int>);
    return true;
}
```

## 关联API

- [本头文件的接口列表](asc_std_execution.md)
