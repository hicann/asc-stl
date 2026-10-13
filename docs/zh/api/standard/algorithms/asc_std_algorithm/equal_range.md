# asc::std::equal_range

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

`asc::std::equal_range` 在已排序范围中返回与目标等价的半开子区间；无策略形式在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型 1

```cpp
template<class ForwardIterator, class T, class Compare> [[nodiscard]] constexpr pair<ForwardIterator, ForwardIterator> asc::std::equal_range(ForwardIterator first, ForwardIterator last, const T& value, Compare compare);
```

### 原型 2

```cpp
template<class ForwardIterator, class T> [[nodiscard]] constexpr pair<ForwardIterator, ForwardIterator> asc::std::equal_range(ForwardIterator first, ForwardIterator last, const T& value);
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 待查找值的类型，须能作为 compare 的实参与元素比较。 |
| `Compare` | 比较器类型；调用形式为 compare(a, b)，返回 bool 且满足严格弱序。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 已排序输入范围的起始迭代器或指针。 |
| `last` | 输入 | 已排序输入范围的结束位置，不包含该位置。 |
| `value` | 输入 | 待查找的值；返回范围内与该值等价元素构成的子范围边界。 |
| `compare` | 输入 | 比较器，按调用形式 compare(a, b) 返回 bool，true 表示 a 排在 b 前；须满足严格弱序，与范围排序规则一致。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 输入范围元素或参与运算的值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 已排序输入范围的起始迭代器或指针。 |
| `last` | 输入 | 已排序输入范围的结束位置，不包含该位置。 |
| `value` | 输入 | 待查找的值；返回范围内与该值等价元素构成的子范围边界。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `pair<ForwardIterator, ForwardIterator>` | 返回与目标值等价的半开子区间。 |
| 原型 2 | `pair<ForwardIterator, ForwardIterator>` | 返回与目标值等价的半开子区间。 |

## 约束说明

- 提供顺序执行且不进行动态内存分配的重载
- 标准执行策略重载采用顺序执行，并遵循标准允许的求值顺序

## 调用示例

以下 Host 片段使用有效整数范围和足够容量的输出缓冲区演示调用。

```cpp
#include <asc/std/algorithm>

decltype(auto) example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    return asc::std::equal_range(values, values + 8, 5);
}
```
