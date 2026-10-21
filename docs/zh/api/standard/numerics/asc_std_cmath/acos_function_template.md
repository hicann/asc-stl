# asc::std::acos（函数模板）

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

`asc::std::acos`的Host整型兼容重载将整数提升为double后计算反余弦，并返回double，与标准`<cmath>`整型调用的行为一致。设备侧整型实参仍经float重载计算并返回float。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

各重载自C++17起提供。执行位置限定按下列原型分别说明；执行位置宏已省略。

### 原型1

```cpp
namespace asc::std {
template <class Tp, ::asc::std::enable_if_t<is_integral_v<Tp>, int> = 0>
[[nodiscard]] constexpr double acos(Tp value) noexcept;
}
```

可用位置：Host。

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Tp` | 数值类型；须满足对应原型中的整数、浮点或混合算术选择条件。 |

未命名的默认int模板形参用于重载选择，调用方无需提供。

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 整型输入；有效实数定义域内的整数为 -1、0和1。 |

## 返回值说明

返回类型按各原型确定（`double`）。返回反余弦；实数结果位于[0, π]，单位为弧度。

## 约束说明

- 仅可在Host调用。
- Integer必须是整数类型（含bool）。
- 整型实参提升为double后计算并返回double，对齐标准`<cmath>`行为。

## 调用示例

以下Host示例展示具体输入、接口调用和可检查的结果。

```cpp
#include <asc/std/cmath>
#include <asc/std/type_traits>
#include <cmath>

bool example()
{
    static_assert(asc::std::is_same_v<decltype(asc::std::acos(0)), double>);
    const double value = asc::std::acos(0);
    return ::std::abs(value - ::std::acos(0.0)) < 1e-14;
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
