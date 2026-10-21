# asc::std::search_n

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

`asc::std::search_n`寻找连续出现指定次数的目标值；在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template <class ForwardIterator, class Size, class T, class BinaryPredicate>
[[nodiscard]] constexpr ForwardIterator search_n(
    ForwardIterator first, ForwardIterator last, Size count, const T& value_, BinaryPredicate pred);
}  // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template <class ForwardIterator, class Size, class T>
[[nodiscard]] constexpr ForwardIterator search_n(
    ForwardIterator first, ForwardIterator last, Size count, const T& value_);
}  // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `Size` | 表示待匹配序列长度的类型，通常为整型或迭代器差值类型。 |
| `T` | 待匹配值的类型，须可与范围内元素按`operator==`比较或作为pred实参。 |
| `BinaryPredicate` | 判断元素与待匹配值是否等价的二元谓词类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `count` | 输入 | 待匹配的连续元素个数。 |
| `value_` | 输入 | 待匹配的值；在范围内查找连续count个与该值等价元素的序列起始位置。 |
| `pred` | 输入 | 二元谓词，按调用形式pred(elem, value_)返回bool；返回true视为元素匹配。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `ForwardIterator` | 遍历输入范围所使用的迭代器类型；须满足原型要求的遍历能力。 |
| `Size` | 表示待匹配序列长度的类型，通常为整型或迭代器差值类型。 |
| `T` | 待匹配值的类型，须可与范围内元素按`operator==`比较。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器或指针。 |
| `last` | 输入 | 输入范围的结束位置，不包含该位置。 |
| `count` | 输入 | 待匹配的连续元素个数。 |
| `value_` | 输入 | 待匹配的值；在范围内查找连续count个与该值等价（`operator==`）元素的序列起始位置。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `ForwardIterator` | 返回找到的匹配位置；没有匹配项时返回输入范围末尾。 |
| 原型2 | `ForwardIterator` | 返回找到的匹配位置；没有匹配项时返回输入范围末尾。 |

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
    auto result = asc::std::search_n(values, values + 8, 2, 3);
    return result == values + 8;
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
