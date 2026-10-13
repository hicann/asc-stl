# asc::std::ranges::views::counted

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

头文件路径为：`<asc/std/ranges>`。

`asc::std::ranges::views::counted`从随机访问迭代器和非负元素数量建立有界子范围；从起始位置到起始位置加指定数量的位置必须有效。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

该名称是公开的常量函数对象；对象的实现类型不构成接口承诺。以下为调用形式，省略的可选参数以各原型约束为准。

```cpp
// asc::std::ranges::views 类内的声明节选；模板形参和其他成员由所属类提供。
counted(iterator, count);
```

## 参数说明

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `iterator` | 输入 | 生成固定长度视图的起始迭代器。 |
| `count` | 输入 | 要处理、保留或跳过的元素数量。 |

## 返回值说明

返回从起始迭代器开始、包含指定数量元素的视图。

| 调用形式 | 返回类型 |
| --- | --- |
| 迭代器与数量 | `subrange<Iterator, Iterator, subrange_kind::sized>` |

## 约束说明

- 视图的元素访问与迭代不额外分配存储；底层范围的生命周期须覆盖所有借用视图的使用。
- 起始迭代器须支持`first + count`。
- `count`不得为负，且区间内的元素须可访问。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/tuple>

bool example()
{
    int values[] = {1, 2, 3, 4};
    auto view = asc::std::ranges::views::counted(values, 2);
    return view.size() == 2 && *view.begin() == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
