# asc::std::greater::operator()

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

`asc::std::greater::operator()` 按函数对象名称比较输入值并返回布尔结果。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

### 原型 1

```cpp
[[nodiscard]] constexpr bool asc::std::greater::operator()(const T& x, const T& y) const;
```

### 原型 2

```cpp
template<class T1, class T2> [[nodiscard]] constexpr auto asc::std::greater::operator()(T1&& x, T2&& y) const noexcept(noexcept(::asc::std::forward<T1>(T) > ::asc::std::forward<T2>(U))) -> decltype(::asc::std::forward<T1>(T) > ::asc::std::forward<T2>(U));
```

### 原型 3

```cpp
template<class T, class U> [[nodiscard]] constexpr bool asc::std::greater::operator()(T&& x, U&& y) const noexcept(noexcept(bool(::asc::std::forward<U>(U4) < ::asc::std::forward<T>(T4))));
```

## 参数说明

### 原型 1 的参数

无参数。

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `T2` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |
| 原型 2 | `decltype(::asc::std::forward<T1>(T) > ::asc::std::forward<T2>(U))` | 返回函数对象按所选实参调用得到的结果。 |
| 原型 3 | `bool` | 条件成立时返回 `true`，否则返回 `false`。 |

## 约束说明

- 同时提供指定类型形式和透明调用形式

## 调用示例

以下 Host 片段以具体整数实参演示函数对象调用。

```cpp
#include <asc/std/functional>

decltype(auto) example()
{
    return asc::std::greater<>{}(1, 2);
}
```
