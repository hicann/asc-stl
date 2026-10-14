# asc::std::acosl

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

`asc::std::acosl`在Host上以long double精度计算反余弦，结果以弧度表示，取值范围为[0, π]。long double的实际精度由Host平台和工具链决定，不保证高于double。

cmath 的 `l` 后缀宿主别名族（如 `sinl`、`fabsl`、`sqrtl` 等）当前均已交付：各别名与 `acosl` 一样仅限 Host 车道，经对应的 `__builtin_*l` 入口路由，本库不在设备车道暴露 long double。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

```cpp
namespace asc::std {
long double acosl(long double value) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待计算的long double值，有效定义域为[-1, 1]。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `long double` | 返回long double反余弦弧度值；定义域外输入按Host数学实现处理。 |

## 约束说明

- 仅可在Host调用。
- 使用参数对应的浮点精度。
- 有效实数输入范围为[-1, 1]。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cmath>

long double example()
{
    return asc::std::acosl(0.5L);
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
