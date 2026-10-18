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

所属类型：[`asc::std::complex<T>`](complex.md)。当前`T`仅支持`float`。以下为该类型可直接使用的构造声明。

### 默认及标量构造

```cpp
constexpr complex(const T& real = T(), const T& imag = T()) noexcept;
```

### 复制构造

```cpp
constexpr complex(const complex& other) noexcept = default;
```

### 移动构造

```cpp
constexpr complex(complex&& other) noexcept = default;
```

### Host系统复数转换

```cpp
template<class U>
complex(const ::std::complex<U>& other) noexcept;
```

最后一种形式仅可在Host调用，将系统复数的两个成分分别转换为`float`。ASC复数间的转换模板不会放宽目标和源ASC类型的限制；`asc::std::complex<double>`不能实例化，本页不将它列作可用输入。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 所属ASC复数的成分类型，当前须为`float`。 |
| `U` | Host系统复数输入的成分类型，须能通过`static_cast<float>`转换。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `real` | 输入 | 初始实部，省略时为0。 |
| `imag` | 输入 | 初始虚部，省略时为0。 |
| `other` | 输入 | 提供实部与虚部的源复数；系统复数转换可能发生精度损失。 |

## 返回值说明

无返回值。

## 约束说明

- `asc::std::complex`当前只支持`float`成分类型；源为系统`::std::complex<U>`时不受ASC源类型限制，但只能在Host转换。
- 复制和移动构造复制两个浮点成分，不借用源对象存储。
- 默认及ASC同类型构造可在相应Host／Device编程模式使用；系统复数转换需要Host标准库。
- `volatile`限定的成分访问和设置成员见各成员页；它们不改变这里的构造重载集合。

## 调用示例

以下Host示例给出具体输入，并检查结果。

```cpp
#include <complex>
#include <asc/std/complex>
#include <asc/std/utility>

bool example()
{
    asc::std::complex<float> zero;
    asc::std::complex<float> scalar(2.0F);
    asc::std::complex<float> value(2.0F, 3.0F);
    const auto copy = value;
    const auto moved = asc::std::move(value);
    const asc::std::complex<float> converted(::std::complex<double>(4.0, 5.0));
    return zero.real() == 0.0F && scalar.imag() == 0.0F && copy.imag() == 3.0F &&
        moved.real() == 2.0F && converted.real() == 4.0F && converted.imag() == 5.0F;
}
```

## 关联API

- [本头文件的接口列表](asc_std_complex.md)
