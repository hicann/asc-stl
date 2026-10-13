# asc::dstrides

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

头文件路径为：`<asc/mdspan>`。

`asc::dstrides`表示包含动态步长的mdspan步长类型。

## 声明

`asc::dstrides<OffsetType, Rank>`是别名模板，等价于含`Rank`个`asc::dynamic_stride`实参的`asc::strides`，不要求调用方命名内部辅助类型。

```cpp
using Rank2 = asc::dstrides<int, 2>;
using Equivalent = asc::strides<int, asc::dynamic_stride, asc::dynamic_stride>;
```

## 约束说明

- `OffsetType`是可表示步长的整数类型，`Rank`是维数。
- 所有维度步长都在构造时提供；步长可为负，后续视图访问仍须落在有效存储中。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/mdspan>
#include <asc/std/type_traits>

bool example()
{
    using Strides = asc::dstrides<int, 2>;
    static_assert(asc::std::is_same_v<Strides, asc::strides<int, asc::dynamic_stride, asc::dynamic_stride>>);
    Strides strides(3, 1);
    return strides.stride(0) == 3 && strides.stride(1) == 1;
}
```

## 关联API

- [本头文件的接口列表](asc_mdspan.md)
