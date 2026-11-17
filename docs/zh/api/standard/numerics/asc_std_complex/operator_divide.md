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
- 复数除法采用比值缩放。对于有限输入，若中间分量发生溢出，会使用缩放后的分子重新求值；例如，`(max + max*i) / (1 + i)` 返回 `(max, 0)`，其中 `max` 是最大有限float值。计算仍使用float精度，仍可能发生舍入、下溢或数学结果超出表示范围。
- 估计频率响应时，应在调用本接口前剔除或单独处理激励值为零的频点。
- 在已验证的 CANN 9.2.0-beta.2 / Ascend 950 SIMT 配置中，`(1 + i) / (max + max*i)` 返回零，而数学结果的实部约为次正规值 `2.93873588e-39`。直接执行 `1.0f / max` 也返回零，但 `min_normal * 0.5f`、按位构造和读写均保留相应的次正规值。这是该配置除法路径的实测限制，不能据此推断所有设备算术都会将次正规值清零。本复数除法实现尚未恢复该结果；下溢边界应在实际工具链和设备上验证。

## 调用示例

以下Host示例批量估计频率响应。第二个频点覆盖大幅值的有限频谱数据，使用复数除法表达计算，无须手工展开实部与虚部公式。

```cpp
#include <asc/std/complex>
#include <asc/std/limits>

using Complex = asc::std::complex<float>;

// Frequency response H[k] = Y[k] / X[k]; each excitation bin is nonzero.
void example(const Complex* measured, const Complex* excitation, Complex* response, int bins)
{
    for (int k = 0; k < bins; ++k) {
        response[k] = measured[k] / excitation[k];
    }
}

bool verify_example()
{
    const float large = asc::std::numeric_limits<float>::max();
    const Complex measured[] = {{1.0f, 2.0f}, {large, large}};
    const Complex excitation[] = {{2.0f, 1.0f}, {1.0f, 1.0f}};
    Complex response[2];
    example(measured, excitation, response, 2);
    return response[0].real() == 0.8f && response[0].imag() == 0.6f &&
        response[1].real() == large && response[1].imag() == 0.0f;
}
```

## 关联API

- [本头文件的接口列表](asc_std_complex.md)
