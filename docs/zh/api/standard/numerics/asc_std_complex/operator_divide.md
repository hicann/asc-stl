# `asc::std::operator/`

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

头文件路径为：`<asc/std/complex>`。

`asc::std::operator/`按复数除法规则计算商。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class T> constexpr complex<T> operator/(const T& lhs, const complex<T>& rhs) noexcept;
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class T> constexpr complex<T> operator/(const complex<T>& lhs, const T& rhs) noexcept;
} // namespace asc::std
```

### 原型3

```cpp
namespace asc::std {
template<class T> constexpr complex<T> operator/(const complex<T>& lhs, const complex<T>& rhs) noexcept;
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 标量左操作数、右操作数复数与结果的成分值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 复数除法的左操作数（实数标量，作为被除数）。 |
| `rhs` | 输入 | 复数除法的右操作数（复数，作为除数，须非零）。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 左操作数复数、右操作数标量与结果的成分值类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 复数除法的左操作数（复数，作为被除数）。 |
| `rhs` | 输入 | 复数除法的右操作数（实数标量，作为除数，须非零）。 |

### 原型3的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 复数操作数的成分（实部与虚部）值类型，须为浮点类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 复数除法的左操作数（复数，作为被除数）。 |
| `rhs` | 输入 | 复数除法的右操作数（复数，作为除数，须非零）。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `complex<T>` | 返回按对应复数算术规则计算出的复数值。 |
| 原型2 | `complex<T>` | 返回按对应复数算术规则计算出的复数值。 |
| 原型3 | `complex<T>` | 返回按对应复数算术规则计算出的复数值。 |

## 约束说明

- 仅提供页面声明的float或`complex<float>`运算。
- 接口可用性取决于相应的float数学能力。

## 调用示例

以下Host片段使用具体对象展示接口调用。

```cpp
#include <asc/std/complex>

decltype(auto) example()
{
    asc::std::complex<float> left{1.0f, 2.0f};
    asc::std::complex<float> right{2.0f, 1.0f};
    return asc::std::operator/(left, right);
}

bool verify_example()
{
    const auto result = example();
    return result.real() == 0.8f && result.imag() == 0.6f;
}
```

## 关联API

- [本头文件的接口列表](asc_std_complex.md)
