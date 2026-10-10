# asc::std::dims

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

`asc::std::dims` 按指定维度数构造运行期维度长度类型。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 声明

```cpp
template<size_t Rank, class IndexType> using asc::std::dims = dextents<IndexType, Rank>
```

## 约束说明

- 固定当前版本的 C++ 标准库的完整dynamic_extent/extents/dextents/dims家族：零rank与正rank、默认/按rank或rank_dynamic传值/array/span/跨extents构造、标准显式性与约束、deduction guide、相等比较及rank/rank_dynamic/static_extent/extent观察
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下片段选用具体模板实参展示别名类型。

```cpp
#include <asc/std/mdspan>

void use_type()
{
    using selected = asc::std::dims<2, int>;
}
```
