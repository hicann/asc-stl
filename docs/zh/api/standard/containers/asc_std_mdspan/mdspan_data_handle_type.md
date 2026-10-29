# asc::std::mdspan::data_handle_type

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

`asc::std::mdspan::data_handle_type`标识访问器持有的底层数据句柄类型。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 声明

所属类型：[`asc::std::mdspan`](mdspan.md)。

```cpp
// asc::std::mdspan 类内的声明节选；模板形参和其他成员由所属类提供。
using data_handle_type = typename Accessor::data_handle_type;
```

## 约束说明

- 该类型别名从C++17起提供；所属类型的访问形式及语言条件见[`mdspan`](mdspan.md#约束说明)。

- 该公开别名由所选`Element`、`Extents`、`Layout`或`Accessor`决定；类型查询不访问底层元素。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/mdspan>
#include <asc/std/cstddef>
#include <type_traits>
#include <cstddef>
#include <utility>

using alias_type = typename asc::std::mdspan<int, asc::std::extents<asc::std::size_t, 2, 3>, asc::std::layout_right,
    asc::std::default_accessor<int>>::data_handle_type;
static_assert(::std::is_same_v<alias_type, int*>);
```

## 关联API

- [`asc::std::mdspan`](mdspan.md)
- [本头文件的接口列表](asc_std_mdspan.md)
