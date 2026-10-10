# asc::std::submdspan_mapping_result

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

`asc::std::submdspan_mapping_result` 按切片规格从现有多维视图生成非拥有子视图或对应映射。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 声明

```cpp
template<class Mapping> struct asc::std::submdspan_mapping_result
```

## 约束说明

- 固定当前版本的 C++ 标准库的完整submdspan家族：full_extent_t/full_extent、strided_slice及deduction guide、submdspan_mapping_result、submdspan_extents/submdspan_mapping/submdspan
- 全部有效整数降rank/full/pair-like/strided slice组合，零与任意rank、静态/动态/混合/空extent、layout_left/layout_right/layout_stride源及标准布局保持或layout_stride回退
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程兼容plain pointer域

## 调用示例

以下片段用具体模板实参实例化类型；实际对象仍须满足本页构造与生命周期约束。

```cpp
#include <asc/std/mdspan>
#include <asc/std/cstddef>

void use_type()
{
    using selected = asc::std::submdspan_mapping_result<asc::std::layout_right::mapping<asc::std::extents<asc::std::size_t, 2, 3>>>;
    (void)sizeof(selected);
}
```
