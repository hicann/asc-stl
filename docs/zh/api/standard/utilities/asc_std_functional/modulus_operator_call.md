# asc::std::modulus::`operator()`

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

`asc::std::modulus::operator()`按函数对象名称对操作数执行对应算术运算。

标准语义参考：[cppreference `functional`](https://en.cppreference.com/w/cpp/header/functional)。

## 函数原型

所属类型：[`asc::std::modulus`](modulus.md)。

### 原型1

```cpp
// asc::std::modulus 类内的声明节选；模板形参和其他成员由所属类提供。
[[nodiscard]] constexpr T operator()(const T& x, const T& y) const;
```

### 原型2

```cpp
// asc::std::modulus 类内的声明节选；模板形参和其他成员由所属类提供。
template<class T1, class T2> [[nodiscard]] constexpr auto operator()(T1&& x, T2&& y) const noexcept(noexcept(::asc::std::forward<T1>(T) % ::asc::std::forward<T2>(U))) -> decltype(::asc::std::forward<T1>(T) % ::asc::std::forward<T2>(U));
```

## 参数说明

### 原型1的参数

无参数。

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T1` | 左侧操作数类型；须支持该函数对象执行的运算。 |
| `T2` | 右侧操作数类型；须支持该函数对象执行的运算。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `T` | 返回函数对象按所选实参调用得到的结果。 |
| 原型2 | `decltype(::asc::std::forward<T1>(T) % ::asc::std::forward<T2>(U))` | 返回函数对象按所选实参调用得到的结果。 |

## 约束说明

- 同时提供指定类型形式和透明调用形式。

## 调用示例

以下Host片段以具体整数实参演示函数对象调用。

```cpp
#include <asc/std/functional>

decltype(auto) example()
{
    return asc::std::modulus<>{}(1, 2);
}
```

## 关联API

- [`asc::std::modulus`](modulus.md)
- [本头文件的接口列表](asc_std_functional.md)
