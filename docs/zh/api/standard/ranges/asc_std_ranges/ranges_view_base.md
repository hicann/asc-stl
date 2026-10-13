# asc::std::ranges::view_base

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

`asc::std::ranges::view_base`标记临时范围的不可借用结果或提供视图适配辅助能力。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

```cpp
namespace asc::std::ranges {
struct view_base;
} // namespace asc::std::ranges
```

## 约束说明

- 视图的元素访问与迭代不额外分配存储；底层范围的生命周期须覆盖所有借用视图的使用。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/ranges>

struct View : asc::std::ranges::view_base {
    int* first = nullptr;
    int* last = nullptr;
    int* begin() const { return first; }
    int* end() const { return last; }
};

bool example()
{
    static_assert(asc::std::ranges::enable_view<View>);
    int values[] = {2, 4};
    View view;
    view.first = values;
    view.last = values + 2;
    return *view.begin() == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
