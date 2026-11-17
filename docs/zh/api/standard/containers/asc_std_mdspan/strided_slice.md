# asc::std::strided_slice

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

`asc::std::strided_slice`用于`submdspan`，描述源张量某一维上等间隔采样的区间。其成员为`offset`（首个源索引）、`extent`（覆盖的源区间长度）和`stride`（采样步长）。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 声明

```cpp
namespace asc::std {
template<class OffsetType, class ExtentType, class StrideType> struct strided_slice;
} // namespace asc::std
```

## 约束说明

- 成员类型为有符号／无符号整数类型或支持的integral-constant-like类型；整数值及生成的映射须能由源索引类型表示。
- 使用`0 <= offset <= source.extent(d)`、`0 <= extent <= source.extent(d) - offset`及正的`stride`；被选中的源索引为`offset + j * stride`，其中`0 <= j < count`。
- `extent`是覆盖的源区间长度，不是选出的元素个数。结果维度为`count = extent == 0 ? 0 : 1 + (extent - 1) / stride`。例如`{1, 5, 2}`选择索引1、3、5，共三个元素；对长度为6的一维源，`{6, 0, 2}`得到空切片。
- 切片保留该维，与源映射共同决定结果跨步；非空切片的步长大于1时可能得到不连续的子视图。视图不复制或拥有元素。
- Host、AI Core SIMD编程 和AI Core SIMT编程兼容plain pointer域。

## 调用示例

以下Host示例每隔一个元素采样一次，并检查结果维度和元素值。

```cpp
#include <asc/std/mdspan>

bool example()
{
    int values[6] = {10, 11, 12, 13, 14, 15};
    asc::std::mdspan<int, asc::std::extents<int, 6>> source(values);
    auto sampled = asc::std::submdspan(source, asc::std::strided_slice<int, int, int>{1, 5, 2});
    auto empty = asc::std::submdspan(source, asc::std::strided_slice<int, int, int>{6, 0, 2});
    return sampled.extent(0) == 3 && sampled(0) == 11 && sampled(1) == 13 &&
        sampled(2) == 15 && sampled.stride(0) == 2 && empty.empty();
}
```

## 关联API

- [submdspan](submdspan.md)：构造借用式子视图。
- [submdspan_mapping](submdspan_mapping.md)：将切片与源布局组合。
- [带padding的裁剪与转置示例](../../../../../../examples/standard/mdspan_matrix/README.md)。
