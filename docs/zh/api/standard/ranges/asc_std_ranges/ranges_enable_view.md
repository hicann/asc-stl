# asc::std::ranges::enable_view

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

`asc::std::ranges::enable_view`标记类型可作为范围视图使用。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

enable_view是已初始化的inline constexpr bool变量模板：通过公开继承view_base或匹配的view_interface识别视图，也可按允许的特化规则指定。以下查询已提供的公开变量；is_enabled_view仅为示例名称。

```cpp
template<class T>
inline constexpr bool is_enabled_view = asc::std::ranges::enable_view<T>;
```

## 约束说明

- 通过公开且可转换的view_base继承，或可识别的view_interface派生关系启用。
- enable_view为true仍不单独保证range和movable条件，也不保证拥有元素；view概念还检查这些条件。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/ranges>

static_assert(asc::std::ranges::enable_view<asc::std::ranges::single_view<int>>);
static_assert(!asc::std::ranges::enable_view<int[3]>);
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
