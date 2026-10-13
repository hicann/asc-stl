# asc::std::frexp

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

`asc::std::frexp`把浮点值分解为尾数和二进制指数；Device侧适用范围以本页float与执行位置约束为准。

该接口的可用位置为Host、AI Core SIMT编程。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

```cpp
namespace asc::std {
float frexp(float x, int* e) noexcept;
} // namespace asc::std
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `x` | 输入 | 待分解为规范化尾数与指数的输入值（无量纲）。 |
| `e` | 输出 | 输出参数，函数将二进制指数写入该指针所指对象；指针须有效（指向可写`int`）。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `float` | 返回输入值的规格化尾数；指数写入输出参数。 |

## 约束说明

- 提供float重载和标准 *f别名，底层能力由Ascend C开发套件提供。

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cmath>

decltype(auto) example(float x, int * e)
{
    return asc::std::frexp(x, e);
}
```

## 关联API

- [本头文件的接口列表](asc_std_cmath.md)
