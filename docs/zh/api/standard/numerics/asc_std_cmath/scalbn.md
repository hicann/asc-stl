# asc::std::scalbn

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

`asc::std::scalbn`按二进制指数缩放浮点值；Device侧适用范围以本页float与执行位置约束为准。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float scalbn(
    float value, int exponent) noexcept;
}
```

可用位置：Host、AI Core SIMT编程。以下constexpr适用于Host；Device声明不带constexpr，调用在运行期执行。

### 原型2

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__expo_supported_extended_v<Tp>, int> = 0>
[[nodiscard]] constexpr Tp scalbn(
    Tp value, int exponent) noexcept;
}
```

可用位置：Host、AI Core SIMT编程。以下constexpr适用于Host；Device声明不带constexpr，调用在运行期执行。

### 原型3

```cpp
namespace asc::std {
[[nodiscard]] constexpr double scalbn(double value, int exponent) noexcept;
}
```

可用位置：Host。

### 原型4

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double scalbn(long double value, int exponent) noexcept;
}
```

可用位置：Host。long double相关重载要求Host启用该类型支持。

### 原型5

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
[[nodiscard]] constexpr double scalbn(Tp value, int exponent) noexcept;
}
```

可用位置：Host。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Tp` | 数值类型；须满足对应原型中的整数、浮点或混合算术选择条件。指数与缩放族的扩展浮点选择仅接受可用的half和bfloat16，不接受FP8。 |

未命名的默认int模板形参用于重载选择，调用方无需提供。

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待按FLT_RADIX（为2）的整数次幂缩放的浮点值（无量纲）。 |
| `exponent` | 输入 | 待按FLT_RADIX（为2）的整数次幂缩放的浮点值（无量纲）。 |

## 返回值说明

返回类型按各原型确定（`float`、`Tp`、`double`、`long double`）。返回输入乘以浮点基数的exponent次幂。

## 约束说明

- 指数和缩放族的扩展浮点模板仅接受half和bfloat16；FP8未提供该族扩展重载。

- 提供float重载和标准 *f别名，底层能力由Ascend C开发套件提供。

## 调用示例

以下Host示例给出具体输入和预期结果。

```cpp
#include <asc/std/cmath>

bool example()
{
    return asc::std::scalbn(0.5F, 4) == 8.0F;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
