# asc::std::ranges::borrowed_subrange_t

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

`asc::std::ranges::borrowed_subrange_t`按名称所指的范围或迭代器属性计算结果类型。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 声明

以下用公开CPO与类型特征表达类型结果的声明摘要；R须满足range，range_size_t还须满足sized_range。

```cpp
namespace asc::std::ranges {
template<class R>
using borrowed_subrange_t = enable_if_t<range<R>,
    conditional_t<borrowed_range<R>, subrange<iterator_t<R>>, dangling>>;
}
```

## 约束说明

- `R`须满足`range`；`range_size_t`只对可查询大小的范围有效。
- 借用结果类型取决于`borrowed_range<R>`，不延长元素存储的生命周期；非借用的临时范围结果使用`dangling`。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/ranges>
#include <asc/std/type_traits>

using result = asc::std::ranges::borrowed_subrange_t<int (&)[3]>;
static_assert(asc::std::is_same_v<result, asc::std::ranges::subrange<int*>>);
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
