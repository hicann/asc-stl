# asc::std::mdspan::stride

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

`asc::std::mdspan::stride`返回指定维度相邻元素之间的步长。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

所属类型：[`mdspan`](mdspan.md)。本查询未声明`noexcept`。

```cpp
constexpr index_type stride(rank_type rank_index) const;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `rank_index` | 输入 | 待查询步长的维度编号，从0起；须满足`rank_index` < `rank()`，返回该维相邻元素相隔的元素个数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `index_type` | 返回指定维度相邻元素之间的步长。 |

## 约束说明

- 本查询从C++17起提供；元素访问形式及语言条件见[`mdspan`](mdspan.md#约束说明)。

- `rank_index`须小于`rank()`；映射须支持stride查询，结果须能由`index_type`表示。

## 调用示例

以下Host片段以具体容量或维度演示调用；对象和索引须满足本页约束。

```cpp
#include <asc/std/mdspan>
#include <asc/std/array>
#include <cstddef>
#include <type_traits>

bool example()
{
    int data[6] = {};
    asc::std::mdspan<int, asc::std::extents<::std::size_t, 2, 3>> value(data);
    return value.stride(0) == 3 && value.stride(1) == 1;
}
```

## 关联API

- [`asc::std::mdspan`](mdspan.md)
- [本头文件的接口列表](asc_std_mdspan.md)
