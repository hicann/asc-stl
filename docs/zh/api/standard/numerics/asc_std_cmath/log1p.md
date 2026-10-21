# asc::std::log1p

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

头文件路径为：`<asc/std/cmath>`。

`asc::std::log1p`计算一加参数的自然对数；Device侧适用范围以本页float与执行位置约束为准。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float log1p(
    float value) noexcept;
}
```

可用位置：Host、AI Core SIMT编程。以下constexpr适用于Host；Device声明不带constexpr，调用在运行期执行。

### 原型2

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
[[nodiscard]] constexpr Tp log1p(
    Tp value) noexcept;
}
```

可用位置：Host、AI Core SIMT编程。以下constexpr适用于Host；Device声明不带constexpr，调用在运行期执行。扩展浮点模板仅在对应类型可用时参与；half、bfloat16及所支持FP8的数值调用用于AI Core SIMT编程。

### 原型3

```cpp
namespace asc::std {
[[nodiscard]] constexpr double log1p(double value) noexcept;
}
```

可用位置：Host。

### 原型4

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double log1p(long double value) noexcept;
}
```

可用位置：Host。long double相关重载要求Host启用该类型支持。

### 原型5

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
[[nodiscard]] constexpr double log1p(Tp value) noexcept;
}
```

可用位置：Host。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Tp` | 数值类型；须满足对应原型中的整数、浮点或混合算术选择条件。 |

未命名的默认int模板形参用于重载选择，调用方无需提供。

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算ln(1 + x)的输入值（无量纲）；定义域为 (-1, +∞)，-1返回 -inf，小于 -1返回NaN，输入接近0时保持精度。 |

## 返回值说明

返回类型按各原型确定（`float`、`Tp`、`double`、`long double`）。返回1加输入的自然对数，改善接近零时的精度。

## 约束说明

- 扩展类型是否可实例化取决于目标类型支持；普通超越函数以float计算再转换回原格式，整数舍入和相邻数的规则见本页专门说明。

## 调用示例

以下Host示例给出具体输入和预期结果。

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::log1p(0.0F);
    return result == 0.0F;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
