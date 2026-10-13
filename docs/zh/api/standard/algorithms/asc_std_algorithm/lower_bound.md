# asc::std::lower_bound

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

`asc::std::lower_bound` 在已排序范围中寻找不小于目标的首个位置；无策略形式在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型 1

```cpp
template<class ForwardIterator, class T, class Compare> [[nodiscard]] constexpr ForwardIterator asc::std::lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp);
```

### 原型 2

```cpp
template<class ForwardIterator, class T> [[nodiscard]] constexpr ForwardIterator asc::std::lower_bound(ForwardIterator first, ForwardIterator last, const T& value);
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `T` | 待查找分界值的类型，须能作为 comp 的实参与元素比较。 |
| `Compare` | 比较器类型；调用形式为 comp(elem, value)，返回 bool 且满足严格弱序。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 已排序输入范围的起始迭代器或指针。 |
| `last` | 输入 | 已排序输入范围的结束位置，不包含该位置。 |
| `value` | 输入 | 待查找的分界值；查找首个不满足 comp(elem, value) 的元素位置。 |
| `comp` | 输入 | 比较器，按调用形式 comp(elem, value) 返回 bool，true 表示 elem 排在 value 前；须满足严格弱序，与范围排序规则一致。 |

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
| `value` | 输入 | 待查找的分界值；查找首个不小于该值（不满足 elem < value）的元素位置。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `ForwardIterator` | 返回符合条件的元素位置；未找到时返回输入范围的结束位置。 |
| 原型 2 | `ForwardIterator` | 返回符合条件的元素位置；未找到时返回输入范围的结束位置。 |

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
    return asc::std::lower_bound(values, values + 8, 5);
}
```
