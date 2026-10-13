# asc::std::submdspan

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

`asc::std::submdspan` 从二维视图选取一行或一列，返回借用原底层存储的子视图。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

```cpp
template<class Element, class Extents, class Layout, class Accessor, class ...Slices> constexpr auto asc::std::submdspan(const mdspan<Element, Extents, Layout, Accessor>& source, const Slices&... slices);
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Element` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `Extents` | 多维视图使用的维度、索引映射、布局或访问策略类型。 |
| `Layout` | 多维视图使用的维度、索引映射、布局或访问策略类型。 |
| `Accessor` | 多维视图使用的维度、索引映射、布局或访问策略类型。 |
| `Slices` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入 | 源 mdspan 视图。本调用为同步执行，返回值为非拥有的子视图，借用源视图的数据指针与布局映射；子视图使用期间，源 mdspan 的数据指针与布局映射须保持有效。 |
| `slices` | 输入 | 提供“从二维视图选取一行或一列，返回借用原底层存储的子视图”使用的对象引用；被引用对象须在调用期间有效。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `auto` | 返回按切片规格建立的非拥有多维子视图或映射。 |

## 约束说明

- 固定当前版本的 C++ 标准库的完整submdspan家族：full_extent_t/full_extent、strided_slice及deduction guide、submdspan_mapping_result、submdspan_extents/submdspan_mapping/submdspan
- 全部有效整数降rank/full/pair-like/strided slice组合，零与任意rank、静态/动态/混合/空extent、layout_left/layout_right/layout_stride源及标准布局保持或layout_stride回退
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程兼容plain pointer域

## 调用示例

以下 Host C++ 片段展示整数索引与 full_extent 混合切片；设备侧须在 AI Core 函数内调用，索引须在各维度范围内。

```cpp
#include <asc/std/mdspan>
#include <asc/std/cstddef>

void example()
{
    int values[6] = {1, 2, 3, 4, 5, 6};
    using extents_type = asc::std::extents<asc::std::size_t, 2, 3>;
    extents_type extents{};
    asc::std::mdspan<int, extents_type> view(values);
    auto row = asc::std::submdspan(view, 1, asc::std::full_extent);
    auto column = asc::std::submdspan(view, asc::std::full_extent, 1);
    (void)row;
    (void)column;
}
```
