# asc::round_up

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

头文件路径为：`<asc/cmath>`。

返回不小于非负整数 a 的最小正整数 b 的倍数。b 可以是任意正整数。

## 函数原型

```cpp
namespace asc {
template<class T>
[[nodiscard]] constexpr T round_up(T a, T b) noexcept;
}
```

## 参数说明

参数名与类型顺序见上述原型。T 为输入及返回的整数类型；E 仅表示指数类型，不与底数做通常算术转换。

## 返回值说明

`T` — 返回不小于非负整数 a 的最小正整数 b 的倍数。b 可以是任意正整数。

## 约束说明

a 非负、b 为正且最终结果可表示。a 为0时返回0，已为倍数时保持原值；不要求 b 为二的幂，也不要求 a+b-1 可表示。

整数模板仅支持不超过64位的 signed char、short、int、long、long long 及五种对应无符号类型；别名按实际类型判定。bool、普通char、其他字符、枚举、浮点和低精度包装不参与重载。二元参数同T，混合类型先由调用方确认值可表示再统一转换。

违反数值前提时，运行期行为未定义；此类调用不是核心常量表达式，要求常量结果时诊断。支持C++17/20的constexpr、noexcept；返回T不随整数提升变化。适用于Host、950PR/950DT的SIMT及普通SIMD标量控制代码。

## 调用示例

```cpp
#include <asc/cmath>

constexpr bool verify_example()
{
    return asc::round_up(1000u, 192u) == 1152u && asc::round_up(0u, 7u) == 0u;
}
```

## 关联API

- [本头文件的接口列表](asc_cmath.md)
