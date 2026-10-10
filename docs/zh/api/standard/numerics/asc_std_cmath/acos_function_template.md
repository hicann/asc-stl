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

`asc::std::acos` 的 Host 整型兼容重载将整数转换为 float 后计算反余弦，并返回 float。这一行为保留此前整型调用的精度和返回类型，与标准库整型调用通常返回 double 的行为不同。

标准语义参考：[cppreference `cmath`](https://en.cppreference.com/w/cpp/header/cmath)。

## 函数原型

```cpp
template<class Integer, enable_if_t<is_integral<Integer>::value, int> = 0> float asc::std::acos(Integer value) noexcept;
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `Integer` | 整型参数类型，包含 bool；不接受浮点类型。 |
| `匿名约束参数2` | 用于在编译期筛选可参与重载的类型或表达式，调用方无需显式指定。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `value` | 输入 | 整型输入；有效实数定义域内的整数为 -1、0 和 1。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `float` | 返回转换为 float 后计算的反余弦弧度值。 |

## 约束说明

- 仅可在 Host 调用
- Integer 必须是整数类型（含 bool）
- 转换为 float 后计算并返回 float，保持既有整型调用行为

## 调用示例

以下片段演示本页接口的基本调用形式；输入和执行上下文须满足本页约束。

```cpp
#include <asc/std/cmath>

float example()
{
    return asc::std::acos(0);
}
```
