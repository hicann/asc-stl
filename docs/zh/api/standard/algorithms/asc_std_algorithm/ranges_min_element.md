# asc::std::ranges::min_element

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

`asc::std::ranges::min_element`从C++17起支持迭代器与哨兵或前向范围，并可指定比较器和投影；返回最小元素的位置，空范围返回结束位置。非借用临时范围返回`dangling`。

标准语义参考：[cppreference `algorithm`](https://en.cppreference.com/w/cpp/header/algorithm)。

## 声明

该名称是公开的常量函数对象；对象的实现类型不构成接口承诺。以下为调用形式，省略的可选参数以各原型约束为准。

```cpp
namespace asc::std::ranges {
min_element(first, last, compare, projection);
} // namespace asc::std::ranges
```

```cpp
namespace asc::std::ranges {
min_element(range, compare, projection);
} // namespace asc::std::ranges
```

## 参数说明

### 调用形式1的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 输入范围的起始迭代器。 |
| `last` | 输入 | 输入范围的结束哨兵。 |
| `compare` | 输入 | 确定元素先后关系的比较对象。 |
| `projection` | 输入 | 在比较或判断前作用于元素的投影函数。 |

### 调用形式2的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `range` | 输入 | 待访问或变换的输入范围；借用结果受其生命周期约束。 |
| `compare` | 输入 | 确定元素先后关系的比较对象。 |
| `projection` | 输入 | 在比较或判断前作用于元素的投影函数。 |

## 返回值说明

返回最小元素的位置；空范围返回结束位置。非借用临时范围的范围重载返回`dangling`。

| 调用形式 | 返回类型 |
| --- | --- |
| 迭代器与哨兵 | `Iterator` |
| 范围 | `borrowed_iterator_t<Range>` |

## 约束说明

- 比较器须能比较投影后的元素。
- 输入须满足前向遍历要求。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/algorithm>

bool example()
{
    int values[] = {1, 2, 3, 4};
    return asc::std::ranges::min_element(values, values + 4) == values && asc::std::ranges::min_element(values) == values;
}
```

## 关联API

- [本头文件的接口列表](asc_std_algorithm.md)
