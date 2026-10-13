# asc::std::ranges::iota_view::iota_view

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

`asc::std::ranges::iota_view::iota_view`按本页所列构造形态初始化`iota_view`对象。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

### 原型1

```cpp
iota_view();
```

### 原型2

```cpp
constexpr iota_view(Start start) noexcept(is_nothrow_move_constructible_v<Start>);
```

### 原型3

```cpp
constexpr iota_view(type_identity_t<Start> start, type_identity_t<BoundSentinel> bound) noexcept(is_nothrow_move_constructible_v<Start>&& is_nothrow_move_constructible_v<BoundSentinel>);
```

### 原型4

```cpp
template<class BoundSentinel2> constexpr iota_view(Iterator start, BoundSentinel bound);
```

### 原型5

```cpp
template<class BoundSentinel2> constexpr iota_view(Iterator start, Iterator bound);
```

### 原型6

```cpp
template<class BoundSentinel2> constexpr iota_view(Iterator start, Sentinel bound);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `start` | 输入 | 序列起始值；视图从该值起按递增生成元素。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `start` | 输入 | 序列起始值；视图从该值起按递增生成元素。 |
| `bound` | 输入 | 序列上界哨兵值；元素生成到等于bound之前结束。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `BoundSentinel2` | bound的实际类型；须可与视图迭代器比较相等或为兼容的哨兵类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `start` | 输入 | 起始迭代器，包装序列起始值。 |
| `bound` | 输入 | 结束哨兵，界定序列上界。 |

### 原型5的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `BoundSentinel2` | bound的实际类型；须可与视图迭代器比较相等或为兼容的哨兵类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `start` | 输入 | 起始迭代器，包装序列起始值。 |
| `bound` | 输入 | 结束迭代器，包装序列上界值。 |

### 原型6的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `BoundSentinel2` | bound的实际类型；须可与视图迭代器比较相等或为兼容的哨兵类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `start` | 输入 | 起始迭代器，包装序列起始值。 |
| `bound` | 输入 | 结束哨兵，界定序列上界。 |

## 返回值说明

无返回值。

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
    asc::std::ranges::iota_view<int, int> view(3, 6);
    return *view.begin() == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
