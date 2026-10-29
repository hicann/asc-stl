# asc::std::ranges::owning_view::`operator=`

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

头文件路径为：`<asc/std/ranges>`。

`asc::std::ranges::owning_view::operator=`按所选赋值重载更新对象，并返回规定的结果。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

所属类型：[`asc::std::ranges::owning_view`](ranges_owning_view.md)。

```cpp
// asc::std::ranges::owning_view 类内的声明节选；模板形参和其他成员由所属类提供。
owning_view<Rp>& operator=(owning_view<Rp>&& other);
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 赋值来源对象；左值形式复制其状态，右值形式按对应成员的移动操作转移状态。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `owning_view<Rp> &` | 返回更新后的当前对象引用，可继续进行赋值或复合操作。 |

## 约束说明

- 视图的元素访问与迭代不额外分配存储；底层范围的生命周期须覆盖所有借用视图的使用。
- owning_view仅拥有调用方传入的范围对象，不产生额外分配。

## 调用示例

以下Host片段使用具体类型演示调用；指针、范围和索引须满足本页约束。

```cpp
#include <asc/std/ranges>

bool example()
{
    using view_type = asc::std::ranges::owning_view<asc::std::ranges::single_view<int>>;
    view_type target(asc::std::ranges::single_view<int>(1)), source(asc::std::ranges::single_view<int>(7));
    target = static_cast<view_type&&>(source);
    return target.size() == 1 && *target.begin() == 7;
}
```

## 关联API

- [`asc::std::ranges::owning_view`](ranges_owning_view.md)
- [本头文件的接口列表](asc_std_ranges.md)
