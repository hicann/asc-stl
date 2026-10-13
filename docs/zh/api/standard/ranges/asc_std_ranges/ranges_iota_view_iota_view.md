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

`asc::std::ranges::iota_view::iota_view` 按本页所列构造形态初始化 `iota_view` 对象。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

### 原型 1

```cpp
iota_view();
```

### 原型 2

```cpp
constexpr iota_view(Start start) noexcept(is_nothrow_move_constructible_v<Start>);
```

### 原型 3

```cpp
constexpr iota_view(type_identity_t<Start> start, type_identity_t<BoundSentinel> bound) noexcept(is_nothrow_move_constructible_v<Start>&& is_nothrow_move_constructible_v<BoundSentinel>);
```

### 原型 4

```cpp
template<class BoundSentinel2> constexpr iota_view(Iterator start, BoundSentinel bound);
```

### 原型 5

```cpp
template<class BoundSentinel2> constexpr iota_view(Iterator start, Iterator bound);
```

### 原型 6

```cpp
template<class BoundSentinel2> constexpr iota_view(Iterator start, Sentinel bound);
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `start` | 输入 | 序列起始值；视图从该值起按递增生成元素。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `start` | 输入 | 序列起始值；视图从该值起按递增生成元素。 |
| `bound` | 输入 | 序列上界哨兵值；元素生成到等于 bound 之前结束。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `BoundSentinel2` | bound 的实际类型；须可与视图迭代器比较相等或为兼容的哨兵类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `start` | 输入 | 起始迭代器，包装序列起始值。 |
| `bound` | 输入 | 结束哨兵，界定序列上界。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `BoundSentinel2` | bound 的实际类型；须可与视图迭代器比较相等或为兼容的哨兵类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `start` | 输入 | 起始迭代器，包装序列起始值。 |
| `bound` | 输入 | 结束迭代器，包装序列上界值。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `BoundSentinel2` | bound 的实际类型；须可与视图迭代器比较相等或为兼容的哨兵类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `start` | 输入 | 起始迭代器，包装序列起始值。 |
| `bound` | 输入 | 结束哨兵，界定序列上界。 |

## 约束说明

- C++20 视图不进行动态内存分配
- owning_view 仅拥有调用方传入的范围对象，不产生额外分配

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/ranges>

void example()
{
    asc::std::ranges::iota_view<int, int> value{};
    (void)value;
}
```
