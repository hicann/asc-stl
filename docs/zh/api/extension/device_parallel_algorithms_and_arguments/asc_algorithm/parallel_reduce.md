# asc::parallel::reduce

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

头文件路径为：`<asc/algorithm>`。

`asc::parallel::reduce` 异步使用给定二元操作归约输入范围与初始值，并把最终结果写入 GM 输出参数。

接口通过 [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md) 指定 Stream、临时存储和执行要求，并异步提交 Device 任务；返回的 [`asc::execution_status`](../../../runtime/execution_policies_and_status/asc_execution/execution_status.md) 表示参数校验与任务提交状态，提交成功不等于异步执行已完成。

## 函数原型

```cpp
template<class Input, class T, class BinaryOperation> asc::execution_status asc::parallel::reduce(asc::device_policy policy, Input first, Input last, T init, T* output_value, BinaryOperation operation) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Input` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 输入范围元素或参与运算的值类型。 |
| `BinaryOperation` | 对输入值执行本页操作的可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `policy` | 输入 | Device 执行策略，用于指定 Stream、临时存储和执行要求。 |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `init` | 输入 | 提供归约初值；初值同时决定归约结果与中间累加值的类型 `T`，空范围时结果即为 `init`。 |
| `output_value` | 输出 | 用于接收归约结果的 GM 地址；结果类型为 `T`，由初值与二元操作决定。归约结果由 Device 异步写入，须在 Stream 同步完成、结果就绪后读取；异步任务完成前地址必须保持有效。 |
| `operation` | 输入 | 提供二元操作，接受当前累加值与一个输入元素并返回新的累加值；归约结果由初值逐个经该操作并入输入元素得到。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::execution_status` | 返回参数校验或任务提交状态，而非归约结果；提交成功不等于归约结果已就绪，读取 `*output_value` 前须同步等待 policy 所绑定的 Stream 完成。 |

## 约束说明

- 使用 C++17，并从毕昇 ASC 翻译单元的 Host 侧提交
- 输入范围必须连续、支持随机访问且可由 Device 访问
- 可调用对象和传输值必须可平凡复制并可在 AI Core 调用
- policy 必须包含有效 Stream 和足够的调用方临时存储
- 标量、数量或索引输出位于 GM，并在 Stream 完成前保持有效
- 参数或能力不满足要求时不会提交任务

## 调用示例

以下片段在毕昇 ASC 翻译单元的 Host 提交侧调用；Stream、临时存储和 GM 参数须在异步任务完成前有效。

```cpp
#include <asc/algorithm>

struct binary_operation { __aicore__ int operator()(int left, int right) const { return left + right; } };

decltype(auto) example(asc::device_policy policy, int* input, int* output)
{
    // policy 绑定有效 Stream 和足够临时存储；所有指针指向有效 GM 且保持到任务完成。
    return asc::parallel::reduce(policy, input, input + 4, 0, output, binary_operation{});
}
```
