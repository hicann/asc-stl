# asc::std::ranges::prev

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

头文件路径为：`<asc/std/iterator>`。

`asc::std::ranges::prev`返回移动后的迭代器副本；正步数使双向迭代器后退，负步数使其前进。调用可用于常量表达式时保持constexpr能力。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

`asc::std::ranges::prev`是可调用对象。对象及其调用运算符由头文件提供，可通过公开名称查询其类型。

```cpp
namespace asc::std::ranges {
using prev_object_type = decltype(::asc::std::ranges::prev);
}
```

## 约束说明

- 接口可用于C++17及C++20；Device调用仍须满足所用迭代器和元素操作的调用位置要求。
- 所有形式要求双向迭代器；支持`prev(i)`、`prev(i, n)`及`prev(i, n, bound)`，返回移动后的副本。
- 正距离后退，负距离前进；负距离也适用于双向迭代器，不要求随机访问。
- 有边界形式的`bound`与`i`类型相同；移动方向与边界须一致，且所经过位置有效。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6, 8};
    auto earlier = asc::std::ranges::prev(values + 3, 2);
    auto later = asc::std::ranges::prev(earlier, -1);
    return earlier == values + 1 && later == values + 2 && *later == 6;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
