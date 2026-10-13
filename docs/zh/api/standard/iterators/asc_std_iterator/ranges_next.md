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

```cpp
namespace asc::std::ranges {
constexpr next_fn next;
} // namespace asc::std::ranges
```

## 约束说明

- 该范围迭代器操作要求C++20，且仅在Host可调用。

- 步数推进不越过哨兵；负步数要求迭代器双向。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/iterator>

bool example()
{
    int values[] = {1, 2, 3};
    return *asc::std::ranges::next(values) == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_iterator.md)
