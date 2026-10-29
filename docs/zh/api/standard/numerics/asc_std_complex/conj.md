# asc::std::conj

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

`asc::std::conj`返回复数的共轭值。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

### 原型1

```cpp
namespace asc::std {
template<class T> [[nodiscard]] constexpr complex<T> conj(T value) noexcept;
} // namespace asc::std
```

### 原型2

```cpp
namespace asc::std {
template<class T> constexpr complex<T> conj(const complex<T>& value) noexcept;
} // namespace asc::std
```

## 参数说明

### 原型1的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 实数输入及返回复数的成分类型，当前须为`float`。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待求共轭的实数输入（按虚部为0的复数处理，共轭为其自身）。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 复数操作数的成分类型，当前须为`float`。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待求共轭的复数操作数（返回虚部取反、实部不变的复数）。 |

## 返回值说明

| 适用原型 | 返回值类型 | 含义 |
| --- | --- | --- |
| 原型1 | `complex<T>` | 返回复数的共轭值。 |
| 原型2 | `complex<T>` | 返回复数的共轭值。 |

## 约束说明

- 仅提供页面声明的float或`complex<float>`运算。
- 接口可用性取决于相应的float数学能力。

## 调用示例

以下Host片段使用具体对象展示接口调用。

```cpp
#include <asc/std/complex>

decltype(auto) example()
{
    asc::std::complex<float> value{1.0f, 2.0f};
    return asc::std::conj(value);
}

bool verify_example()
{
    const auto result = example();
    return result.real() == 1.0f && result.imag() == -2.0f;
}
```

## 关联API

- [本头文件的接口列表](asc_std_complex.md)
