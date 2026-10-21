# asc::std::uniform_int_distribution::min

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

`asc::std::uniform_int_distribution::min`返回当前分布参数的下界a()。

标准语义参考：[cppreference `random`](https://en.cppreference.com/w/cpp/header/random)。

## 函数原型

所属类型：[`asc::std::uniform_int_distribution`](uniform_int_distribution.md)。

```cpp
// asc::std::uniform_int_distribution 类内的声明节选；模板形参和其他成员由所属类提供。
constexpr result_type min() const noexcept;
```

## 参数说明

无参数。

## 返回值说明

| 返回值类型 | 含义 |
| --- | --- |
| `result_type` | 返回当前分布参数的下界a()。 |

## 约束说明

- 支持全部标准整数结果类型。

## 调用示例

以下Host示例给出具体输入，并检查调用结果。

```cpp
#include <asc/std/random>
#include <asc/std/limits>

bool example()
{
    asc::std::uniform_int_distribution<int> distribution(2, 5);
    return distribution.min() == 2;
}
```

## 关联API

- [`asc::std::uniform_int_distribution`](uniform_int_distribution.md)
- [本头文件的接口列表](asc_std_random.md)
