# asc::std::lerp

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

`asc::std::lerp`计算两个值之间的线性插值；Device侧适用范围以本页float与执行位置约束为准。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
[[nodiscard]] float lerp(float a, float b, float t) noexcept;
}
```

可用位置：Host、AI Core SIMT编程。

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `a` | 输入 | 线性插值的起点值（无量纲）。 |
| `b` | 输入 | 线性插值的终点值（无量纲）。 |
| `t` | 输入 | 插值权重（无量纲）；数学上为a + t * (b - a)，实现避免有限区间内异号大数差值溢出；t = 1时返回b，允许取[0, 1] 之外的值做外推。 |

## 返回值说明

返回类型按各原型确定（`float`）。返回线性插值；有限端点及[0, 1]权重产生有限结果，并保持端点与单调性。

## 约束说明

- a、b有限且t在[0, 1]内时返回有限结果，并保持端点与单调性；外推结果仍可能溢出。

## 调用示例

以下Host示例给出具体输入和预期结果。

```cpp
#include <asc/std/cmath>

bool example()
{
    return asc::std::lerp(-3.0e38F, 3.0e38F, 0.5F) == 0.0F;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
