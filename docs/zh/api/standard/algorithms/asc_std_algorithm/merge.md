# asc::std::merge

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

`asc::std::merge`把两个已排序范围合并写入输出范围；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
constexpr OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2,
    OutputIterator result, Compare compare);
}  // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型2

```cpp
namespace asc::std {
template <class InputIterator1, class InputIterator2, class OutputIterator>
constexpr OutputIterator merge(
    InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result);
}  // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator1` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `InputIterator2` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `OutputIterator` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |
| `Compare` | 比较器类型；调用形式为compare(a, b)，返回bool且满足严格弱序。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first1` | 输入 | 第一个已排序输入范围的起始迭代器或指针。 |
| `last1` | 输入 | 第一个已排序输入范围的结束位置，不包含该位置。 |
| `first2` | 输入 | 第二个已排序输入范围的起始迭代器或指针。 |
| `last2` | 输入 | 第二个已排序输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 写入合并结果的输出迭代器；目标范围容量须足以容纳两个输入范围的全部元素。 |
| `compare` | 输入 | 比较器，按调用形式compare(a, b)返回bool；返回true表示a顺序在b前，须满足严格弱序，与两个输入范围的排序规则一致。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `InputIterator1` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `InputIterator2` | 读取输入范围元素的迭代器类型；须满足原型要求的遍历能力。 |
| `OutputIterator` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first1` | 输入 | 第一个已排序输入范围的起始迭代器或指针。 |
| `last1` | 输入 | 第一个已排序输入范围的结束位置，不包含该位置。 |
| `first2` | 输入 | 第二个已排序输入范围的起始迭代器或指针。 |
| `last2` | 输入 | 第二个已排序输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 写入合并结果的输出迭代器；目标范围容量须足以容纳两个输入范围的全部元素。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `OutputIterator` | 返回输出范围中最后一个写入元素之后的位置。 |
| 原型2 | `OutputIterator` | 返回输出范围中最后一个写入元素之后的位置。 |

## 约束说明

- 使用C++17。
- 提供顺序执行且不进行动态内存分配的重载。

## 调用示例

以下Host示例在局部范围仍有效时检查结果和输出；函数返回可独立判断的布尔值。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int other[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int output[16] = {};
    auto result = asc::std::merge(values, values + 8, other, other + 8, output);
    return result == output + 16 && output[0] == 1 && output[1] == 1 && output[15] == 8;
}
```

## 关联API

- [`asc::parallel::merge`](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_merge.md)：使用执行策略提交异步设备操作。
