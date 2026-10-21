# asc::std::mdspan::is_always_unique

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

`asc::std::mdspan::is_always_unique`在编译期判断映射是否保证每个索引对应唯一元素。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

所属类型：[`mdspan`](mdspan.md)。异常规格跟随`mapping_type`的对应静态查询。

```cpp
static constexpr bool is_always_unique()
    noexcept(noexcept(mapping_type::is_always_unique()));
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `bool` | 条件成立时返回`true`，否则返回`false`。 |

## 约束说明

- 本查询从C++17起提供；元素访问形式及语言条件见[`mdspan`](mdspan.md#约束说明)。

- 静态查询，无需构造视图或访问底层元素；映射属性取自`mapping_type`。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/mdspan>
#include <asc/std/type_traits>

bool example()
{
    int values[] = {1, 2, 3, 4, 5, 6};
    using Extents = asc::std::extents<asc::std::size_t, 2, 3>;
    asc::std::mdspan<int, Extents> view(values);
    return view.is_always_unique();
}
```

## 关联API

- [`asc::std::mdspan`](mdspan.md)
- [本头文件的接口列表](asc_std_mdspan.md)
