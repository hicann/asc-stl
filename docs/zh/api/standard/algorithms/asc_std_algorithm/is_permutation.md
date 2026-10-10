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

`asc::std::is_permutation` 判断两个范围是否含有相同元素且各元素出现次数相同；无策略形式在调用者所在执行主体内顺序执行。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 函数原型

### 原型 1

```cpp
template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate> [[nodiscard]] constexpr bool asc::std::is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, BinaryPredicate predicate);
```

### 原型 2

```cpp
template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate> [[nodiscard]] constexpr bool asc::std::is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred);
```

### 原型 3

```cpp
template<class ForwardIterator1, class ForwardIterator2> [[nodiscard]] constexpr bool asc::std::is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2);
```

### 原型 4

```cpp
template<class ForwardIterator1, class ForwardIterator2> [[nodiscard]] constexpr bool asc::std::is_permutation(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2);
```

## 参数说明

### 原型 1 的参数

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

### 原型 2 的参数

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

### 原型 3 的参数

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

### 原型 4 的参数

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
| 原型 1 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 2 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 3 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 4 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

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
    int other[8] = {1, 2, 3, 4, 5, 6, 7, 8};
    return asc::std::is_permutation(values, values + 8, other);
}
```
