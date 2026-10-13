# asc::std::stable_sort

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

`asc::std::stable_sort`排序范围并保持等价元素的原有相对顺序；无策略形式在调用者所在执行主体内顺序执行。

该接口的可用位置为Host、AI Core SIMD编程。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class RandomAccessIterator, class Compare> void stable_sort(RandomAccessIterator first, RandomAccessIterator last, Compare compare);
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class RandomAccessIterator> void stable_sort(RandomAccessIterator first, RandomAccessIterator last);
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `RandomAccessIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `Compare` | 定义元素先后顺序的比较对象类型。 |

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

- stable_sort/stable_partition/inplace_merge的非分配、非递归random-access pointer核心。
- Host+普通AICore。

## 调用示例

以下Host片段使用有效整数范围和足够容量的输出缓冲区演示调用。

```cpp
#include <asc/std/algorithm>

void example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    asc::std::stable_sort(values, values + 8);
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
