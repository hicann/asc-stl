# asc::std::hypotf

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

`asc::std::hypotf`计算平方和的平方根；Device侧适用范围以本页float与执行位置约束为准。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float hypotf(
    float x, float y) noexcept;
}
```

可用位置：Host、AI Core SIMT编程。以下constexpr适用于Host；Device声明不带constexpr，调用在运行期执行。

### 原型2

```cpp
namespace asc::std {
[[nodiscard]] constexpr float hypotf(
    float x, float y, float z) noexcept;
}
```

可用位置：Host、AI Core SIMT编程。以下constexpr适用于Host；Device声明不带constexpr，调用在运行期执行。

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 三维斜边sqrt(x^2 + y^2 + z^2)计算中x方向的边长（无量纲）。 |
| `y` | 输入 | 三维斜边sqrt(x^2 + y^2 + z^2)计算中y方向的边长（无量纲）。 |
| `z` | 输入 | 三维斜边sqrt(x^2 + y^2 + z^2)计算中z方向的边长（无量纲）。 |

## 返回值说明

返回类型按各原型确定（`float`）。返回各输入平方和的平方根。

## 约束说明

- 保持参数说明中的数学定义域及指针有效性要求；可用位置和语言条件按各原型分别确定。

## 调用示例

以下Host示例给出具体输入和预期结果。

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::hypotf(3.0F, 4.0F);
    return result == 5.0F;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
