# asc::std::extents::rank_dynamic

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

`asc::std::extents::rank_dynamic`返回运行期指定长度的维度数量。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

所属类型：[`asc::std::extents`](extents.md)。

```cpp
// asc::std::extents 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr rank_type rank_dynamic() noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `rank_type` | 返回运行期指定长度的维度数量。 |

## 约束说明

- Host、AI Core SIMD编程 和AI Core SIMT编程。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/mdspan>
#include <asc/std/type_traits>

bool example()
{
    asc::std::extents<int, 2, 3> shape;
    return shape.rank() == 2 && shape.rank_dynamic() == 0 && shape.extent(0) == 2 && shape.extent(1) == 3;
}
```

## 关联API

- [`asc::std::extents`](extents.md)
- [本头文件的接口列表](asc_std_mdspan.md)
