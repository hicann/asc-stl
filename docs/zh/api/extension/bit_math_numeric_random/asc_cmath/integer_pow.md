# asc::integer_pow

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

`asc::integer_pow`使用整数运算计算`base`的`exponent`次幂。

## 函数原型

```cpp
namespace asc {
template <class T, class E>
[[nodiscard]] constexpr T integer_pow(T base, E exponent) noexcept;
}  // namespace asc
```

## 参数说明

**模板参数**

| 参数名 | 描述 |
| --- | --- |
| `T` | 底数与幂结果的整数或枚举类型。 |
| `E` | 指数的整数或枚举类型。 |

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `base` | 输入 | 整数幂运算的底数。 |
| `exponent` | 输入 | 整数幂运算的指数；取非负整数。 |

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `T` | 返回输入值按接口规定运算后的数值结果。 |

## 约束说明

- T和E必须为非bool的整数或枚举类型。
- 有符号指数不得为负数。
- 结果必须可表示。

## 调用示例

以下Host示例使用具体输入，并检查结果。

```cpp
#include <asc/cmath>

bool example()
{
    const auto result = asc::integer_pow(2, 3);
    return result == 8;
}
```

## 关联API

- [本头文件的接口列表](asc_cmath.md)
