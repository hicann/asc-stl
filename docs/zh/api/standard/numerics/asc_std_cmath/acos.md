# asc::std::acos（函数）

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

头文件路径为：`<asc/std/cmath>`、`<asc/std/complex>`。

`asc::std::acos`计算反余弦，实数结果以弧度表示，取值范围为[0, π]。float重载可在Host侧和AI Core SIMT编程中调用，double和long double重载仅可在Host调用并保持对应精度；复数重载仅支持`complex<float>`。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float acos(
    float value) noexcept;
}
```

可用位置：Host、AI Core SIMT编程。以下constexpr适用于Host；Device声明不带constexpr，调用在运行期执行。

### 原型2

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
[[nodiscard]] constexpr Tp acos(Tp value) noexcept;
}
```

可用位置：Host、AI Core SIMT编程。以下constexpr适用于Host；Device声明不带constexpr，调用在运行期执行。扩展浮点模板仅在对应类型可用时参与；half、bfloat16及所支持FP8的数值调用用于AI Core SIMT编程。

### 原型3

```cpp
namespace asc::std {
[[nodiscard]] constexpr double acos(double value) noexcept;
}
```

可用位置：Host。

### 原型4

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double acos(long double value) noexcept;
}
```

可用位置：Host。long double相关重载要求Host启用该类型支持。

### 原型5

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
[[nodiscard]] constexpr double acos(Tp value) noexcept;
}
```

可用位置：Host。

### 原型6

```cpp
namespace asc::std {
template <class T>
[[nodiscard]] complex<T> acos(const complex<T>& value) noexcept;
}
```

可用位置：Host、AI Core SIMT编程。此复数重载需要包含`<asc/std/complex>`，ASC复数成分当前仅支持float。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Tp` | 数值类型；须满足对应原型中的整数、浮点或混合算术选择条件。 |
| `T` | 复数成分类型；ASC复数当前只支持float。 |

未命名的默认int模板形参用于重载选择，调用方无需提供。

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算的实数或复数值；实数有效定义域为[-1, 1]。 |

## 返回值说明

返回类型按各原型确定（`float`、`Tp`、`double`、`long double`、`complex<T>`）。返回反余弦；实数结果位于[0, π]，单位为弧度。

## 约束说明

- 扩展类型是否可实例化取决于目标类型支持；普通超越函数以float计算再转换回原格式，整数舍入和相邻数的规则见本页专门说明。

- float和`complex<float>`重载可在Host与AI Core SIMT编程中调用。
- double与long double重载限Host调用。
- 复数重载的T仅支持float。
- 实数有效定义域为[-1, 1]，域外输入和NaN的处理遵循对应数学后端。
- Host long double的实际精度由平台与工具链决定，不保证高于double。

## 调用示例

以下Host示例给出具体输入和预期结果。

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::acos(1.0F);
    return result == 0.0F;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
