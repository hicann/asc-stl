# asc::std::layout_left::mapping

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

`layout_left::mapping<Extents>`按最左维连续的布局把多维索引映射到线性存储偏移。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 声明

所属类型：[`asc::std::layout_left`](layout_left.md)。

```cpp
// asc::std::layout_left 类内的声明节选；模板形参和其他成员由所属类提供。
template<class Extents> class mapping;
```

## 约束说明

- Host、AI Core SIMD编程 和AI Core SIMT编程兼容plain pointer域。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/mdspan>

bool example()
{
    using shape = asc::std::extents<int, 2, 3>;
    asc::std::layout_left::mapping<shape> mapping(shape{});
    return mapping(1, 2) == 5 && mapping.stride(0) == 1 && mapping.stride(1) == 2;
}
```

## 关联API

- [`asc::std::layout_left`](layout_left.md)
- [本头文件的接口列表](asc_std_mdspan.md)
