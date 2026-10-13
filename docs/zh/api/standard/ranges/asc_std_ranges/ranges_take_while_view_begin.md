# asc::std::ranges::take_while_view::begin

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

`asc::std::ranges::take_while_view::begin`返回指向首元素的迭代器。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

所属类型：[`asc::std::ranges::take_while_view`](ranges_take_while_view.md)。

### 原型1

```cpp
// asc::std::ranges::take_while_view 类内的声明节选；模板形参和其他成员由所属类提供。
template<class View2> [[nodiscard]] constexpr auto begin();
```

### 原型2

```cpp
// asc::std::ranges::take_while_view 类内的声明节选；模板形参和其他成员由所属类提供。
template<class View2> [[nodiscard]] constexpr auto begin() const;
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `View2` | 输入范围或视图的类型；须满足所选原型的遍历要求。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `View2` | 输入范围或视图的类型；须满足所选原型的遍历要求。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `auto` | 返回指向首元素的迭代器。 |
| 原型2 | `auto` | 返回指向首元素的迭代器。 |

## 约束说明

- 视图的元素访问与迭代不额外分配存储；底层范围的生命周期须覆盖所有借用视图的使用。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/ranges>
#include <asc/std/array>
#include <asc/std/iterator>
#include <asc/std/tuple>

bool example()
{
    int values[] = {1, 2, 3, 4};
    using Base = asc::std::ranges::subrange<int*>;
    Base base(values, values + 4);
    auto predicate = [](int value) { return value < 3; };
    asc::std::ranges::take_while_view<Base, decltype(predicate)> view(base, predicate);
    return *view.begin() == 1;
}
```

## 关联API

- [`asc::std::ranges::take_while_view`](ranges_take_while_view.md)
- [本头文件的接口列表](asc_std_ranges.md)
