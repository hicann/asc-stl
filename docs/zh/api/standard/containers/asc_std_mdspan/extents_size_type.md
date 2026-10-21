# asc::std::extents::size_type

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

`asc::std::extents::size_type`标识容器大小的无符号类型。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 声明

所属类型：[`extents`](extents.md)。该类型是`index_type`对应的无符号类型，不固定为size_t。

```cpp
using size_type = make_unsigned_t<index_type>;
```

## 约束说明

- 此别名表示所属类型用于元素数量或大小的无符号整数类型；读取类型本身不分配内存，也不访问元素。
- 构造、分配和访问的运行条件见所属类型[asc::std::`extents`](extents.md)。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/mdspan>
#include <asc/std/type_traits>

using shape_type = asc::std::extents<int, 2, 3>;
static_assert(asc::std::is_same_v<shape_type::size_type, unsigned int>);
static_assert(asc::std::is_unsigned_v<shape_type::size_type>);
```

## 关联API

- [`asc::std::extents`](extents.md)
- [本头文件的接口列表](asc_std_mdspan.md)
