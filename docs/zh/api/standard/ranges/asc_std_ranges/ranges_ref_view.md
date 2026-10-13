# asc::std::ranges::ref_view

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

`asc::std::ranges::ref_view`惰性地观察、筛选、组合或变换输入范围；底层存储仍由调用方管理。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

```cpp
namespace asc::std::ranges {
template<class Range> class ref_view;
} // namespace asc::std::ranges
```

## 约束说明

- 视图的元素访问与迭代不额外分配存储；底层范围的生命周期须覆盖所有借用视图的使用。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/tuple>

bool example()
{
    int values[] = {1, 2, 3, 4};
    using Base = asc::std::ranges::subrange<int*>;
    Base base(values, values + 4);
    asc::std::ranges::ref_view<int[4]> view(values);
    *view.begin() = 9;
    return values[0] == 9 && view.size() == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
