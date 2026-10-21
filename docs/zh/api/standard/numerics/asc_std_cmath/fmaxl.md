# asc::std::fmaxl

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

`asc::std::fmaxl`返回两个long double实参中较大者；任一实参为NaN时返回另一个实参。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double fmaxl(long double x, long double y) noexcept;
}
```

可用位置：Host。long double相关重载要求Host启用该类型支持。

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 参与求较大值的第一个操作数（无量纲）；任一操作数为NaN时返回另一个操作数。 |
| `y` | 输入 | 参与求较大值的第一个操作数（无量纲）；任一操作数为NaN时返回另一个操作数。 |

## 返回值说明

返回类型按各原型确定（`long double`）。返回两个输入中的较大值；仅一个输入为NaN时返回另一个非NaN值。

## 约束说明

- Host标准整型输入提升为double；Device整型提升分支被静态断言拒绝。float、double、long double及扩展类型的实例还须由目标编译模式支持。

- NaN感知：仅当两实参均为NaN时返回NaN，恒不抛出。

## 调用示例

以下Host示例给出具体输入和预期结果。

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::fmaxl(2.0L, 5.0L);
    return result == 5.0L;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
