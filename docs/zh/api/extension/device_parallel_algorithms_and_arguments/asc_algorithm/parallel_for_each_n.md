# asc::parallel::for_each_n

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

`asc::parallel::for_each_n` 从给定起始位置开始，异步对指定数量的元素调用函数对象。

## 函数原型

```cpp
template<class Input, class Size, class Function> asc::execution_status asc::parallel::for_each_n(asc::device_policy policy, Input first, Size count, Function function) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Input` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `Size` | 表示待处理元素个数的类型（整数）。 |
| `Function` | 对输入值执行本页操作的可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `policy` | 输入 | Device 执行策略（device_policy）：提供任务提交所用的 Stream 与调用方临时存储；返回值仅反映提交状态，提交成功不表示异步工作已完成。 |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `count` | 输入 | 从 first 起待调用函数对象的元素个数。 |
| `function` | 输入 | 函数对象：对从 first 起的 count 个元素各调用一次 function(元素)；须可平凡复制并可在 AI Core 调用。 |

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

struct action { __aicore__ void operator()(int& value) const { ++value; } };

decltype(auto) example(asc::device_policy policy, int* input)
{
    // policy 绑定有效 Stream 和足够临时存储；所有指针指向有效 GM 且保持到任务完成。
    return asc::parallel::for_each_n(policy, input, 4, action{});
}
```
