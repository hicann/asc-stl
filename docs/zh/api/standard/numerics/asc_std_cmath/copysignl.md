# asc::std::copysignl

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

`asc::std::copysignl`由`<asc/std/cmath>`提供，组合幅值与符号位生成带符号的长双精度浮点值。接口遵循对应C++ 标准设施的语义；ASC-STL的语言模式和调用位置以本页声明为准。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

```cpp
namespace asc::std {
constexpr long double copysignl(long double x, long double y) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 控制本次操作的标量值；有效取值由声明和约束说明共同确定。 |
| `y` | 输入 | 控制本次操作的标量值；有效取值由声明和约束说明共同确定。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `long double` | 大小取自第一个实参、符号取自第二个实参的值。 |

## 约束说明

- 把第二个参数的符号位复制到第一个参数的幅值上，返回long double结果。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cmath>

decltype(auto) example(long double x, long double y)
{
    return asc::std::copysignl(x, y);
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
