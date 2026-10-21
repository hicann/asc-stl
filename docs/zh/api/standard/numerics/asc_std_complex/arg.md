# asc::std::arg

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

`asc::std::arg`返回复数的幅角。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `complex`](https://en.cppreference.com/w/cpp/header/complex)。

## 函数原型

以下两种形式用于Host及AI Core SIMT编程：

```cpp
namespace asc::std {
[[nodiscard]] float arg(float value) noexcept;
}
```

```cpp
namespace asc::std {
template<class T> [[nodiscard]] T arg(const complex<T>& value) noexcept;
}
```

以下标量重载仅用于Host：

```cpp
namespace asc::std {
[[nodiscard]] double arg(double value) noexcept;
}
```

```cpp
namespace asc::std {
[[nodiscard]] long double arg(long double value) noexcept;
}
```

```cpp
namespace asc::std {
template<class T> [[nodiscard]] double arg(T value) noexcept;
}
```

## 参数说明

### 原型1的参数

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待求幅角的实数输入（按虚部为0的复数处理，返回值为0或 π 弧度）。 |

### 原型2的参数

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 复数操作数的成分（实部与虚部）值类型，须为浮点类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待求幅角的复数操作数（幅角为atan2(虚部, 实部)，单位为弧度）。 |

## 返回值说明

返回以弧度表示的幅角atan2(虚部, 实部)。复数输入返回T；标量float、double、long double分别返回原类型，整数返回double。标量视为虚部为正零的复数。

## 约束说明

- ASC复数输入只支持complex<float>；Host标量另外支持double、long double及整数。整数模板通过static_assert要求T为整数类型。
- 接口可用性取决于相应的float数学能力。

## 调用示例

以下Host示例使用具体输入，并检查结果。

```cpp
#include <asc/std/complex>

bool example()
{
    const asc::std::complex<float> value(1.0F, 0.0F);
    return asc::std::arg(value) == 0.0F && asc::std::arg(2.0) == 0.0;
}
```

## 关联API

- [本头文件的接口列表](asc_std_complex.md)
