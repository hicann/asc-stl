# asc::std::ranges::advance

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

`asc::std::ranges::advance`按指定距离或结束哨兵更新迭代器；同时给出距离与边界时，在完成距离或到达边界处停止，并返回未完成的距离。

标准语义参考：[cppreference `iterator`](https://en.cppreference.com/w/cpp/header/iterator)。

## 声明

`asc::std::ranges::advance`是可调用对象。对象及其调用运算符由头文件提供，可通过公开名称查询其类型。

```cpp
namespace asc::std::ranges {
using advance_object_type = decltype(::asc::std::ranges::advance);
}
```

## 约束说明

- 接口可用于C++17及C++20；Device调用仍须满足所用迭代器和元素操作的调用位置要求。
- `advance(i, n)`按有符号距离更新`i`；`advance(i, bound)`推进至哨兵。
- `advance(i, n, bound)`在完成距离或到达边界时停止，返回未完成的距离。
- 非负移动要求从当前位置到边界形成有效范围；负移动要求双向迭代器，带边界的负移动还要求边界与迭代器为同一类型。

## 调用示例

以下Host示例在对象有效期间检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6, 8};
    int* iterator = values;
    asc::std::ranges::advance(iterator, 2);
    auto remaining = asc::std::ranges::advance(iterator, 3, values + 4);
    return iterator == values + 4 && remaining == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
