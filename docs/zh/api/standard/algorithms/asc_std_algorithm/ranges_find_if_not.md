# asc::std::ranges::find_if_not

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

`asc::std::ranges::find_if_not`是C++17起可调用的算法对象，接受迭代器与哨兵或输入范围，并可指定投影；返回首个投影后不满足谓词的位置。范围重载对非借用临时范围返回`dangling`。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 声明

该名称是公开的常量函数对象；对象的实现类型不构成接口承诺。以下为调用形式，省略的可选参数以各原型约束为准。

```cpp
namespace asc::std::ranges {
find_if_not(first, last, predicate, projection);
}  // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
find_if_not(range, predicate, projection);
}  // namespace asc::std::ranges
```

## 参数说明

### 调用形式1的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器。 |
| `last` | 输入 | 输入范围的结束哨兵。 |
| `predicate` | 输入 | 对元素或投影结果执行判断的谓词。 |
| `projection` | 输入 | 在比较或判断前作用于元素的投影函数；省略时使用`asc::std::identity`。 |

### 调用形式2的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `range` | 输入 | 待访问或变换的输入范围；借用结果受其生命周期约束。 |
| `predicate` | 输入 | 对元素或投影结果执行判断的谓词。 |
| `projection` | 输入 | 在比较或判断前作用于元素的投影函数；省略时使用`asc::std::identity`。 |

## 返回值说明

返回首个不满足谓词的元素位置；未找到时返回结束位置。非借用临时范围的范围重载返回`dangling`。

| 调用形式 | 返回类型 |
| --- | --- |
| 迭代器与哨兵 | `Iterator` |
| 范围 | `borrowed_iterator_t<Range>` |

## 约束说明

- 谓词须能接收投影后的元素。
- 迭代器与哨兵须形成有效范围。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto predicate = [](int value) { return value % 2 == 0; };
    auto first = asc::std::ranges::find_if_not(values, values + 4, predicate);
    auto second = asc::std::ranges::find_if_not(values, predicate);
    return first == values && second == first;
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
