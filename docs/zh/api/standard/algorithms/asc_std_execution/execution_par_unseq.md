# asc::std::execution::par_unseq

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

`asc::std::execution::par_unseq`表示并行且无序的策略形式；当前版本对应重载使用顺序执行路径。

标准语义参考：[cppreference `execution`](https://en.cppreference.com/w/cpp/header/execution)。

## 声明

```cpp
namespace asc::std::execution {
inline constexpr const parallel_unsequenced_policy par_unseq;
}  // namespace asc::std::execution
```

## 约束说明

- 提供四种执行策略类型、对象和特征。
- 已提供的算法重载采用符合标准的顺序执行语义。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/type_traits>
#include <asc/std/execution>

auto value = asc::std::execution::par_unseq;

static_assert(asc::std::is_same_v<decltype(value), asc::std::execution::parallel_unsequenced_policy>);
```

## 关联API

- [本头文件的接口列表](asc_std_execution.md)
