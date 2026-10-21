# asc::std::dextents

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

`asc::std::dextents`按指定维度数构造运行期维度长度类型。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 声明

dextents是每一维均为`dynamic_extent`的`extents`别名。以下用公开模板查询结果类型；dynamic_shape_type只是示例名称，不是另一公开接口。

```cpp
template<class IndexType, asc::std::size_t Rank>
using dynamic_shape_type = asc::std::dextents<IndexType, Rank>;
```

## 约束说明

- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/mdspan>

using shape_type = asc::std::dextents<int, 3>;
static_assert(shape_type::rank() == 3 && shape_type::rank_dynamic() == 3);

bool example()
{
    const shape_type shape(2, 3, 4);
    return shape.extent(0) == 2 && shape.extent(1) == 3 && shape.extent(2) == 4;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
