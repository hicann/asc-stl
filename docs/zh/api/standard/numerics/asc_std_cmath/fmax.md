# asc::std::fmax

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

`asc::std::fmax`按浮点最大值规则选择较大参数；Device侧适用范围以本页float与执行位置约束为准。

不同类型的可用位置见各原型及约束说明。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__is_extended_arithmetic_v<Tp>, int> = 0>
[[nodiscard]] constexpr conditional_t<is_integral_v<Tp>, double, Tp> fmax(Tp x, Tp y) noexcept;
}
```

可用位置：Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型2

```cpp
namespace asc::std {
template <class Tp, class Up,
    ::asc::std::enable_if_t<::asc::std::is_floating_point_v<Tp>&& ::asc::std::is_floating_point_v<Up>, int> = 0>
[[nodiscard]] constexpr auto fmax(Tp x, Up y) noexcept;
}
```

可用位置：Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Tp` | 数值类型；须满足对应原型中的整数、浮点或混合算术选择条件。标准整型提升到double的分支仅用于Host；Device不提供该整型提升。 |
| `Up` | 数值类型；须满足对应原型中的整数、浮点或混合算术选择条件。标准整型提升到double的分支仅用于Host；Device不提供该整型提升。 |

未命名的默认int模板形参用于重载选择，调用方无需提供。

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 参与求较大值的第一个操作数（无量纲）；任一操作数为NaN时返回另一个操作数。 |
| `y` | 输入 | 参与求较大值的第二个操作数（无量纲）；任一操作数为NaN时返回另一个操作数。 |

## 返回值说明

返回类型按各原型确定（`conditional_t<is_integral_v<Tp>, double, Tp>`、`auto`）。返回两个输入中的较大值；仅一个输入为NaN时返回另一个非NaN值。

## 约束说明

- Host标准整型输入提升为double；Device整型提升分支被静态断言拒绝。float、double、long double及扩展类型的实例还须由目标编译模式支持。

## 调用示例

以下Host示例给出具体输入和预期结果。

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::fmax(2.0F, 5.0F);
    return result == 5.0F;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
