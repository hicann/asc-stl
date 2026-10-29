# `asc::std::operator*`

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

`asc::std::operator*`执行复数乘法：原型1将两个`complex<float>`按复数乘法规则相乘；原型2将`complex<float>`的实部与虚部同乘`float`标量；原型3为`float`标量乘以`complex<float>`，与原型2的标量乘法结果相同。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

以下函数模板可用于Host、AI Core SIMD编程和AI Core SIMT编程；T当前只能为float。

```cpp
namespace asc::std {
template<class T> constexpr complex<T> operator*(const complex<T>& left, const complex<T>& right) noexcept;
}
```

```cpp
namespace asc::std {
template<class T> constexpr complex<T> operator*(const complex<T>& left, const T& right) noexcept;
}
```

```cpp
namespace asc::std {
template<class T> constexpr complex<T> operator*(const T& left, const complex<T>& right) noexcept;
}
```

Host另外提供两个按值接收float的非模板重载：

```cpp
namespace asc::std {
constexpr complex<float> operator*(const complex<float>& left, float right) noexcept;
}
```

```cpp
namespace asc::std {
constexpr complex<float> operator*(float left, const complex<float>& right) noexcept;
}
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | ASC复数成分类型，当前仅float。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `left` | 输入 | 乘法左操作数，复数或标量float。 |
| `right` | 输入 | 乘法右操作数，复数或标量float。 |

两个复数按复数乘法计算；标量重载对实部、虚部同乘标量，不修改输入。

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `asc::std::complex<float>` | 返回按对应复数算术规则计算出的复数值。 |
| 原型2 | `asc::std::complex<float>` | 返回按对应复数算术规则计算出的复数值。 |
| 原型3 | `asc::std::complex<float>` | 返回按对应复数算术规则计算出的复数值。 |

## 约束说明

- 仅提供页面声明的float或`complex<float>`运算。
- 接口可用性取决于相应的float数学能力。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/complex>

decltype(auto) example(const asc::std::complex<float>& lhs, const asc::std::complex<float>& rhs)
{
    return asc::std::operator*(lhs, rhs);
}

bool verify_example()
{
    const auto result = example(asc::std::complex<float>(1.0f, 2.0f), asc::std::complex<float>(2.0f, 1.0f));
    return result.real() == 0.0f && result.imag() == 5.0f;
}
```

## 关联API

- [本头文件的接口列表](asc_std_complex.md)
