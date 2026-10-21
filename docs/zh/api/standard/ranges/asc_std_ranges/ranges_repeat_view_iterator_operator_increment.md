# asc::std::ranges::repeat_view::iterator::`operator++`

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

`repeat_view::iterator::operator++`：后置自增，返回自增前副本。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

所属迭代器类型通过`decltype(view.begin())`取得；下面在其类内上下文中使用iterator和difference_type作声明摘要。标有friend的是隐藏友元，使用运算符表达式调用。

### 原型1

```cpp
constexpr iterator& operator++();
```

### 原型2

```cpp
constexpr iterator operator++(int);
```

## 参数说明

### 原型1的参数

无函数参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `后置标记` | 输入 | int占位实参，只用于区分后置形式，不表示移动距离。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `iterator&` | 前置递增，原地前进一个位置并返回自身引用。 |
| 原型2 | `iterator` | 后置递增，原地前进一个位置并返回更新前的迭代器副本。 |

## 约束说明

- 迭代器须关联同一重复序列；所有算术结果须可由difference_type及实际位置类型表示。
- 有界序列的位置不得移到0之前；访问时还须位于结束位置之前。递减不得越过序列起点。
- 迭代器保存指向view中被重复值的指针；该view及保存值须覆盖迭代器使用期。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/ranges>

bool example()
{
    auto view = asc::std::ranges::views::repeat(7, 4);
    const auto first = view.begin();
    auto position = first;
    const auto previous = position++;
    auto& same = ++position;
    return previous == first && position - first == 2 && &same == &position && *position == 7;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
