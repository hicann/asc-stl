# asc::std::fmaf

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

`asc::std::fmaf`计算一次舍入的乘加结果；Device侧适用范围以本页float与执行位置约束为准。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
[[nodiscard]] constexpr float fmaf(
    float x, float y, float z) noexcept;
}
```

可用位置：Host、AI Core SIMT编程。以下constexpr适用于Host；Device声明不带constexpr，调用在运行期执行。

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 融合乘加中乘积x * y的第一个因子（无量纲）。 |
| `y` | 输入 | 融合乘加中乘积x * y的第二个因子（无量纲）。 |
| `z` | 输入 | 融合乘加中与乘积相加的加数（无量纲）；整体仅做一次舍入。 |

## 返回值说明

返回类型按各原型确定（`float`）。返回乘积加第三参数的结果，仅进行一次舍入。

## 约束说明

- Host全整数模板按既有接口返回float；含double或long double的混合模板按原型的提升类型返回，不应假设所有整数数学函数都返回double。

## 调用示例

以下Host示例给出具体输入和预期结果。

```cpp
#include <asc/std/cmath>

bool example()
{
    return asc::std::fmaf(2.0F, 3.0F, 1.0F) == 7.0F;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
