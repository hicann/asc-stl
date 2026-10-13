# asc::std::partition_copy

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

头文件路径为：`<asc/std/algorithm>`。

`asc::std::partition_copy` 按谓词把元素分别复制到两个输出范围；无策略形式在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型 1

```cpp
template<class Input, class Output1, class Output2, class UnaryPredicate> asc::std::pair<Output1, Output2> asc::std::partition_copy(asc::device_policy policy, Input first, Input last, Output1 true_result, Output2 false_result, UnaryPredicate predicate);
```

该原型适用于 `C++17+`，可用位置为 Host。

### 原型 2

```cpp
template<class InputIterator, class OutputIterator1, class OutputIterator2, class Predicate> constexpr pair<OutputIterator1, OutputIterator2> asc::std::partition_copy(InputIterator first, InputIterator last, OutputIterator1 out_true, OutputIterator2 out_false, Predicate pred);
```

该原型适用于 `C++17+`，可用位置为 Host、AI Core SIMD 编程、AI Core SIMT 编程。

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Input` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `Output1` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `Output2` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `UnaryPredicate` | 判断元素是否满足条件的可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `policy` | 输入 | Device 执行策略，用于指定 Stream、临时存储和执行要求。 |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `true_result` | 输出 | 写入结果的输出迭代器之一；谓词返回 true 的元素复制到该范围，容量须足以容纳对应元素。 |
| `false_result` | 输出 | 写入结果的输出迭代器之一；谓词返回 false 的元素复制到该范围，容量须足以容纳对应元素。 |
| `predicate` | 输入 | 一元谓词，按调用形式 predicate(elem) 返回 bool，决定元素复制到哪个输出范围。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `OutputIterator1` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `OutputIterator2` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `Predicate` | 判断元素是否满足条件的可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `out_true` | 输出 | 写入结果的输出迭代器之一；谓词返回 true 的元素复制到该范围，容量须足以容纳对应元素。 |
| `out_false` | 输出 | 写入结果的输出迭代器之一；谓词返回 false 的元素复制到该范围，容量须足以容纳对应元素。 |
| `pred` | 输入 | 一元谓词，按调用形式 pred(elem) 返回 bool，决定元素复制到哪个输出范围。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `asc::std::pair<Output1, Output2>` | 返回两个输出范围中已写入部分各自的结束位置。 |
| 原型 2 | `pair<OutputIterator1, OutputIterator2>` | 返回两个输出范围中已写入部分各自的结束位置。 |

## 约束说明

- 使用 C++17
- 该 Host 同步适配接口调用对应的 asc::parallel 前端
- policy 必须包含有效 Stream 和足够的调用方临时存储
- 接口只等待该 Stream
- 由于标准形式没有错误返回通道，参数校验、提交或同步失败时调用 asc::std::terminate
- 提供顺序执行且不进行动态内存分配的重载
- 标准执行策略重载采用顺序执行，并遵循标准允许的求值顺序

## 调用示例

以下 Host 片段使用有效整数范围和足够容量的输出缓冲区演示调用。

```cpp
#include <asc/std/algorithm>

decltype(auto) example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int output[16] = {};
    auto predicate = [](int value) { return value % 2 == 0; };
    return asc::std::partition_copy(values, values + 8, output, output + 8, predicate);
}
```
