# asc::std::complex::complex

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

`asc::std::complex::complex`按本页所列构造形态初始化`complex`对象。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

### 原型1

```cpp
constexpr complex(complex<T>&& other) noexcept(is_nothrow_move_constructible_v<T>);
```

### 原型2

```cpp
constexpr complex(const complex<T>& other) noexcept(is_nothrow_copy_constructible_v<T>);
```

### 原型3

```cpp
constexpr complex(const value_type& real, const value_type& imaginary) noexcept(is_nothrow_default_constructible_v<T>);
```

### 原型4

```cpp
template<class U, enable_if_t<!Ascinternal::Isnonnarrowingconvertible<T, U>::value, int>, enable_if_t<is_constructible_v<T, U>, int>> constexpr complex(const complex<U>& other);
```

### 原型5

```cpp
template<class U, enable_if_t<Ascinternal::Isnonnarrowingconvertible<T, U>::value, int>> constexpr complex(const complex<U>& other);
```

### 原型6

```cpp
template<class U> complex(const ::std::complex<U>& other);
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 移动构造的源complex对象（右值引用，构造后源处于有效但未指定状态）。 |

### 原型2的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 复制构造的源complex对象（复制其实部与虚部）。 |

### 原型3的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `real` | 输入 | 初始化实部的值（value_type标量，无量纲）。 |
| `imaginary` | 输入 | 初始化虚部的值（value_type标量，无量纲）。 |

### 原型4的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 源复数的成分值类型（转换为T时可能收窄，对应显式构造原型）。 |
**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 转换构造的源complex对象（成分为U，经static_cast转为T，可能收窄）。 |

### 原型5的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 源复数的成分值类型（非收窄地转换为T，对应隐式构造原型）。 |
**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 转换构造的源complex对象（成分为U，无损地转换为T）。 |

### 原型6的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 源std::complex的成分值类型（转换为T）。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 转换构造的源std::complex对象（成分为U，仅Host侧可用）。 |

## 返回值说明

无返回值。

## 约束说明

- 仅提供页面声明的float或`complex<float>`运算。
- 接口可用性取决于相应的float数学能力。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/complex>

bool example()
{
    asc::std::complex<float> value(2.0f, 3.0f);
    return value.real() == 2.0f && value.imag() == 3.0f;
}
```

## 关联API

- [本头文件的接口列表](asc_std_complex.md)
