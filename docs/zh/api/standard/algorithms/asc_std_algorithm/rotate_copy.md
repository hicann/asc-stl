# asc::std::rotate_copy

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

`asc::std::rotate_copy`将旋转后的元素顺序复制到输出范围；无策略形式在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class Forward, class Output> Output rotate_copy(asc::device_policy policy, Forward first, Forward middle, Forward last, Output result);
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host。

### 原型2

```cpp
namespace asc::std {
template<class ForwardIterator, class OutputIterator> constexpr OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle, ForwardIterator last, OutputIterator result);
} // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Forward` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `Output` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `policy` | 输入 | Device执行策略，用于指定Stream、临时存储和执行要求。 |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `middle` | 输入 | 旋转分界迭代器，须位于[first, last)内；输出顺序为[middle, last)后接[first, middle)。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 写入结果的输出迭代器；目标范围容量须足以容纳全部复制元素。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `OutputIterator` | 写入结果范围的迭代器类型；目标存储须有足够容量。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `middle` | 输入 | 旋转分界迭代器，须位于[first, last)内；输出顺序为[middle, last)后接[first, middle)。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `result` | 输出 | 写入结果的输出迭代器；目标范围须有足够容量。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `Output` | 返回输出范围中最后一个写入元素之后的位置。 |
| 原型2 | `OutputIterator` | 返回输出范围中最后一个写入元素之后的位置。 |

## 约束说明

- 使用C++17。
- 该Host同步适配接口调用对应的asc::parallel前端。
- policy必须包含有效Stream和足够的调用方临时存储。
- 接口只等待该Stream。
- 由于标准形式没有错误返回通道，参数校验、提交或同步失败时调用asc::std::terminate。
- 提供顺序执行且不进行动态内存分配的重载。
- 标准执行策略重载采用顺序执行，并遵循标准允许的求值顺序。

## 调用示例

以下Host片段使用有效整数范围和足够容量的输出缓冲区演示调用。

```cpp
#include <asc/std/algorithm>

decltype(auto) example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int output[16] = {};
    return asc::std::rotate_copy(values, values + 3, values + 8, output);
}
```

## 关联API

- [`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md)：指定Stream、临时存储和执行要求的Device执行策略。
