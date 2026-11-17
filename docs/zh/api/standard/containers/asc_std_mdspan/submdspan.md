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

`asc::std::submdspan`从多维视图按逐维切片规格创建子视图；返回视图独立保存映射和访问器，并借用原元素存储。

## 函数原型

以下为省略内部SFINAE筛选参数的声明摘要；切片须能用于源布局的`submdspan_mapping`。

```cpp
namespace asc::std {
template<class T, class Extents, class Layout, class Accessor, class... Slices>
constexpr auto submdspan(
    const mdspan<T, Extents, Layout, Accessor>& source, Slices... slices);
}
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 元素类型；子视图访问原存储中的相同对象。 |
| `Extents` | 源视图的静态／动态维度信息及索引类型。 |
| `Layout` | 源布局策略，决定其mapping类型。 |
| `Accessor` | 源访问器类型；子视图采用其offset_policy。 |
| `Slices` | 逐维切片类型列表，数量等于源视图rank。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `source` | 输入 | 被切片的视图；函数读取其句柄、映射和访问器，不拥有或复制元素。 |
| `slices` | 输入 | 逐维指定整数索引、full_extent、半开区间或strided_slice；具体边界见submdspan_mapping。 |

## 返回值说明

返回对应元素类型、结果维度、结果布局和`Accessor::offset_policy`的mdspan。原始视图对象可在子视图之前销毁，但底层元素存储及访问器依赖的资源须持续有效。

## 约束说明

- 切片数量和取值满足源映射的要求；所有计算出的访问位置均须在有效存储中。
- 返回视图不拥有存储；对可写子视图的修改直接作用于原元素。
- 保存原跨步的结果不一定连续，不得仅按结果维度乘积假设连续排列。
- 相应布局映射与访问器在所选执行位置可用。

## 调用示例

```cpp
#include <asc/std/mdspan>

bool example()
{
    int values[6] = {1, 2, 3, 4, 5, 6};
    asc::std::mdspan<int, asc::std::extents<int, 2, 3>> view(values);
    auto row = asc::std::submdspan(view, 1, asc::std::full_extent);
    auto column = asc::std::submdspan(view, asc::std::full_extent, 1);
    column(1) = 9;
    return row.extent(0) == 3 && row(0) == 4 &&
        column.extent(0) == 2 && column(0) == 2 && values[4] == 9;
}
```

## 关联API

- [submdspan_mapping](submdspan_mapping.md)：各切片形式和布局计算规则。
- [mdspan](mdspan.md)：借用式多维数据视图。

[带padding的批量裁剪与转置完整示例](../../../../../../examples/standard/mdspan_matrix/README.md)：组合区间切片与步进切片并保留行和批次跨步，再写出转置结果。
