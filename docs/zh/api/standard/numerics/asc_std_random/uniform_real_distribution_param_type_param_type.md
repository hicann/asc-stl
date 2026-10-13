# asc::std::uniform_real_distribution::param_type::param_type

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

头文件路径为：`<asc/std/random>`。

构造float均匀实数分布的半开区间参数对象。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 函数原型

```cpp
constexpr explicit asc::std::uniform_real_distribution<float>::param_type::param_type(float a = 0.0F, float b = 1.0F) noexcept;
```

## 参数说明

**函数参数**

| 参数名 | 输入/输出 | 描述 |
| --- | --- | --- |
| `a` | 输入 | 均匀实数分布半开区间的下界；生成值满足a <= x < b，省略时为0.0F。 |
| `b` | 输入 | 均匀实数分布半开区间的上界；省略时为1.0F。 |

## 返回值说明

无返回值。

## 约束说明

- 仅提供uniform_real_distribution<float>。
- 结果位于指定的半开区间内，不提供double、long double及其他统计分布。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/random>
#include <asc/std/limits>

bool example()
{
    asc::std::uniform_real_distribution<float>::param_type parameters(2.0f, 5.0f);
    return parameters.a() == 2.0f && parameters.b() == 5.0f;
}
```

## 关联API

- [本头文件的接口列表](asc_std_random.md)
