# asc::std::mdspan::static_extent

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

`asc::std::mdspan::static_extent`返回指定维度的编译期静态长度。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

所属类型：[`asc::std::mdspan`](mdspan.md)。

```cpp
// asc::std::mdspan 类内的声明节选；模板形参和其他成员由所属类提供。
static constexpr size_t static_extent(rank_type rank_index) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `rank_index` | 输入 | 待查询静态长度的维度编号，从0起；须满足`rank_index` < `rank()`，该维为动态维时返回`dynamic_extent`。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `size_t` | 返回指定维度的编译期静态长度。 |

## 约束说明

- 本查询从C++17起提供；元素访问形式及语言条件见[`mdspan`](mdspan.md#约束说明)。

- 静态查询；`rank_index`必须小于`rank()`，动态维返回`dynamic_extent`标记。

## 调用示例

以下Host片段以具体容量或维度演示调用；对象和索引须满足本页约束。

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>
#include <cstddef>
#include <type_traits>

bool example()
{
    return asc::std::mdspan<int, asc::std::extents<::std::size_t, 2, 3>>::static_extent(0) == 2 &&
        asc::std::mdspan<int, asc::std::extents<::std::size_t, 2, 3>>::static_extent(1) == 3;
}
```

## 关联API

- [`asc::std::mdspan`](mdspan.md)
- [本头文件的接口列表](asc_std_mdspan.md)
