# asc::std::submdspan_extents

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

`asc::std::submdspan_extents`按每一维的切片计算结果`extents`，不创建元素视图或访问存储。整数切片消除该维，`full_extent`保留该维，区间或步长切片生成对应的长度。

## 函数原型

```cpp
namespace asc::std {
template<class Extents, class... Slices,
    enable_if_t<(Extents::rank() == sizeof...(Slices)), int> = 0>
constexpr auto submdspan_extents(const Extents& source, Slices... slices);
}
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Extents` | 来源维度类型。 |
| `Slices` | 逐维切片类型包；个数须等于来源`rank()`。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入 | 来源各维长度；只读取元数据。 |
| `slices` | 输入 | 每维的整数索引、`full_extent`、半开区间[first,last)或`strided_slice`。步长切片的extent是覆盖长度，结果计数为ceil(extent/stride)。 |

## 返回值说明

| 返回类型 | 含义 |
| --- | --- |
| 推导的`extents`类型 | 按值保存剩余维度及各长度；整数切片不保留维度，能在编译期确定的长度保留静态extent。结果不借用source，不保存元素地址。 |

## 约束说明

- 切片个数必须等于source.`rank()`。
- 整数切片处于对应维度的有效索引范围；半开区间须满足0 <= first <= last <= 源维长度。
- `strided_slice`的offset及extent须覆盖源维内的合法子区间，stride须为正。
- 所有索引、长度、差及步长计算须能由结果`index_type`表示。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/mdspan>
#include <asc/std/utility>

bool example()
{
    using shape_type = asc::std::extents<asc::std::size_t, 4, 5>;
    const auto interval = asc::std::submdspan_extents(shape_type{}, asc::std::full_extent,
        asc::std::pair<int, int>{1, 4});
    const auto selected = asc::std::submdspan_extents(shape_type{}, asc::std::full_extent, 2);
    static_assert(decltype(selected)::rank() == 1);
    return interval.extent(0) == 4 && interval.extent(1) == 3 && selected.extent(0) == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
