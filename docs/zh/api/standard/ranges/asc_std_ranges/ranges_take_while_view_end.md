# asc::std::ranges::take_while_view::end

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

`asc::std::ranges::take_while_view::end`返回指向尾后位置的迭代器。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

所属类型：[`take_while_view`](ranges_take_while_view.md)。以下是按参与条件列出的声明摘要；保留供调用使用的模板默认值，省略仅供SFINAE的实现选择参数。涉及私有返回类型时用auto摘要表示，不承诺可直接命名该类型。

### 原型1

```cpp
template<class View2 = View>
constexpr auto end();
```

底层不是“简单视图”时提供本非const形式；简单视图可使用适用的const形式。“简单视图”指底层为view，const与非const均可迭代，且对应iterator和sentinel类型分别相同。

### 原型2

```cpp
template<class View2 = View>
constexpr auto end() const;
```

参与条件：`((range<const View2> && indirect_unary_predicate<const Pred, iterator_t<const View2>>))`。

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `View2` | 用于延迟检查成员的所属类型或种类，默认值见原型；一般调用无需显式指定。 |

无函数参数。

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `View2` | 用于延迟检查成员的所属类型或种类，默认值见原型；一般调用无需显式指定。 |

无函数参数。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `auto` | 返回尾后迭代器或哨兵，不可解引用；是否与begin同类型由所属视图和底层范围决定。 |
| 原型2 | `auto` | 返回尾后迭代器或哨兵，不可解引用；是否与begin同类型由所属视图和底层范围决定。 |

## 约束说明

- 每种形式的参与条件见原型；无实参查询一般直接调用，不需要指定模板选择类型。
- 返回的迭代器、指针或引用以及借用范围不得超过其实际依赖的视图对象和元素存储的有效期。

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
    auto last = view.end();
    unsigned int count = 0;
    for (auto it = view.begin(); it != last; ++it) ++count;
    return count == 2;
}
```

## 关联API

- [`asc::std::ranges::take_while_view`](ranges_take_while_view.md)
- [本头文件的接口列表](asc_std_ranges.md)
