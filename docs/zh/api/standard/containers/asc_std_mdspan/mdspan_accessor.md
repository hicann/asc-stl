# asc::std::mdspan::accessor

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

`asc::std::mdspan::accessor`返回当前多维视图使用的元素访问器。

标准语义参考：[cppreference `mdspan`](https://en.cppreference.com/w/cpp/header/mdspan)。

## 函数原型

所属类型：[`asc::std::mdspan`](mdspan.md)。

```cpp
// asc::std::mdspan 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr const Accessor& accessor() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `const Accessor &` | 返回当前多维视图使用的元素访问器。 |

## 约束说明

- 本查询从C++17起提供；元素访问形式及语言条件见[`mdspan`](mdspan.md#约束说明)。

- 返回视图所保存元数据的只读引用；`mdspan`对象须覆盖该引用使用期，不访问元素存储。

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
    return view.accessor().access(values, 4) == 5;
}
```

## 关联API

- [`asc::std::mdspan`](mdspan.md)
- [本头文件的接口列表](asc_std_mdspan.md)
