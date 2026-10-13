# asc::std::full_extent_t

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

头文件路径为：`<asc/std/mdspan>`。

`asc::std::full_extent_t`表示多维切片、维度范围或布局适配方式。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 声明

```cpp
namespace asc::std {
struct full_extent_t;
} // namespace asc::std
```

## 约束说明

- 全部有效整数降rank/full/pair-like/strided slice组合，零与任意rank、静态/动态/混合/空extent、layout_left/layout_right/layout_stride源及标准布局保持或layout_stride回退。
- Host、AI Core SIMD编程 和AI Core SIMT编程兼容plain pointer域。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/mdspan>
#include <asc/std/mdspan>

bool example()
{
    int values[] = {1, 2, 3, 4, 5, 6};
    using Extents = asc::std::extents<int, 2, 3>;
    asc::std::mdspan<int, Extents> view(values);
    asc::std::full_extent_t all{};
    auto row = asc::std::submdspan(view, 1, all);
    return row.extent(0) == 3 && row(2) == 6;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
