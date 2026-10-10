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

`asc::std::ranges::repeat_view::repeat_view` 按本页所列构造形态初始化 `repeat_view` 对象。

标准语义参考：[cppreference `ranges`](https://en.cppreference.com/w/cpp/header/ranges)。

## 函数原型

### 原型 1

```cpp
repeat_view();
```

### 原型 2

```cpp
constexpr repeat_view(T&& value, Bound bound);
```

### 原型 3

```cpp
template<class ...TpArgs, class ...BoundArgs> constexpr repeat_view(piecewise_construct_t tag, tuple<TpArgs...> value_args, tuple<BoundArgs...> bound_args);
```

### 原型 4

```cpp
template<class Tp2> constexpr repeat_view(const Tp2& value, Bound bound);
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入/输出 | 参与操作或用于初始化、比较的值。 |
| `bound` | 输入 | 提供“按本页所列构造形态初始化 `repeat_view` 对象”所需的输入对象；类型须满足所选原型约束。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `TpArgs` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |
| `BoundArgs` | 所选原型使用的类型参数；其可用操作由约束说明限定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `tag` | 输入 | 提供“按本页所列构造形态初始化 `repeat_view` 对象”所需的输入对象；类型须满足所选原型约束。 |
| `value_args` | 输入 | 参与操作或用于初始化、比较的值。 |
| `bound_args` | 输入 | 转发给对象构造或函数调用的实参列表。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Tp2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 参与操作或用于初始化、比较的值。 |
| `bound` | 输入 | 提供“按本页所列构造形态初始化 `repeat_view` 对象”所需的输入对象；类型须满足所选原型约束。 |

## 约束说明

- 七个列出名称
- 有限repeat、两路random-access+sized zip引用写回、单次range|closure
- Host、AI Core SIMD 编程 和 AI Core SIMT 编程

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/ranges>

void example()
{
    asc::std::ranges::repeat_view<int, int> value{};
    (void)value;
}
```
