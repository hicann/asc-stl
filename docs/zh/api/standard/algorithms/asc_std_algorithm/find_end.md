# asc::std::find_end

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

`asc::std::find_end`返回子序列在范围内最后一次出现的起始位置；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
[[nodiscard]] constexpr ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1,
    ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate predicate);
}  // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template <class ForwardIterator1, class ForwardIterator2>
[[nodiscard]] constexpr ForwardIterator1 find_end(
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
| `last2` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `predicate` | 输入 | 用于判断元素是否满足条件的可调用对象。 |

### 原型2的参数

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
| 原型1 | `ForwardIterator1` | 返回找到的匹配位置；没有匹配项时返回输入范围末尾。 |
| 原型2 | `ForwardIterator1` | 返回找到的匹配位置；没有匹配项时返回输入范围末尾。 |

## 约束说明

- 支持当前版本列出的迭代器、哨兵和可调用对象重载。
- 标准执行策略重载采用顺序执行。

## 调用示例

以下Host示例在局部范围仍有效时检查结果和输出；函数返回可独立判断的布尔值。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    int other[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    auto result = asc::std::find_end(values, values + 8, other, other + 3);
    return result == values;
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
