# asc::std::inclusive_scan

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

`asc::std::inclusive_scan`写出包含当前输入的前缀归约。

本页说明顺序执行的重载。Device并行提交入口为[`asc::parallel::inclusive_scan`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_inclusive_scan.md)，其参数、状态返回和完成条件见对应页面。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator, class BinaryO> constexpr OutputIterator inclusive_scan(InputIterator first, InputIterator last, OutputIterator result, BinaryO binary_op);
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型2

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator, class T, class BinaryO> constexpr OutputIterator inclusive_scan(InputIterator first, InputIterator last, OutputIterator result, BinaryO binary_op, T init);
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型3

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator> constexpr OutputIterator inclusive_scan(InputIterator first, InputIterator last, OutputIterator result);
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `OutputIterator` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `BinaryO` | 前缀归约的二元运算可调用对象类型：接受当前部分和与当前元素。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 写入结果的输出迭代器；目标范围须有足够容量。 |
| `binary_op` | 输入 | 二元归约运算对象，按binary_op(当前累加值, 当前元素)生成包含当前项的前缀结果；省略该参数的重载使用`operator+`。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `OutputIterator` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `T` | 归约初值与前缀结果的类型。 |
| `BinaryO` | 前缀归约的二元运算可调用对象类型：接受当前部分和与当前元素。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 写入结果的输出迭代器；目标范围须有足够容量。 |
| `binary_op` | 输入 | 二元归约运算对象，按binary_op(当前累加值, 当前元素)生成包含当前项的前缀结果；省略该参数的重载使用`operator+`。 |
| `init` | 输入 | 归约初值，作为首个输出之前的起始累加值，会计入每个输出元素。 |

### 原型3的参数

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
| 原型1 | `OutputIterator` | 返回输出范围中最后一个写入结果之后的位置。 |
| 原型2 | `OutputIterator` | 返回输出范围中最后一个写入结果之后的位置。 |
| 原型3 | `OutputIterator` | 返回输出范围中最后一个写入结果之后的位置。 |

## 约束说明

- `[first, last)`须为有效的可读输入范围；从`result`起须能写入相同数量的结果。
- 每个输出包含当前位置的输入；有初值时先合并`init`，无初值时以首个输入元素开始归约。
- 运算结果须可赋回累加类型；自定义运算不得修改输入范围或使迭代器失效。允许`result == first`的原地计算。

## 调用示例

以下示例将包含当前项的前缀和1、3、6、10写入四个输出元素。

```cpp
#include <asc/std/numeric>

bool example()
{
    int input[4] = {1, 2, 3, 4};
    int output[4] = {};
    const auto end = asc::std::inclusive_scan(input, input + 4, output);
    return end == output + 4 &&
        output[0] == 1 &&
        output[1] == 3 &&
        output[2] == 6 &&
        output[3] == 10;
}
```

## 关联API

- [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md)：指定Stream、临时存储和执行要求的Device执行策略。
