# asc::std::ranges::filter_view::filter_view

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

`asc::std::ranges::filter_view::filter_view` 按本页所列构造形态初始化 `filter_view` 对象。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

### 原型 1

```cpp
constexpr filter_view(View base, Pred predicate) noexcept(is_nothrow_move_constructible_v<View>&& is_nothrow_constructible_v<Movablebox<Pred>, in_place_t, add_rvalue_reference_t<Pred>>);
```

### 原型 2

```cpp
template<class View2, class Pred2> constexpr filter_view() noexcept(is_nothrow_default_constructible_v<View2>&& is_nothrow_default_constructible_v<Pred2>);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `base` | 输入 | 提供“按本页所列构造形态初始化 `filter_view` 对象”所需的输入对象；类型须满足所选原型约束。 |
| `predicate` | 输入 | 用于判断元素是否满足条件的可调用对象。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `View2` | 输入范围或视图的类型；须满足所选原型的遍历要求。 |
| `Pred2` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

## 约束说明

- C++20 视图不进行动态内存分配
- owning_view 仅拥有调用方传入的范围对象，不产生额外分配

## 调用示例

以下 Host 片段使用具体类型演示调用；指针、范围和索引须满足本页约束。

```cpp
#include <asc/std/ranges>

void example()
{
    asc::std::ranges::single_view<int> source(7);
    asc::std::ranges::filter_view<asc::std::ranges::single_view<int>, asc::std::identity> view(
        source, asc::std::identity{});
    (void)view;
}
```
