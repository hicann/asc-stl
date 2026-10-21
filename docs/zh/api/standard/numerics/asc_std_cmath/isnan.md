# asc::std::isnan

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

`asc::std::isnan`判断输入是否为NaN；浮点输入按相应类型分类，整数输入返回false。

不同类型的可用位置见各原型及约束说明。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
[[nodiscard]] constexpr bool isnan(float x) noexcept;
}
```

可用位置：Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型2

```cpp
namespace asc::std {
[[nodiscard]] constexpr bool isnan(double x) noexcept;
}
```

可用位置：Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型3

```cpp
namespace asc::std {
[[nodiscard]] constexpr bool isnan(long double x) noexcept;
}
```

可用位置：Host。long double相关重载要求Host启用该类型支持。

### 原型4

```cpp
namespace asc::std {
[[nodiscard]] constexpr bool isnan(__float128 x) noexcept;
}
```

可用位置：Host；该声明要求启用Host扩展浮点类型支持。

### 原型5

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<__is_extended_floating_point_v<Tp>, int> = 0>
[[nodiscard]] constexpr bool isnan(Tp x) noexcept;
}
```

可用位置：Host、AI Core SIMD编程、AI Core SIMT编程。扩展浮点模板仅在对应类型可用时参与；分类及符号查询的执行位置按本原型说明。

### 原型6

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
[[nodiscard]] constexpr bool isnan(Tp) noexcept;
}
```

可用位置：Host、AI Core SIMD编程、AI Core SIMT编程。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Tp` | 数值类型；须满足对应原型中的整数、浮点或混合算术选择条件。 |

未命名的默认int模板形参用于重载选择，调用方无需提供。

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 待判断是否为NaN的输入值（无量纲）。 |

## 返回值说明

返回类型按各原型确定（`bool`）。NaN返回true，其余返回false。

## 约束说明

- Host与Device实例化都要求目标支持所用类型；扩展浮点模板仅在相应类型已启用时参与。
- long double与__float128重载仅在对应Host类型支持已启用时提供，具体门控见各原型说明。

## 调用示例

以下Host示例给出具体输入和预期结果。

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::isnan(1.0F);
    return result == false;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
