# asc::std::ranges::zip_view::begin

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

`asc::std::ranges::zip_view::begin`返回指向首元素的迭代器。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

所属类型：[`zip_view`](ranges_zip_view.md)。以下是按参与条件列出的声明摘要；保留供调用使用的模板默认值，省略仅供SFINAE的实现选择参数。涉及私有返回类型时用auto摘要表示，不承诺可直接命名该类型。

### 原型1

```cpp
constexpr auto begin();
```

此形式没有额外的成员模板参与条件；仍须满足所属类型的要求。

### 原型2

```cpp
constexpr auto begin() const;
```

此形式没有额外的成员模板参与条件；仍须满足所属类型的要求。

## 参数说明

### 原型1的参数

无函数参数。

### 原型2的参数

无函数参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `auto` | 返回起始迭代器；私有迭代器类型以auto表示，由所属视图定义其解引用和移动行为。 |
| 原型2 | `auto` | 返回起始迭代器；私有迭代器类型以auto表示，由所属视图定义其解引用和移动行为。 |

## 约束说明

- 每种形式的参与条件见原型；无实参查询一般直接调用，不需要指定模板选择类型。
- 返回的迭代器、指针或引用以及借用范围不得超过其实际依赖的视图对象和元素存储的有效期。
- 当前zip固定保存两个范围；其迭代器须支持随机访问，范围须有大小。const形式还要求两侧const迭代器类型分别与非const形式相同，这些条件在实例化时检查。

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
    asc::std::ranges::zip_view<Base, Base> view(base, base);
    return asc::std::get<0>(*view.begin()) == 1;
}
```

## 关联API

- [`asc::std::ranges::zip_view`](ranges_zip_view.md)
- [本头文件的接口列表](asc_std_ranges.md)
