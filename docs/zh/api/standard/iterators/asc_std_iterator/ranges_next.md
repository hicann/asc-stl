# asc::std::ranges::next

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

`asc::std::ranges::next`返回推进指定步数后的迭代器副本，负步数依赖双向能力。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

`asc::std::ranges::next`是可调用对象。对象及其调用运算符由头文件提供，可通过公开名称查询其类型。

```cpp
namespace asc::std::ranges {
using next_object_type = decltype(::asc::std::ranges::next);
}
```

## 约束说明

- 接口可用于C++17及C++20；Device调用仍须满足所用迭代器和元素操作的调用位置要求。
- 支持`next(i)`、`next(i, n)`、`next(i, bound)`及`next(i, n, bound)`；返回移动后的迭代器副本。
- 负距离要求双向迭代器；带边界的负距离还要求边界与迭代器为同一类型，且所经过位置有效。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6, 8};
    auto result = asc::std::ranges::next(values, 2, values + 4);
    auto bounded = asc::std::ranges::next(result, 3, values + 4);
    return result == values + 2 && *result == 6 && bounded == values + 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
