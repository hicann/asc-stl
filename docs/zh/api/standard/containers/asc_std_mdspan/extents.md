# asc::std::extents

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

`asc::std::extents`保存多维索引空间的静态与动态维度长度。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 声明

```cpp
namespace asc::std {
template<class IndexType, size_t ...StaticExtents> class extents;
} // namespace asc::std
```

## 约束说明

- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/mdspan>

bool example()
{
    using shape = asc::std::extents<int, 2, asc::std::dynamic_extent>;
    shape sizes(3);
    static_assert(shape::rank() == 2 && shape::rank_dynamic() == 1);
    return sizes.extent(0) == 2 && sizes.extent(1) == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_mdspan.md)
