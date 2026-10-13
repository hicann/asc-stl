# asc::std::ranges::common_view::common_view

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

`asc::std::ranges::common_view::common_view`按本页所列构造形态初始化`common_view`对象。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

### 原型1

```cpp
common_view();
```

### 原型2

```cpp
constexpr common_view(View base) noexcept(is_nothrow_move_constructible_v<View>);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `base` | 输入 | 被适配的底层视图；当其迭代器与哨兵类型不同（非common范围）时，本视图将其呈现为迭代器/哨兵同型的公共范围。 |

## 返回值说明

无返回值。

## 约束说明

- 视图的元素访问与迭代不额外分配存储；底层范围的生命周期须覆盖所有借用视图的使用。

## 调用示例

本例使用不同类型的迭代器与哨兵；common_view将它们转换为可用同一种类型表示的起止位置。

```cpp
#include <asc/std/ranges>
#include <asc/std/iterator>

bool example()
{
    int values[] = {2, 4, 6};
    using Iterator = asc::std::counted_iterator<int*>;
    using Base = asc::std::ranges::subrange<Iterator, asc::std::default_sentinel_t>;
    Base base(Iterator(values, 3), asc::std::default_sentinel);
    asc::std::ranges::common_view<Base> view(base);
    return *view.begin() == 2;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
