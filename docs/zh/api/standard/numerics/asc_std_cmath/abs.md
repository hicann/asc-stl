# asc::std::abs

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

头文件路径为：`<asc/std/cmath>`、`<asc/std/complex>`、`<asc/std/cstdlib>`。

`asc::std::abs`返回参数的绝对值；Device侧适用范围以本页float与执行位置约束为准。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float abs(float x) noexcept;
}
```

可用位置：Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型2

```cpp
namespace asc::std {
[[nodiscard]] constexpr double abs(double x) noexcept;
}
```

可用位置：Host、AI Core SIMD编程、AI Core SIMT编程。

### 原型3

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double abs(long double x) noexcept;
}
```

可用位置：Host。long double相关重载要求Host启用该类型支持。

### 原型4

```cpp
namespace asc::std {
template <class T>
[[nodiscard]] T abs(const complex<T>& value) noexcept;
}
```

可用位置：Host、AI Core SIMT编程。此复数重载需要包含`<asc/std/complex>`，ASC复数成分当前仅支持float。

### 标准整数重载

以下形式需包含`<asc/std/cstdlib>`，可用于Host及适用Device模式。

```cpp
namespace asc::std {
constexpr int abs(int value) noexcept;
}
```

```cpp
namespace asc::std {
constexpr long abs(long value) noexcept;
}
```

```cpp
namespace asc::std {
constexpr long long abs(long long value) noexcept;
}
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 复数成分类型；ASC复数当前只支持float。 |

未命名的默认int模板形参用于重载选择，调用方无需提供。

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 待求浮点绝对值的输入值（无量纲）。 |
| `value` | 输入 | 待求模（绝对值）的复数操作数，模为实部与虚部构成向量的长度。 |

## 返回值说明

返回类型按各原型确定（`float`、`double`、`long double`、`T`）。返回实数的绝对值或复数的模。

## 约束说明

- 提供整数重载及相应结果类型。
- 标准整数重载要求参数的绝对值可由返回类型表示，例如`abs(INT_MIN)`不满足该要求，行为无定义。
- 标量精度与执行位置按各原型确定；复数输入仅支持complex<float>。
- 接口可用性取决于相应的float数学能力。

## 调用示例

以下Host示例给出具体输入和预期结果。

```cpp
#include <asc/std/cmath>

bool example()
{
    return asc::std::abs(-2.0F) == 2.0F;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
