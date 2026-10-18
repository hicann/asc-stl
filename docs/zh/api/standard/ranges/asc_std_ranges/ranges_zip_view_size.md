# asc::std::ranges::zip_view::size

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

`asc::std::ranges::zip_view::size`返回当前对象包含的元素数量。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

所属类型：[`asc::std::ranges::zip_view`](ranges_zip_view.md)。以下为类内声明，`first_`与`second_`表示两个底层视图。

```cpp
constexpr asc::std::size_t size()
    noexcept(noexcept(asc::std::ranges::size(first_)) && noexcept(asc::std::ranges::size(second_)));
```

```cpp
constexpr asc::std::size_t size() const
    noexcept(noexcept(asc::std::ranges::size(first_)) && noexcept(asc::std::ranges::size(second_)));
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `asc::std::size_t` | 两个底层视图大小的较小值，即可组成的元素对数量。 |

## 约束说明

- 两个底层视图须支持`asc::std::ranges::size`；`const`重载还要求对常量底层视图求大小的表达式有效。
- 当前`zip_view`组合两个支持随机访问和大小查询的视图；它借用的底层元素存储须保持有效。
- 本成员不遍历元素；当两个底层大小查询均不抛出异常时，本成员也不抛出异常。

## 调用示例

以下Host示例给出具体输入，并检查结果。

```cpp
#include <asc/std/ranges>

bool example()
{
    int left[4] = {1, 2, 3, 4};
    int right[2] = {5, 6};
    using Base = asc::std::ranges::subrange<int*>;
    asc::std::ranges::zip_view<Base, Base> view(Base(left, left + 4), Base(right, right + 2));
    const auto& constant = view;
    return view.size() == 2 && constant.size() == 2;
}
```

## 关联API

- [`asc::std::ranges::zip_view`](ranges_zip_view.md)
- [本头文件的接口列表](asc_std_ranges.md)
