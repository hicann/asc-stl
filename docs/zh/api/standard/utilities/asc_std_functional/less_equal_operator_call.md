# asc::std::less_equal::`operator()`

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

头文件路径为：`<asc/std/functional>`。

`asc::std::less_equal::operator()`按函数对象名称比较输入值并返回布尔结果。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

所属类型：[`asc::std::less_equal`](less_equal.md)。

### 原型1：指定类型形式

```cpp
// less_equal<T>（T非void）类内声明，T由所属类提供。
[[nodiscard]] constexpr bool operator()(const T& x, const T& y) const;
```

### 原型2：透明特化

```cpp
// less_equal<void> 类内声明，模板实参由调用推导。
template <class T1, class T2>
[[nodiscard]] constexpr auto operator()(T1&& x, T2&& y) const noexcept(noexcept(::asc::std::forward<T1>(x) <= ::asc::std::forward<T2>(y))) -> decltype(::asc::std::forward<T1>(x) <= ::asc::std::forward<T2>(y));
```

## 参数说明

### 原型1的参数

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 当前运算的左侧操作数，通过const引用读取。 |
| `y` | 输入 | 当前运算的右侧操作数，通过const引用读取。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 左操作数的推导类型；转发引用保留输入的cv限定和值类别。 |
| `T2` | 右操作数的推导类型；转发引用保留输入的cv限定和值类别。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 左侧操作数；按原值类别转发给运算表达式。 |
| `y` | 输入 | 右侧操作数；按原值类别转发给运算表达式。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `bool` | 返回`x <= y`按指定类型运算得到的结果。 |
| 原型2 | 原型尾置返回类型指定的表达式类型 | 返回转发后的同一运算表达式结果；类型由原型中的`decltype`确定。 |

## 约束说明

- 操作数必须支持原型中的运算表达式，原型1的结果还须能转换为其返回类型。
- 透明形式允许两侧类型不同；只有运算表达式有效时该形式才可用。
- 透明形式的`noexcept`与相应运算表达式一致；当前指定类型形式没有声明`noexcept`。Device调用还要求相应操作可在该执行位置使用。

## 调用示例

以下Host示例分别检查指定类型和透明形式的具体结果。

```cpp
#include <asc/std/functional>

static_assert(asc::std::less_equal<int>{}(4, 2) == (false));
static_assert(asc::std::less_equal<>{}(4L, 2) == (false));
```

## 关联API

- [`asc::std::less_equal`](less_equal.md)
- [本头文件的接口列表](asc_std_functional.md)
