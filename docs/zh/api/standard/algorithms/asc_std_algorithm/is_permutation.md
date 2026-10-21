# asc::std::is_permutation

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

`asc::std::is_permutation`判断两个范围是否含有相同元素且各元素出现次数相同；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
[[nodiscard]] constexpr bool is_permutation(
    ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, BinaryPredicate predicate);
}  // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
[[nodiscard]] constexpr bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2,
    ForwardIterator2 last2, BinaryPredicate pred);
}  // namespace asc::std
```

### 原型3

```cpp
namespace asc::std {
template <class ForwardIterator1, class ForwardIterator2>
[[nodiscard]] constexpr bool is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2);
}  // namespace asc::std
```

### 原型4

```cpp
namespace asc::std {
template <class ForwardIterator1, class ForwardIterator2>
[[nodiscard]] constexpr bool is_permutation(
    ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2);
}  // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator1` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `ForwardIterator2` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `BinaryPredicate` | 判断元素是否满足条件的可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first1` | 输入 | 输入范围的起始迭代器或指针。 |
| `last1` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `first2` | 输入 | 输入范围的起始迭代器或指针。 |
| `predicate` | 输入 | 用于判断元素是否满足条件的可调用对象。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator1` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `ForwardIterator2` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `BinaryPredicate` | 判断元素是否满足条件的可调用对象类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first1` | 输入 | 输入范围的起始迭代器或指针。 |
| `last1` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `first2` | 输入 | 输入范围的起始迭代器或指针。 |
| `last2` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `pred` | 输入 | 用于判断元素是否满足条件的可调用对象。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator1` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `ForwardIterator2` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first1` | 输入 | 输入范围的起始迭代器或指针。 |
| `last1` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `first2` | 输入 | 输入范围的起始迭代器或指针。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator1` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `ForwardIterator2` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first1` | 输入 | 输入范围的起始迭代器或指针。 |
| `last1` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `first2` | 输入 | 输入范围的起始迭代器或指针。 |
| `last2` | 输入 | 输入范围的结束位置，不包含该位置。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `bool` | 条件成立时返回`true`，否则返回`false`。 |
| 原型2 | `bool` | 条件成立时返回`true`，否则返回`false`。 |
| 原型3 | `bool` | 条件成立时返回`true`，否则返回`false`。 |
| 原型4 | `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 对未提供`last2`的重载，从`first2`起须有至少`last1 - first1`个有效可读元素；两个范围在比较期间均须保持有效。

- 提供顺序执行且不进行动态内存分配的重载。

## 调用示例

以下Host片段使用有效整数范围和足够容量的输出缓冲区演示调用。

```cpp
#include <asc/std/algorithm>

decltype(auto) example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int other[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    return asc::std::is_permutation(values, values + 8, other);
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
