# asc::std::mdspan::value_type

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

`asc::std::mdspan::value_type`标识元素或结果的值类型。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 声明

所属类型：[`mdspan`](mdspan.md)。`value_type`移除元素类型的const与volatile限定。

```cpp
using value_type = remove_cv_t<element_type>;
```

## 约束说明

- 该类型别名从C++17起提供；所属类型的访问形式及语言条件见[`mdspan`](mdspan.md#约束说明)。

- 该公开别名由所选`Element`、`Extents`、`Layout`或`Accessor`决定；类型查询不访问底层元素。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/mdspan>
#include <asc/std/type_traits>

using view_type = asc::std::mdspan<const int, asc::std::extents<int, 2, 3>>;
static_assert(asc::std::is_same_v<view_type::element_type, const int>);
static_assert(asc::std::is_same_v<view_type::value_type, int>);
```

## 关联API

- [`asc::std::mdspan`](mdspan.md)
- [本头文件的接口列表](asc_std_mdspan.md)
