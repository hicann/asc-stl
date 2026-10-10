# asc::std::operator/

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

`asc::std::operator/` 按复数除法规则计算商。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

### 原型 1

```cpp
template<class T> [[nodiscard]] constexpr complex<T> asc::std::operator/(const T& lhs, const complex<T>& rhs);
```

### 原型 2

```cpp
template<class T> [[nodiscard]] constexpr complex<T> asc::std::operator/(const complex<T>& lhs, const T& rhs);
```

### 原型 3

```cpp
template<class T> [[nodiscard]] constexpr complex<T> asc::std::operator/(const complex<T>& lhs, const complex<T>& rhs);
```

## 参数说明

### 原型 1 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与本页所述数学运算的输入值。 |
| `rhs` | 输入 | 参与本页所述数学运算的输入值。 |

### 原型 2 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与本页所述数学运算的输入值。 |
| `rhs` | 输入 | 参与本页所述数学运算的输入值。 |

### 原型 3 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `lhs` | 输入 | 参与本页所述数学运算的输入值。 |
| `rhs` | 输入 | 参与本页所述数学运算的输入值。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型 1 | `complex<T>` | 返回按对应复数算术规则计算出的复数值。 |
| 原型 2 | `complex<T>` | 返回按对应复数算术规则计算出的复数值。 |
| 原型 3 | `complex<T>` | 返回按对应复数算术规则计算出的复数值。 |

## 约束说明

- 仅提供页面声明的 float 或 complex<float> 运算
- 接口可用性取决于相应的 float 数学能力

## 调用示例

以下 Host 片段使用具体对象展示接口调用。

```cpp
#include <asc/std/complex>

decltype(auto) example()
{
    asc::std::complex<float> left{1.0f, 2.0f};
    asc::std::complex<float> right{2.0f, 1.0f};
    return asc::std::operator/(left, right);
}
```
