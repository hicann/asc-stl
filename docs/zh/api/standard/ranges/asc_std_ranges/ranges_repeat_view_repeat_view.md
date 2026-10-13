# asc::std::ranges::repeat_view::repeat_view

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

`asc::std::ranges::repeat_view::repeat_view`按本页所列构造形态初始化`repeat_view`对象。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

### 原型1

```cpp
repeat_view();
```

### 原型2

```cpp
constexpr repeat_view(T&& value, Bound bound);
```

### 原型3

```cpp
template<class ...TpArgs, class ...BoundArgs> constexpr repeat_view(piecewise_construct_t tag, tuple<TpArgs...> value_args, tuple<BoundArgs...> bound_args);
```

### 原型4

```cpp
template<class Tp2> constexpr repeat_view(const Tp2& value, Bound bound);
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 待重复的值，被移动构造到视图中保存；每次解引用返回该值的副本。 |
| `bound` | 输入 | 重复次数上界；默认构造（表示无界）时视图无限重复。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `TpArgs` | value_args元组中的实参类型包。 |
| `BoundArgs` | bound_args元组中的实参类型包。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | piecewise_construct标记，指示以元组形式逐元素转发构造成员。 |
| `value_args` | 输入 | 转发给所存值构造的实参元组。 |
| `bound_args` | 输入 | 转发给重复次数上界构造的实参元组。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Tp2` | 可转换为视图所存值类型的实参类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待重复的值，从该值构造视图所存元素。 |
| `bound` | 输入 | 重复次数上界；默认构造（表示无界）时视图无限重复。 |

## 返回值说明

无返回值。

## 约束说明

- 七个列出名称。
- 有限repeat、两路random-access+sized zip引用写回、单次range|closure。
- Host、AI Core SIMD编程 和AI Core SIMT编程。

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
    asc::std::ranges::repeat_view<int, int> view(7, 3);
    return *view.begin() == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
