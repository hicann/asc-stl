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

`asc::std::complex::complex` 按本页所列构造形态初始化 `complex` 对象。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

### 原型 1

```cpp
constexpr complex(complex<T>&& other) noexcept(is_nothrow_move_constructible_v<T>);
```

### 原型 2

```cpp
constexpr complex(const complex<T>& other) noexcept(is_nothrow_copy_constructible_v<T>);
```

### 原型 3

```cpp
constexpr complex(const value_type& real, const value_type& imaginary) noexcept(is_nothrow_default_constructible_v<T>);
```

### 原型 4

```cpp
template<class U, enable_if_t<!Ascinternal::Isnonnarrowingconvertible<T, U>::value, int>, enable_if_t<is_constructible_v<T, U>, int>> constexpr complex(const complex<U>& other);
```

### 原型 5

```cpp
template<class U, enable_if_t<Ascinternal::Isnonnarrowingconvertible<T, U>::value, int>> constexpr complex(const complex<U>& other);
```

### 原型 6

```cpp
template<class U> complex(const ::std::complex<U>& other);
```

## 参数说明

### 原型 1 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入/输出 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 2 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 3 的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `real` | 输入 | 参与本页所述数学运算的输入值。 |
| `imaginary` | 输入 | 参与本页所述数学运算的输入值。 |

### 原型 4 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |
| `匿名约束参数3` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 5 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

### 原型 6 的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `U` | 本接口处理或保存的值类型；须满足原型中的类型约束。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `other` | 输入 | 待复制、移动、比较或交换的另一个对象；具体操作由所选原型决定。 |

## 约束说明

- 仅提供页面声明的 float 或 complex<float> 运算
- 接口可用性取决于相应的 float 数学能力

## 调用示例

以下 Host 片段使用具体数值类型演示调用；状态与参数须满足本页约束。

```cpp
#include <asc/std/complex>

void example()
{
    asc::std::complex<float> source(1.0f, 2.0f);
    asc::std::complex<float> copy(static_cast<asc::std::complex<float>&&>(source));
    (void)copy.real();
}
```
