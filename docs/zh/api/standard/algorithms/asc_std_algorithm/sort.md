# asc::std::sort

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

`asc::std::sort`按比较关系排序随机访问范围；在调用者所在执行主体内顺序执行。

适用重载的同步/并行关系：带策略原型由Host调用对应的[asc::parallel::sort](../../../extension/device_parallel_algorithms_and_arguments/asc_algorithm/parallel_sort.md)前端并行执行，并同步等待该Stream完成；无策略原型为顺序执行，不涉及Device提交。带策略原型的执行策略参数[`asc::device_policy`](../../../runtime/execution_policies_and_status/asc_execution_policy_h/device_policy.md)须绑定有效Stream和足够的调用方临时存储。由于标准形式没有错误返回通道，参数校验、提交或同步失败时调用[`asc::std::terminate`](../../language_support/asc_std_exception/terminate.md)。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template <class RandomAccessIterator, class Com>
constexpr void sort(RandomAccessIterator first, RandomAccessIterator last, Com compare);
}  // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型2

```cpp
namespace asc::std {
template <class RandomAccessIterator>
constexpr void sort(RandomAccessIterator first, RandomAccessIterator last);
}  // namespace asc::std
```

该原型适用于`C++17+`，可用位置为Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `RandomAccessIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `Com` | 元素比较器类型；返回true表示第一操作数排在第二操作数之前，须满足严格弱序。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `compare` | 输入 | 用于确定元素顺序的比较对象。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `RandomAccessIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |

## 返回值说明

无返回值。

## 约束说明

- 使用C++17。
- sort/nth_element的sequential random-access pointer、默认比较与自定义比较核心。
- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host片段使用有效整数范围和足够容量的输出缓冲区演示调用。

```cpp
#include <asc/std/algorithm>

void example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    asc::std::sort(values, values + 8);
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
