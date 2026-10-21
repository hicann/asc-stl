# asc::std::ranges::iter_swap

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

`asc::std::ranges::iter_swap`是交换两个迭代器所指元素的定制点对象：优先调用可发现的`iter_swap`，其次交换可解引用结果，再次逐元素`swap`。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

`asc::std::ranges::iter_swap`是可调用对象。对象及其调用运算符由头文件提供，可通过公开名称查询其类型。

```cpp
namespace asc::std::ranges {
using iter_swap_object_type = decltype(::asc::std::ranges::iter_swap);
}
```

## 约束说明

- 接口可用于C++17及C++20；Device调用仍须满足所用迭代器和元素操作的调用位置要求。
- `iter_swap(i, j)`交换两迭代器所指元素；支持适用的自定义交换、解引用后交换及移动交换路径。
- 两个迭代器须可解引用，且对应元素满足实际选择交换路径的要求。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4};
    asc::std::ranges::iter_swap(values, values + 1);
    return values[0] == 4 && values[1] == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
