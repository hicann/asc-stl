# asc::std::roundl

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

`asc::std::roundl`由`<asc/std/cmath>`提供，宿主long double半值远离零取整，后缀l别名

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

```cpp
namespace asc::std {
constexpr long double roundl(long double value) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 待就近取整（半值远离零）的输入值（无量纲）。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `long double` | 最接近输入的整数值，中点向远离零的方向舍入。 |

## 约束说明

- 宿主long double半值远离零取整，后缀l别名。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cmath>

decltype(auto) example(long double value)
{
    return asc::std::roundl(value);
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
