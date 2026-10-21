# asc::std::fabsl

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

`asc::std::fabsl`返回long double实参的绝对值，constexpr且可作用于常量表达式。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
[[nodiscard]] constexpr long double fabsl(long double x) noexcept;
}
```

可用位置：Host。long double相关重载要求Host启用该类型支持。

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 待求浮点绝对值的输入值（无量纲）。 |

## 返回值说明

返回类型按各原型确定（`long double`）。返回清除符号后的绝对值；float、double、long double保留原类型，Host整数输入返回double。

## 约束说明

- Host标准整型输入提升为double；Device整型提升分支被静态断言拒绝。float、double、long double及扩展类型的实例还须由目标编译模式支持。

- 参数为负时返回其相反数，恒不抛出。

## 调用示例

以下Host示例给出具体输入和预期结果。

```cpp
#include <asc/std/cmath>

bool example()
{
    const auto result = asc::std::fabsl(-2.0L);
    return result == 2.0L;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
