# asc::std::ranges::single_view::single_view

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

`asc::std::ranges::single_view::single_view`按本页所列构造形态初始化`single_view`对象。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

### 原型1

```cpp
single_view();
```

### 原型2

```cpp
constexpr single_view(T&& value) noexcept(is_nothrow_move_constructible_v<T>);
```

### 原型3

```cpp
template<class ...Args> constexpr single_view(in_place_t tag, Args&&... args) noexcept(is_nothrow_constructible_v<T, Args...>);
```

### 原型4

```cpp
template<class Tp2> constexpr single_view(const Tp2& value) noexcept(is_nothrow_copy_constructible_v<Tp2>);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 视图唯一元素的值，被移动构造到视图中保存。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Args` | 转发给所存元素构造的实参类型包。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | in_place_t标记，指示以args原位构造视图所存元素。 |
| `args` | 输入/输出 | 转发给所存元素构造的实参包。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Tp2` | 可转换为视图所存元素类型的实参类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 视图唯一元素的值，从该值构造所存元素。 |

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
    asc::std::ranges::single_view<int> view(7);
    return *view.begin() == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
