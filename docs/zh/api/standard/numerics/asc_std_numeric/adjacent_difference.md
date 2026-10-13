# asc::std::adjacent_difference

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

头文件路径为：`<asc/std/numeric>`。

`asc::std::adjacent_difference` 依次写出相邻输入元素的差分。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

### 原型 1

```cpp
template<class Input, class Output, class BinaryOperation> Output asc::std::adjacent_difference(asc::device_policy policy, Input first, Input last, Output result, BinaryOperation operation);
```

该原型适用于 `C++17+`，可用位置为 Host。

### 原型 2

```cpp
template<class InputIterator, class OutputIterator, class BinaryOperation> constexpr OutputIterator asc::std::adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op);
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

### 原型 3

```cpp
template<class InputIterator, class OutputIterator> constexpr OutputIterator asc::std::adjacent_difference(InputIterator first, InputIterator last, OutputIterator result);
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Input` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `Output` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `BinaryOperation` | 计算相邻差分的二元运算可调用对象类型：接受前一项与当前项，返回差分结果。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `policy` | 输入 | Device 执行策略，用于指定 Stream、临时存储和执行要求。 |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 写入差分结果的输出迭代器；目标范围须有足够容量。 |
| `operation` | 输入 | 二元差分运算对象，按 operation(前一项, 当前项) 计算相邻元素差分；省略该参数的重载使用 operator-。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `OutputIterator` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `BinaryOperation` | 计算相邻差分的二元运算可调用对象类型：接受前一项与当前项，返回差分结果。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 写入结果的输出迭代器；目标范围须有足够容量。 |
| `binary_op` | 输入 | 二元差分运算对象，按 binary_op(前一项, 当前项) 计算相邻元素差分；省略该参数的重载使用 operator-。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `OutputIterator` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 写入结果的输出迭代器；目标范围须有足够容量。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `Output` | 返回输出范围中最后一个写入结果之后的位置。 |
| 原型 2 | `OutputIterator` | 返回输出范围中最后一个写入结果之后的位置。 |
| 原型 3 | `OutputIterator` | 返回输出范围中最后一个写入结果之后的位置。 |

## 约束说明

- 使用 C++17
- 该 Host 同步适配接口调用对应的 asc::parallel 前端
- policy 必须包含有效 Stream 和足够的调用方临时存储
- 接口只等待该 Stream
- 由于标准形式没有错误返回通道，参数校验、提交或同步失败时调用 asc::std::terminate
- 提供顺序迭代器/值重载
- 本族中标准定义的执行策略重载采用顺序执行语义

## 调用示例

以下片段用具体整数范围展示数值调用；输出数组具有足够容量。

```cpp
#include <asc/std/numeric>

decltype(auto) example()
{
    int input[4] = {1, 2, 3, 4};
    int output[4] = {};
    return asc::std::adjacent_difference(input, input + 4, output);
}
```
