# asc::std::partial_sum

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

`asc::std::partial_sum`依次写出前缀归约结果。

标准语义参考：[cppreference `numeric`](https://en.cppreference.com/w/cpp/header/numeric)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator, class BinaryOperation> constexpr OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op);
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class InputIterator, class OutputIterator> constexpr OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result);
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `OutputIterator` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `BinaryOperation` | 前缀归约的二元运算可调用对象类型：接受当前部分和与当前元素，返回新的部分和。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 写入结果的输出迭代器；目标范围须有足够容量。 |
| `binary_op` | 输入 | 二元归约运算对象，按binary_op(当前部分和, 当前元素)生成前缀结果；省略该参数的重载使用`operator+`。 |

### 原型2的参数

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

## 约束说明

- `[first, last)`须为有效的可读输入范围；从`result`起须能写入相同数量的结果。
- 首个输出为首个输入元素，其后依次使用`operator+`或`binary_op`合并当前累计值和输入元素。
- 运算结果须能赋给输入元素的值类型；运算不得修改输入范围或使迭代器失效。允许`result == first`的原地计算。

## 调用示例

以下示例将1、2、3、4的前缀和1、3、6、10写入四个输出元素。

```cpp
#include <asc/std/numeric>

bool example()
{
    int input[4] = {1, 2, 3, 4};
    int output[4] = {};
    const auto end = asc::std::partial_sum(input, input + 4, output);
    return end == output + 4 &&
        output[0] == 1 &&
        output[1] == 3 &&
        output[2] == 6 &&
        output[3] == 10;
}
```

## 关联API

- [本头文件的接口列表](asc_std_numeric.md)
