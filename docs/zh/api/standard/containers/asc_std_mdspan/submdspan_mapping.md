# asc::std::submdspan_mapping

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

`asc::std::submdspan_mapping`按逐维切片规格计算结果布局映射和相对源数据起点的元素偏移，不读取或拥有元素存储。

## 函数原型

以下为省略内部SFINAE筛选参数的声明摘要；参与条件见约束说明。

```cpp
namespace asc::std {
template<class LayoutMapping, class... Slices>
constexpr auto submdspan_mapping(const LayoutMapping& mapping, Slices... slices);
}
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `LayoutMapping` | 源映射类型；当前提供layout_left、layout_right和layout_stride的映射重载。 |
| `Slices` | 每个源维度的切片类型列表，长度须等于源rank。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `mapping` | 输入 | 提供各维长度、跨步和索引到线性偏移的映射；在调用期间有效。 |
| `slices` | 输入 | 按源维度顺序提供整数索引、full_extent、半开区间对或strided_slice。整数索引移除该维，其余形式保留该维。 |

## 返回值说明

返回`submdspan_mapping_result<ResultMapping>`。`mapping`成员为独立保存的结果映射，`offset`是相对源起点的元素偏移，不是字节偏移。保持连续性时结果可以保留源的左右布局，否则使用保存原跨步的`layout_stride`。

## 约束说明

- 切片数量等于源映射的维数，结果维数等于非整数切片的数量。
- 整数索引满足`0 <= index < extent`。
- 区间对表示半开区间`[first, last)`，满足`0 <= first <= last <= extent`；例如`[1, 3)`保留两个位置。
- `full_extent`保留当前维度的完整范围。
- `strided_slice`的偏移、覆盖范围和正步长须使所有访问位置位于源维度内；保留的长度按覆盖范围和步长计算。
- 映射、索引、跨步及元素偏移的计算结果须能由对应整数类型表示。
- 操作为同步计算；满足常量表达式条件时可在编译期求值。返回映射不借用源映射对象。

## 调用示例

下例验证选取一列及裁剪内层维度时保留的原始跨步。

```cpp
#include <asc/std/mdspan>
#include <asc/std/utility>

bool example()
{
    using shape = asc::std::extents<int, 2, 3>;
    asc::std::layout_right::mapping<shape> mapping(shape{});
    const auto column = asc::std::submdspan_mapping(mapping, asc::std::full_extent, 1);
    const auto range = asc::std::submdspan_mapping(
        mapping, asc::std::full_extent, asc::std::pair<int, int>{1, 3});
    return column.offset == 1 && column.mapping.stride(0) == 3 &&
        range.offset == 1 && range.mapping.extents().extent(1) == 2 &&
        range.mapping(1, 1) == 4;
}
```

## 关联API

- [submdspan](submdspan.md)：将结果映射应用到实际数据视图。
- [strided_slice](strided_slice.md)：跨步切片的偏移、范围和步长。
