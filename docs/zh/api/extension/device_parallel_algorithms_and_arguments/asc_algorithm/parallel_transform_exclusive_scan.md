# asc::parallel::transform_exclusive_scan

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

`asc::parallel::transform_exclusive_scan` 先异步变换输入元素，再执行不包含当前元素的前缀扫描。

## 函数原型

```cpp
template<class Input, class Output, class T, class BinaryOperation, class UnaryOperation> asc::execution_status asc::parallel::transform_exclusive_scan(asc::device_policy policy, Input first, Input last, Output result, T init, BinaryOperation binary_operation, UnaryOperation unary_operation) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Input` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `Output` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `T` | 输入范围元素或参与运算的值类型。 |
| `BinaryOperation` | 对输入值执行本页操作的可调用对象类型。 |
| `UnaryOperation` | 对输入值执行本页操作的可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `policy` | 输入 | Device 执行策略（device_policy）：提供任务提交所用的 Stream 与调用方临时存储；返回值仅反映提交状态，提交成功不表示异步工作已完成。 |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 输出范围的起始迭代器：排除当前项的前缀扫描结果经该范围异步写入，容量不小于输入元素数。 |
| `init` | 输入 | 前缀归约的初始累加值：输出首元素即该值，其后每个输出由该值与先前元素的变换结果归约得到。 |
| `binary_operation` | 输入 | 二元归约运算对象，按 binary_operation(当前累加值, 变换结果) 生成排除当前项的前缀结果；须可平凡复制并可在 AI Core 调用。 |
| `unary_operation` | 输入 | 一元变换对象，每个元素先经 unary_operation 变换再参与扫描；须可平凡复制并可在 AI Core 调用。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::execution_status` | 返回参数校验或任务提交状态；提交成功不表示异步工作已经完成。 |

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
struct unary_operation { __aicore__ int operator()(int value) const { return value * 2; } };

decltype(auto) example(asc::device_policy policy, int* input, int* output)
{
    // policy 绑定有效 Stream 和足够临时存储；所有指针指向有效 GM 且保持到任务完成。
    return asc::parallel::transform_exclusive_scan(policy, input, input + 4, output, 0, binary_operation{}, unary_operation{});
}
```
