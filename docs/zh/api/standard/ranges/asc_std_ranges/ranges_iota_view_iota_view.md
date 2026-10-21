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

所属类型：[`iota_view`](ranges_iota_view.md)。以下按当前实现列声明摘要；省略仅供SFINAE的选择参数，保留供调用使用的类型默认值。默认构造形式均有逐项参与条件，不能据此假定所有特化都可默认构造。

### 原型1

```cpp
constexpr iota_view();
```

仅当Value满足default_initializable时参与；保存起点与Bound均值初始化。

### 原型2

```cpp
constexpr explicit iota_view(Value value) noexcept;
```

显式保存起点，边界值初始化；默认Bound为unreachable_sentinel_t时得到无界递增序列。

### 原型3

```cpp
constexpr iota_view(type_identity_t<Value> value, type_identity_t<Bound> bound_sentinel) noexcept;
```

保存起点和不包含在结果中的边界；必须能够按递增及比较规则到达所需结束位置。

### 原型4

```cpp
template<class Bound2 = Bound>
constexpr iota_view(iterator first, iterator last) noexcept;
```

仅在same_as<Value, Bound2>时参与；iterator是本类型已公开的计数迭代器。

### 原型5

```cpp
template<class Bound2 = Bound>
constexpr iota_view(iterator first, Bound2 last) noexcept;
```

仅在same_as<Bound2, unreachable_sentinel_t>时参与。

### 原型6

另有接受当前计数迭代器与实现哨兵的构造，带Bound2=Bound选择参数，条件为!same_as<Value, Bound2> && !same_as<Value, unreachable_sentinel_t>。正常异构有界特化可传入原视图的begin()与end()；哨兵的实现名字不作为公开类型声明。该构造同为constexpr且noexcept。

## 参数说明

### 原型1的参数

无函数参数。

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 计数序列起点。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 计数序列起点。 |
| `bound_sentinel` | 输入 | 不包含的结束值或哨兵。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Bound2` | 用于选择边界构造的类型，默认为Bound。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 决定新起点的当前视图迭代器。 |
| `last` | 输入 | 决定不包含的新边界值的当前视图迭代器。 |

### 原型5的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Bound2` | 用于选择边界构造的类型，默认为Bound。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 决定新起点的当前视图迭代器。 |
| `last` | 输入 | 不可达哨兵，产生无界结束条件。 |

### 原型6的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `first` | 输入 | 决定新起点的计数迭代器。 |
| `last` | 输入 | 同一iota特化取得的异构有界哨兵，保存原边界值。 |

## 返回值说明

无返回值。

## 约束说明

- 每种形式须满足其原型所列参与条件；实际保存的范围或值还须满足所属视图的类型要求。
- 构造视图不会复制它所借用的元素；底层存储和被借用对象须覆盖相应迭代器与元素访问期。
- 以noexcept标注的形式须遵守实际成员操作不抛出异常的要求；具体异常规格见各原型。

## 调用示例

以下Host示例使用具体输入，并检查接口的可观察结果。

```cpp
#include <asc/std/ranges>

bool example()
{
    asc::std::ranges::iota_view<int> unbounded(3);
    asc::std::ranges::iota_view<int, int> original(3, 7);
    asc::std::ranges::iota_view<int, int> selected(original.begin() + 1, original.end());
    return *unbounded.begin() == 3 && *selected.begin() == 4 && selected.size() == 3;
}
```

## 关联API

- [本头文件的接口列表](asc_std_ranges.md)
